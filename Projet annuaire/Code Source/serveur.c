/**********************************************
 * 
 * Fichier contenant les fonctions du serveur qui sont essentielles à l'échange
 * entre celui-ci et le client.
 * 
 * Créé et programmé par Clément BRONGNIART.
 * 
 * *******************************************/

#include <ctype.h>
#include <sys/types.h>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "purge.c"
#include "structures.c"
#include "codes.c"

#ifdef WIN32
#define perror(x) printf("%s : code d'erreur : %d\n", (x), WSAGetLastError())
#define close closesocket
#define socklen_t int
#endif

/* Variables cachees */

/* le socket d'ecoute */
int socketEcoute;
/* longueur de l'adresse */
socklen_t longeurAdr;
/* le socket de service */
int socketService;
int debutTampon;
int finTampon;

int VerificationConnexion();
requete Reception();
int Emission(reponse rep);
void DeconnexionClient();

/* Initialisation.
 * Création du serveur en précisant le service ou numéro de port.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int InitialisationAvecService(char *service) {
	int n;
	const int on = 1;
	struct addrinfo	hints, *res, *ressave;

	#ifdef WIN32
	WSADATA	wsaData;
	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR)
	{
		printf("WSAStartup() n'a pas fonctionne, erreur : %d\n", WSAGetLastError()) ;
		WSACleanup();
		exit(1);
	}
	memset(&hints, 0, sizeof(struct addrinfo));
    #else
	bzero(&hints, sizeof(struct addrinfo));
	#endif

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ( (n = getaddrinfo(NULL, service, &hints, &res)) != 0)  {
     		printf("Initialisation, erreur de getaddrinfo : %s", gai_strerror(n));
     		return 0;
	}
	ressave = res;

	do {
		socketEcoute = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (socketEcoute < 0)
			continue;		/* error, try next one */

		setsockopt(socketEcoute, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
#ifdef BSD
		setsockopt(socketEcoute, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
#endif
		if (bind(socketEcoute, res->ai_addr, res->ai_addrlen) == 0)
			break;			/* success */

		close(socketEcoute);	/* bind error, close and try next one */
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL) {
     		perror("Initialisation, erreur de bind.");
     		return 0;
	}

	/* conserve la longueur de l'addresse */
	longeurAdr = res->ai_addrlen;

	freeaddrinfo(ressave);
	/* attends au max 4 clients */
	listen(socketEcoute, 4);
	printf("Création du serveur réussie sur %s.\n", service);

	return 1;
}

/* Attends qu'un client se connecte. */
int AttenteClient() {
	struct sockaddr *clientAddr;
	char machine[NI_MAXHOST];
	requete req;
	
	clientAddr = (struct sockaddr*) malloc(longeurAdr);

	/* On accepte la connexion avec le client puis on vérifie le login/password 
	 * envoyés dans la requête pour décider si on le laisse connecté ou si on le
	 * déconnecte en cas d'erreur/non correspondance du login et password.
	 */
	socketService = accept(socketEcoute, clientAddr, &longeurAdr);
	if (socketService == -1) {
		perror("AttenteClient, erreur de accept.");
		return 0;
	} else {
		req = Reception();
		printf("Reçu une requête de connexion : %d\n", req.type);
		VerificationConnexion(req);
	}
	free(clientAddr);
	/*
	 * Reinit buffer
	 */
	debutTampon = 0;
	finTampon = 0;

	return 1;
}

/* Vérifie si la combinaison login/password envoyée par le client correspond
 * à ce que connait le serveur dans son fichier utilisateurs.txt.
 */
int VerificationConnexion(requete req) {
	char contenufichier[51];
	char concatLogPass[51];
	FILE *f;
	reponse rep;

	/* S'il s'agit d'une requête de type BIND (connexion), on regarde
	 * dans le fichier contenant les utilisateurs pouvant le loguer auprès du serveur.
	 */
	if (req.type == BIND) {
		strcpy(concatLogPass, req.login);
		strcat(concatLogPass, ";");
		strcat(concatLogPass, req.password);
		strcat(concatLogPass, "\r\n");

		f = fopen("utilisateurs.txt", "r");
		if (f == NULL) {
			perror("Erreur lors de l'ouverture du fichier.");
			return -1;
		}

		while (fgets(contenufichier, 51, f)) {
			/* Si le login et password envoyés par le client correspondent à ce que connait le serveur,
			 * on envoie une réponse avec le code AUTH_OK et un message associé.
			 */
			if(strcmp(contenufichier, concatLogPass) == 0) {
				rep.code = AUTH_OK;
				strcpy(rep.data.message, "AuthOK");
				Emission(rep);
				puts("Client connecté.");
				break;
			}
		}

		/* Si le login et le password envoyés par le client ne correspond pas à ce que le serveur connait.
		 * On envoie une réponse contenant code AUTH_ERR et un message associé puis on le déconnecte. */
		if (strcmp(contenufichier, concatLogPass) != 0) {
			puts("Erreur d'authentification du client");
			rep.code = AUTH_ERR;
			strcpy(rep.data.message, "AuthError");
			Emission(rep);
			DeconnexionClient();
			AttenteClient();
		}
		fclose(f);
	} else {
		/* S'il ne s'agit pas d'une requête BIND, on envoie une réponse
		 * contenant un code REQ_ERR et un message associé car le serveur
		 * attendait une requête spécifique et différente que ce que le 
		 * client a envoyé à ce moment précis. 
		 */
		puts("\nRequête incorrecte.");
		rep.code = REQ_ERR;
		strcpy(rep.data.message, "RequestError");
		Emission(rep);
		DeconnexionClient();
	}

	return 0;
}

/* Reçoie une requête du client. */
requete Reception() {
	requete req;
	recv(socketService, &req, sizeof(requete), 0);
	return req;
}

/* Envoie une réponse au client. */
int Emission(reponse rep) {
	if (send(socketService, &rep, sizeof(reponse),0) == -1) {
        perror("Emission, probleme lors du send.");
        return 0;
	}
	printf("Envoie d'une réponse avec le code : %d\n", rep.code);
	return 1;
}

/* Ferme la connexion avec le client. */
void DeconnexionClient() {
	close(socketService);
	puts("Client déconnecté.\n");
}

/* Arrete le serveur. */
void Terminaison() {
	puts("Arrêt du serveur...");
	close(socketEcoute);
}

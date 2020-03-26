/**********************************************
 * 
 * Fichier contenant les fonctions du client qui sont essentielles à l'échange
 * entre celui-ci et le serveur.
 * 
 * Créé et programmé par Clément BRONGNIART.
 * 
 * *******************************************/

#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "client.h"
#include "structures.c"
#include "codes.c"

/* le socket client */
int socketClient;
int debutTampon;
int finTampon;

int Emission(requete req);
reponse Reception();
void Deconnexion();
void vidage_stdin(void);

/* Initialisation.
 * Connexion au serveur sur le service donné.
 */
int Connexion(char *login, char *password, char *service) {
	int n;
	struct addrinfo	hints, *res, *ressave;
	requete req;
	strcpy(req.login, login);
	strcpy(req.password, password);
	req.type = BIND;
	strcpy(req.data.message, "AuthReq");

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ( (n = getaddrinfo("localhost", service, &hints, &res)) != 0)  {
     		fprintf(stderr, "Initialisation, erreur de getaddrinfo : %s", gai_strerror(n));
     		return 0;
	}
	ressave = res;

	do {
		socketClient = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (socketClient < 0)
			continue;

		if (connect(socketClient, res->ai_addr, res->ai_addrlen) == 0) {
			// Emission d'un requête BIND avec les infos nécessaires au serveur.
			Emission(req);
			break;
		}
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL) {
     		perror("Initialisation, erreur de connect.");
     		return 0;
	}
	freeaddrinfo(ressave);
	return 1;
}

/* Affiche le menu principal après la phase de connexion. */
void AffichageMenuPrincipal() {
    printf("\033[1;34m");
    puts("\n******* Menu principal *******");
    puts("1. Menu Affichage");
    puts("2. Menu Création");
    puts("3. Menu Modification");
    puts("4. Menu Suppression");
	puts("5. Attribution de droits");
	puts("6. Déconnexion");
    printf("\033[0m");
    printf("\nChoisissez un menu : ");
}

/* On demande si l'utilisateur veut afficher toutes les données
 * ou seulement les données "obligatoires" des contacts.
 * Retourne 0 si 'O' ou 'o' sélectionné, retourne 1 si 'n' ou 'N'.
 */
int yesNo() {
	char r;

	if (r != 'O' && r != 'o' && r != 'n' && r != 'N') {
        r = getchar();
		vidage_stdin();
        while(r != 'n' && r != 'N' && r != 'o' && r != 'O') {
        	printf("Choix invalide, entrez de nouveau votre choix (o/O/n/N) : ");
        	r = getchar();
			vidage_stdin();
        }
    }

	if (r == 'o' || r == 'O')
		return 0;
	else if (r == 'n' || r == 'N')
		return 1;
}

/* Recoit une réponse envoyée par le serveur
 * et la retourne.
 */
reponse Reception() {
	reponse rep;
	recv(socketClient, &rep, sizeof(reponse), 0);

	/* Vérification en cas d'erreur de réception possible (rep.code = 0 et aucune data).
	 * Si on reçoit une réponse avec un code 0 (comportement anormal du serveur),
	 * on demande réémission des données.
	 */
	if (rep.code == 0)
		recv(socketClient, &rep, sizeof(reponse), 0);
	return rep;
}

/* Envoie une requête au serveur.
 * Retourne 1 si tout c'est bien passé.
 */
int Emission(requete req) {
	if (send(socketClient, &req, sizeof(requete),0) == -1) {
        perror("Emission, probleme lors du send.");
        return 0;
	}
	return 1;
}

/* Ferme la connexion. */
void Deconnexion() {
	close(socketClient);
}

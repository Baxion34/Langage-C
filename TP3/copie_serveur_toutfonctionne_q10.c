#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "serveur.h"

int extraitFichier(char *requete, char *tableauNomFichier, int tailleTableauNomFichier);
int extraitTypeRequete(char *requete, char *tableauTypeRequete);
unsigned long longueur_fichier(char *nomFichier);
int envoyerContenuFichierTexte(char *nomFichier);
int envoyerReponse200HTML(char *nomFichier);
int envoyerReponse404(char *nomFichier);
int envoyerReponse500(char *message);

#define Taille_fichier 1024

int main() {
	char *message = NULL;
	char Tab_fichier[Taille_fichier];
	char Tab_Requete[10];

	Initialisation();

	while(1) {
		int fini = 0;
		int i = 0;
		AttenteClient();

		while(!fini) {
			message = Reception();

			if(message != NULL) {
				printf("%s", message);

				/* Condition pour essayer de récupérer le nom du fichier
				 * uniquement dans la première ligne de la requête.
				 */
				if (i==0) {
					extraitFichier(message, Tab_fichier, Taille_fichier);
					extraitTypeRequete(message, Tab_Requete);
				}

				/* Si le message contient uniquement "\r\n" (fin de requête) */
				if (strcmp(message, "\r\n") == 0) {
					/* S'il s'agit du'une requête GET */
					if(strcmp(Tab_Requete, "GET") == 0) {
						/* Si le fichier demandé existe */
						if(access(Tab_fichier, F_OK ) != -1 ) {
							envoyerReponse200HTML(Tab_fichier);
							envoyerContenuFichierTexte(Tab_fichier);
						} else {
							envoyerReponse404(Tab_fichier);
						}
					} else {
						envoyerReponse500("Oops, something went wrong.");
					}
					fini = 1;
				}
				i++;
				free(message);
			}
		}
		TerminaisonClient();
		puts("Le client a fermé la connexion.\n");
	}
	return 0;
}

int extraitFichier(char *requete, char *tableauNomFichier, int tailleTableauNomFichier) {
	char *copie;
	int j = 0;
	
	if (requete == NULL)
		return 1;
	else {
		/* On copie la requête pour pouvoir la découper et récupérer le nom du fichier sans modifier la requête. */
		copie = malloc(sizeof(char) * (strlen(requete)+1));
		strcpy(copie, requete);
		/* On coupe et retient tous les caractères après la première apparition du caractère "/". */
		strtok(copie, "/");

		while(copie != NULL) {
			/* On coupe dès la première apparition d'un espace et on ne retient que ce qu'il y avait avant.
			 *On récupère donc le nom du fichier que l'on copie dans tableauNomFichier pour récupérer la valeur dans le main().
			 */
			if (j==1)
				strcpy(tableauNomFichier, copie);
			copie = strtok(NULL, " ");
			j++;
   		}
	}
	return 0;
}

int extraitTypeRequete(char *requete, char *tableauTypeRequete) {
	char *copie;
	int j = 0;
	
	if (requete == NULL)
		return 1;
	else {
		/* On copie la requête pour pouvoir la découper et récupérer le nom du fichier sans modifier la requête. */
		copie = malloc(sizeof(char) * (strlen(requete)+1));
		strcpy(copie, requete);
		/* On coupe et retient tous les caractères après la première apparition du caractère "/". */
		strtok(copie, " ");

		while(copie != NULL) {
			/* On coupe dès la première apparition d'un espace et on ne retient que ce qu'il y avait avant.
			 *On récupère donc le type de requête que l'on copie dans tableauTypeRequete pour récupérer la valeur dans le main().
			 */
			if (j==0)
				strcpy(tableauTypeRequete, copie);
			copie = strtok(NULL, " ");
			j++;
   		}
	}
	return 0;
}

unsigned long longueur_fichier(char *nomFichier) {
	FILE *f;
    unsigned long len = 0;

	/* Ouverture du fichier */
    f = fopen(nomFichier, "r");
	if (f == NULL) {
    	perror("Erreur lors de l'ouverture du fichier.");
		return -1;
	}

    /* On se place à la fin du fichier avec un offset de 0 octets. */
    if (fseek(f, 0, SEEK_END) != 0) {
		perror("Impossible d'atteindre la fin du fichier");
		return -1;
	}

    /* On stocke la valeur de l'indicateur de position dans une variable 
	 * pour retourner la taille du fichier.
	 */
    len = ftell(f);
    fclose(f);

	return len;
}

int envoyerContenuFichierTexte(char *nomFichier) {
	FILE *f;
	int longueur = longueur_fichier(nomFichier);
	char contenu[longueur+1];

	/* Ouverture du fichier. */
	f = fopen(nomFichier , "r");
	if (f == NULL) {
    	perror("Erreur lors de l'ouverture du fichier.");
		return -1;
	}

	/* Lecture du contenu du fichier et emission de celui-ci. */
	while (fgets(contenu, longueur, f)) {
		if (Emission(contenu)!=1) {
			printf("Erreur d'émission\n");
			return 1;
		}
	}
	fclose(f);
   
	return 0;
}

int envoyerReponse200HTML(char *nomFichier) {
	int longueur = longueur_fichier(nomFichier);
	char reponse[80] = "HTTP/1.0 200 OK\r\nContent-type : text/html\r\nContent-length : ";
	char conv_str[10];

	/* Conversion de la longueur du fichier (int) en string.
	 * Puis, concaténation de la longueur convertie en string
	 * avec la réponse en ajoutant '\r\n' pour pouvoir émettre.
	 */
	sprintf(conv_str, "%d", longueur);
	strcat(reponse, conv_str);
	strcat(reponse, "\r\n\r\n");

	/* Emission de la réponse complète. */
	Emission(reponse);

	return 0;
}

int envoyerReponse404(char *nomFichier) {
	int longueur_404 = longueur_fichier("404error.html");
	char reponse_404[80] = "HTTP/1.0 404 Not Found\r\nContent-type : text/html\r\nContent-length : ";
	char conv_str[10];
	char contenu_404[Taille_fichier];
	FILE *f;

	/* Ouverture du fichier */
	f = fopen("404error.html" , "r+");
	if (f == NULL) {
    	perror("Erreur lors de l'ouverture du fichier.");
		return -1;
	}

	/* Lecture du fichier HTML et ajout d'une ligne indiquant
	 * que la page demandée n'a pas été trouvée (en indiquant son nom).
	 */
	while (fgets(contenu_404, longueur_404, f)) {
		if (strcmp("<h1>404 Not Found</h1>\r\n", contenu_404) == 0) {
			fprintf(f, "<p>La page %s n'a pas ete trouvee.</p>\r\n</body>\r\n</html>\r\n", nomFichier);
		}
	}

	fclose(f);

	/* Conversion de la longueur du fichier (int) en string.
	 * Puis, concaténation de la longueur convertie en string
	 * avec la réponse en ajoutant '\r\n' pour pouvoir émettre.
	 */
	longueur_404 = longueur_fichier("404error.html");
	sprintf(conv_str, "%d", longueur_404);
	strcat(reponse_404, conv_str);
	strcat(reponse_404, "\r\n\r\n");

	/* Emission de la réponse HTTP 404 Not Found complète ainsi que
	 * le contenu de la page 404error.html.
	 */
	Emission(reponse_404);
	envoyerContenuFichierTexte("404error.html");

	return 0;
}

int envoyerReponse500(char *message) {
	int longueur_500 = longueur_fichier("500error.html");
	char reponse_500[80] = "HTTP/1.0 500 Server Error\r\nContent-type : text/html\r\nContent-length : ";
	char conv_str[10];
	char contenu_500[Taille_fichier];
	FILE *f;

	/* Ouverture du fichier */
	f = fopen("500error.html" , "r+");
	if (f == NULL) {
    	perror("Erreur lors de l'ouverture du fichier.");
		return -1;
	}

	/* Lecture du fichier HTML et ajout d'une ligne indiquant
	 * que la page demandée n'a pas été trouvée (en indiquant son nom).
	 */
	while (fgets(contenu_500, longueur_500, f)) {
		if (strcmp("<h1>500 Server Error</h1>\r\n", contenu_500) == 0) {
			fprintf(f, "<p>%s</p>\r\n</body>\r\n</html>\r\n", message);
		}
	}

	fclose(f);

	/* Conversion de la longueur du fichier (int) en string.
	 * Puis, concaténation de la longueur convertie en string
	 * avec la réponse en ajoutant '\r\n' pour pouvoir émettre.
	 */
	longueur_500 = longueur_fichier("500error.html");
	sprintf(conv_str, "%d", longueur_500);
	strcat(reponse_500, conv_str);
	strcat(reponse_500, "\r\n\r\n");

	/* Emission de la réponse HTTP 500 Server Error complète ainsi que
	 * le contenu de la page 500error.html.
	 */
	Emission(reponse_500);
	envoyerContenuFichierTexte("500error.html");

	return 0;
}
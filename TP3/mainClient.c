#include <stdio.h>
#include <stdlib.h>
#include "client.h"

int main() {
	char *message = NULL;

	/* Connexion au serveur localhost sur le port 13214 */
	if(Initialisation("localhost") != 1) {
		printf("Erreur d'initialisation\n");
		return 1;
	}

	/* Emission d'une requête HTTP GET vers le serveur localhost */
	if(Emission("GET /index.html HTTP/1.0\r\n")!=1) {
		printf("Erreur d'émission\n");
		return 1;
	}

	if(Emission("Host: localhost\r\n")!=1) {
		printf("Erreur d'émission\n");
		return 1;
	}

	if(Emission("\r\n")!=1) {
		printf("Erreur d'émission\n");
		return 1;
	}

	/* Réception de la réponse HTTP, 200 OK si tout s'est bien passé. */
	printf("\n");
	do {
		message = Reception();
		if(message != NULL) {
			printf("%s", message);
			free(message);
		}
	} while(message != NULL);

	Terminaison();
	return 0;
}

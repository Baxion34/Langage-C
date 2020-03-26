#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vidage_stdin(void);
char * lire_chaine_stdin(char *, int);

int main () {
    char lecture[500];
    char *texte[10];
    char *paide;
    int i,j;

    for(i=0; i<10; i++) {
        printf("Entrez une phrase: ");
        if(fgets(lecture, 500, stdin) == NULL) {
            printf("Erreur lors de la lecture de la ligne de texte.");
            return 1;
        }
        lire_chaine_stdin(lecture, 500);

        /* Réservation de la mémoire */
        texte[i] = malloc(strlen(lecture));
        if (texte[i] == NULL) { // Si l'allocation a échoué
            return 1; // On arrête immédiatement le programme
        }

        /* Copie des phrases de lecture vers texte. */
        if (texte[i])   // S'il y a assez de mémoire, faire : 
            strncpy(texte[i], lecture, strlen(lecture));
        else {
            printf("Pas assez de mémoire.\n");
            return 1;
        }
    }

    /* Affichage des phrases dans l'ordre d'entrée par l'utilisateur. */
    printf("Phrases dans l'ordre entrées par l'utilisateur :\n");
    for(i=0; i<10; i++) { 
        puts(texte[i]);
    }
    printf("\n");

    /* Inversion de l'ordre des phrases */
    printf("Phrases dans l'ordre inverse :\n");
    for(i=0, j=9; i<j; i++, j--) {
        paide = texte[i];
        texte[i] = texte[j];
        texte[j] = paide;
    }

    /* Affichage des phrases dans l'ordre inverse. */
    for(i=0; i<10; i++) { 
        puts(texte[i]);
    }
    free(*texte);   // Libération de la mémoire allouée.
    return 0;
}

void vidage_stdin(void) {
    int c ;
    do {
        c=getchar() ;
    } while ((c != '\n') && (c != EOF)) ;
}

char * lire_chaine_stdin(char * chaine, int taille) {
    char * resultat, *position;
    resultat = chaine;
    if (resultat != NULL) {
        position = strchr(chaine, '\n');
        if (position != NULL)
            *position = '\0';
        else
            vidage_stdin();
    }
    return resultat;
}
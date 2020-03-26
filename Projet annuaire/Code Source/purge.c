/**********************************************
 * 
 * Fichier contenant les fonctions servant purger le buffer
 * ou à remplacer un retour chariot dans une chaîne de caractères
 * par le caractère '\0'.
 * 
 * Créé par Clément BRONGNIART.
 * 
 * *******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Vide le buffer */
void vidage_stdin(void) {
    int c ;
    do {
        c=getchar() ;
    } while ((c != '\n') && (c != EOF)) ;
}

/* Remplace le caractère '\n' à la fin d'une chaîne de caractères par '\0'. */
char * lire_chaine_stdin(char * chaine, int taille) {
    char * resultat, *position;
    resultat = chaine;
    if (resultat != NULL) {
        position = strchr(chaine, '\n');
        if (position != NULL)
            *position = '\0';
    }
    return resultat;
}
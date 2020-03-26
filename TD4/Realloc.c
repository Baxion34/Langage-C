#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_carac ();

int main() {
    int nb_carac;

    nb_carac = str_carac();
    if (nb_carac != -1)
        printf("Nb de caractères dans la phrase : %d\n", nb_carac);
    else
        printf("Erreur: %d mémoire non allouée\n", nb_carac);
    
    return 0;
}

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

int str_carac () {
    int nb_carac;
    char *p;
    p = calloc(40, sizeof(char));   // Création d'un tableau de 40 caractères.

    if(p == NULL)
        return -1;
    printf("Entrez une phrase : ");
    fgets(p, 40, stdin);    // L'utilisateur entre une phrase qui est stockée dans le tableau
    
    lire_chaine_stdin(p, strlen(p));    // On remplace le newline par '\0'
    p = realloc(p, strlen(p));  // On modifie la taille du tableau selon la taille de la phrase entrée.

    nb_carac = strlen(p);   // On lit le nb de caractère dans la chaîne jusqu'au '\0'
    return nb_carac;
    free(p);
}
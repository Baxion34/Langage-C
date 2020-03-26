#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void vidage_stdin(void);
char * lire_chaine_stdin(char * chaine, int taille);

#define TAILLE 21

int main() {
    int i = 0;
    char Nom_fichier[TAILLE];
    int Nb_pers;
    char Nom_pers[TAILLE];
    /* Création d'un pointeur vers un fichier */
    FILE *fichier;

    printf("Entrez le nom du fichier : ");
    fgets(Nom_fichier,TAILLE,stdin);
    lire_chaine_stdin(Nom_fichier, TAILLE);

    printf("Entrez le nombre de personnes : ");
    scanf("%d", &Nb_pers);
    vidage_stdin();

    /* On ouvre le fichier et on choisie le mode "write" */
    fichier=fopen(Nom_fichier, "w");
    while(i < Nb_pers) {
        printf("Entrez le nom de la personne : ");
        fgets(Nom_pers,TAILLE,stdin);
        if (i == Nb_pers-1) {
            lire_chaine_stdin(Nom_pers,TAILLE);
            fputs(Nom_pers, fichier);
        } else {
            fputs(Nom_pers, fichier);
        }
        i++;
    }
    /* Fermeture du fichier ouvert précédemment */
    fclose(fichier);

    fichier=fopen(Nom_fichier, "r");
    i=1;
    printf("\n");
    printf("Contenu du fichier : \n");
    while(1) {
        /* Si on atteint la fin du fichier, on sort de la boucle */
        if(feof(fichier))
            break ;

        fscanf(fichier, "%s", Nom_pers);
        printf("L%d: %s\n", i, Nom_pers);
        i++;
    }
    /* Fermeture du fichier ouvert précédemment */
    fclose(fichier);

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
    }
    return resultat;
}
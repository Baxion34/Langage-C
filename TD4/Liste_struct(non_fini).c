#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct etudiant etudiant;
struct etudiant {
    etudiant *predecesseur;
    char nom[20];
    char prenom[20];
    int age;
    etudiant *successeur;
};

typedef struct Liste Liste;
struct Liste {
    etudiant *debut_liste;
    etudiant *fin_liste;
};

void vidage_stdin(void);
char * lire_chaine_stdin(char *, int);
Liste *initialisation();
void Afficher_liste(Liste *);

int main() {
    Liste *liste_etudiants = initialisation();
    etudiant *nouveau = malloc(sizeof(*nouveau));   //Allocation de mémoire pour un nouvel élève
    int termine = 0;
    int j = 1;

    /* Tant que termine = 0, on continue de faire tourner la boucle.*/
    while(!termine) {   // Fonctionne comme un booléen
        if (liste_etudiants == NULL || nouveau == NULL)
            exit(EXIT_FAILURE);
        
        printf("Nom de l'élève n°%d : ", j);
        fgets(nouveau->nom, 20, stdin);
        lire_chaine_stdin(nouveau->nom, 20);
        //vidage_stdin();

        if (strncmp(nouveau->nom, "fin", 20) == 0) {
            nouveau = NULL;
            break;
        }
        
        printf("Prénom de l'élève n°%d : ", j);
        fgets(nouveau->prenom, 20, stdin);
        lire_chaine_stdin(nouveau->prenom, 20);
        //vidage_stdin();

        do {
            printf("Âge de l'élève n°%d : ", j);
            scanf("%d", &nouveau->age);
            printf("\n");
            vidage_stdin();
        } while((nouveau->age < 0) && (nouveau->age > 100));

        nouveau->predecesseur = nouveau - 1;
        nouveau->successeur = nouveau + 1;

        if (j ==1) {
            nouveau->predecesseur = NULL;
            liste_etudiants->debut_liste = nouveau;
        }
       
        j++;
    }
    liste_etudiants->fin_liste = nouveau;
   
    /* Affichage de la liste */
    Afficher_liste(liste_etudiants);
    free(nouveau);
    return 0;
}

Liste *initialisation() {
    Liste *liste = malloc(sizeof(*liste));
    etudiant *student = malloc(sizeof(*student));
    liste->debut_liste = NULL;
    liste->fin_liste = NULL;
    student->predecesseur = NULL;
    student->successeur = NULL;

    if (liste == NULL || student == NULL)
        exit(EXIT_FAILURE);

    liste->debut_liste = student;

    return liste;
}

void Afficher_liste(Liste *liste) {
    if (liste == NULL)
        exit(EXIT_FAILURE);
    
    etudiant *actuel = liste->debut_liste;

    while (actuel != NULL) {
        printf("%s %s %d ans -> ", actuel->nom, actuel->prenom, actuel->age);
        actuel = actuel->successeur;
    }
    printf("\n");
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
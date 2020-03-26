#include <stdio.h>
#include <stdlib.h>
// Programme permettant d'entrer la dimension d'un tableau <= 50, le remplir par l'utilisateur et l'inverser sans aide d'un autre tableau.

int main() {
    int i, dim;
    int tempo=0;
    int tab[50];
    int *P1,*P2;

    /* Initialisation de la dimension du tableau */
    printf("Entrez la dimension du tableau (50 maxi): ");
    scanf("%d", &dim);
    if (dim <= 50) {
        /* Remplissage du tableau*/
        for(i=0; i < dim; i++) {
            printf("Entrez une valeur: ");
            scanf("%d",&tab[i]);
        }

        printf("Affichage du tableau : [ ");
        for(i=0; i < dim; i++) {
            printf("%d ", tab[i]);
        }
        printf("]\n");

        /* Inversion du tableau
        On place P2 à la fin de la chaine de nombres.*/
        for (P2 = tab; (*P2 != '\n') && (*P2 != '\0'); P2++)
            ;
        P2--;
        for (P1 = tab; P1 < P2; P1++, P2--) {
            tempo = *P1;
            *P1=*P2;
            *P2=tempo;
        }
        
        /*Inversion du tableau*/
        /*for(i=0, j=dim-1; i < j; i++, j--) {
            
            tempo = tab[i];
            tab[i] = tab[j];
            tab[j] = tempo;
        }*/
        printf("Affichage du tableau inversé : [ ");
        for(i=0; i < dim; i++) {
            printf("%d ", tab[i]);
        }
        printf("]\n");
    } else
        printf("Dimension entrée trop élevée.\n");
    return 0;
}
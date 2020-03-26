#include <stdio.h>
// Programme permettant d'entrer la dimension d'un tableau < 50, le remplir par l'utilisateur et l'inverser sans aide d'un autre tableau.

int main() {
    int i, j, dim;
    int tab[50];

    printf("Entrez la dimension du tableau (50 maxi): ");
    scanf("%d", &dim);
    if (dim <= 50) {
        for(i=0; i < dim; i++) {
            printf("Entrez une valeur: ");
            scanf("%d",&tab[i]);
        }
        printf("Affichage du tableau : [ ");
        for(i=0; i < dim; i++) {
            printf("%d ", tab[i]);
        }
        printf("]\n");

        /*Inversion du tableau*/
        for(i=0, j=dim-1; i < j; i++, j--) {
            int tempo;
            tempo = tab[i];
            tab[i] = tab[j];
            tab[j] = tempo;
        }
        printf("Affichage du tableau inversé : [ ");
        for(i=0; i < dim; i++) {
            printf("%d ", tab[i]);
        }
        printf("]\n");
    } else
        printf("Dimension entrée trop élevée.\n");
    return 0;
}
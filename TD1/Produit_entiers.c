#include <stdio.h>

int main(void) {
    int nb1, nb2, produit;
    char reponse='O';

    while(reponse == 'O') {
        printf("Saisissez un premier nombre: ");
        scanf("%d",&nb1);
        printf("Saisissez un second nombre: ");
        scanf("%d",&nb2);

        produit=nb1*nb2;
        printf("Produit de ces deux nombres: %d\n", produit);
        printf("Souhaitez-vous continuer à taper des nombres ? (O pour continuer)\n");
        scanf(" %c", &reponse); // Espace pour éviter le "problème" avec %c et scanf.
    }
    return 0;
}
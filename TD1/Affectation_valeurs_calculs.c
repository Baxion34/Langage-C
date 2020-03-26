#include <stdio.h>

int main(void) {
    int nb1, nb2;
    int somme, produit, soustract, div, div_reste;

    nb1=3;
    nb2=15;

    somme = nb1 + nb2;
    produit = nb1 * nb2;
    if (nb1<nb2) {
        soustract=nb2-nb1;
        div=nb2/nb1;
        div_reste=nb2%nb1;
    } else {
        soustract=nb1-nb2;
        div=nb1/nb2;
        div_reste=nb1%nb2;
    }

    printf("\nValeur de la somme de ces nombres: %d\n", somme);
    printf("Valeur de la produit de ces nombres: %d\n", produit);
    printf("Valeur de la soustraction de ces nombres: %d\n", soustract);
    printf("Valeur de la division entière de ces nombres: %d\n", div);
    printf("Reste de la division entière de ces nombres: %d\n", div_reste);
    return 0;
}
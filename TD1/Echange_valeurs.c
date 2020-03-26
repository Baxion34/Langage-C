#include <stdio.h>

int main(void) {
    int nb1, nb2, nb_inter;

    nb1=3;
    nb2=15;
    printf("Valeur de nb1 avant échange: %d\n",nb1);
    printf("Valeur de nb2 avant échange: %d\n",nb2);

    nb_inter=nb1;
    nb1=nb2;
    nb2=nb_inter;

    printf("Valeur de nb1 après échange: %d\n",nb1);
    printf("Valeur de nb2 après échange : %d\n",nb2);
    return 0;
}
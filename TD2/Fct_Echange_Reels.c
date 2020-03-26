#include <stdio.h>
// Programme permettant l'échange des valeurs de 2 variables réelles entrées par l'utilisateur (en virgule flottante) grâce à une fonction.
void echanger(float, float); // Pré-déclaration de la fonction

int main() {
    float nb1, nb2;

    printf("Entrez un premier réel: ");
    scanf("%fe%d",&nb1);

    printf("Entrez un second réel: ");
    scanf("%fe%d",&nb2);

    printf("Valeur de nb1: %f\n",nb1);
    printf("Valeur de nb2: %f\n",nb2);
    echanger(nb1,nb2);
    
    return 0;
}

void echanger(float nb1, float nb2) {
    float temp;
    temp=nb1;
    nb1=nb2;
    nb2=temp;
    printf("Valeur de nb1 après échange: %f\n",nb1);
    printf("Valeur de nb2 après échange: %f\n",nb2);
}
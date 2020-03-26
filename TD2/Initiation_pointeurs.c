#include <stdio.h>
// Programme d'initiation aux pointeurs en attribuant l'adresse de la variable i à un pointeur et en modifiant la valeur de i en passant par ce pointeur.
int main() {
    int i, *p=NULL;

    i = 50;
    p=&i;
    printf("Valeur de i : %d\n", i);
    *p+=5;
    printf("Valeur de i modifiée en passant par le pointeur: %d\n", *p);
}
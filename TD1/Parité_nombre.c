#include <stdio.h>

int main(void) {
    int nombre;

    printf("Entrez un nombre: ");
    if (scanf("%d",&nombre) == 1) {
        if(nombre%2 == 0)
            printf("Le nombre entré est pair\n");
        else 
            printf("Le nombre entré est impair\n");
    } else {
        printf("Il ne s'agit pas d'un nombre\n");
    }
    return 0;
}
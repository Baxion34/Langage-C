#include <stdio.h>
#include <math.h>

int main(void) {
    int nombre_total, somme, puissance, nombre;
    somme=0;
    printf("Veuillez entrer le nombre d'entiers dans la somme pondérée: ");
    scanf("%d", &nombre_total);

    for(int i=0; i<nombre_total; i++) {
        printf("Veuillez entrer un nombre: ");
        scanf("%d", &nombre);
        printf("Veuillez entrer la puissance de ce nombre: ");
        scanf("%d", &puissance);

        somme=somme+(pow(nombre,puissance)); //math.h fonctionne pas ???
    }
    printf("Le résultat de la somme pondérée est : %d\n", somme);
    return 0;
}
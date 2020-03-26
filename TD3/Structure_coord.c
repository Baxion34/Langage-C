#include <stdio.h>
// Programme permettant de calculer l'aire d'un rectangle à partir des coordonnées de 2 points diagonaux entrées par l'utilisateur.

typedef struct {
    int x;
    int y;
} coord;

typedef struct {
    coord A;
    coord B;
} rectangle;

int main() {
    rectangle rect;
    int largeur, longueur;
    unsigned int aire;

    printf("Entrez les coordonnées de A\nx=");
    scanf("%d", &rect.A.x);
    printf("y=");
    scanf("%d", &rect.A.y);
    printf("Entrez les coordonnées de B\nx=");
    scanf("%d", &rect.B.x);
    printf("y=");
    scanf("%d", &rect.B.y);

    largeur = rect.B.y - rect.A.y;
    longueur = rect.B.x - rect.A.x;
    aire = largeur * longueur;
    printf("Aire du rectangle: %d\n",aire);
    
    return 0;
}
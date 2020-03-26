#include <stdio.h>
#include <stdlib.h>

int main () {
    FILE *f;
    int len;

    f = fopen("exemple.txt", "r");
    // On se place à la fin du fichier avec un offset de 0 octets.
    fseek(f, 0, SEEK_END);

    // On stocke la valeur de l'indicateur de position dans une variable pour calculer la taille du fichier.
    len = ftell(f);
    fclose(f);
    
    printf("Taille totale du fichier exemple.txt = %d octets\n", len);
  
    return 0;
}
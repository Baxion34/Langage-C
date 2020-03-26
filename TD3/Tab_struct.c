#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titre[20];
    int prix;
} livre;

int main() {
    livre biblio[5];
    char cbuf;  // Caractère restant dans le buffer
    int i;

    for(i=0; i<5; i++) {
        printf("Entrez le titre du livre (# pour arrêter de taper): ");
        fgets(biblio[i].titre,20,stdin);
    
        /* Conditions utilisées pour supprimer le newline à la fin de fgets() : */
        int chlen = strlen(biblio[i].titre);   // Lecture de la longueur de la chaîne
        if (biblio[i].titre[chlen - 1] == '\n')
            biblio[i].titre[chlen - 1] = '\0';  // On remplace le newline avec \0 pour le supprimer.
        
        if ((biblio[i].titre[0] =='#') && (biblio[i].titre[1] == '\0'))
            break;
        printf("Entrez son prix: ");
        scanf("%d", &biblio[i].prix);
        while ((cbuf = getchar ()) != '\n' && cbuf != EOF); // Vidage du buffer
        printf("\n");
    }
    
    printf("il y a %d livre(s) dans la bibliothèque : \n",i);
    for(i=0; i<5; i++) {
        if ((biblio[i].titre[0] =='#') && (biblio[i].titre[1] == '\0')) 
                break;
        else
            printf("\"%s\" à %d €\n", biblio[i].titre, biblio[i].prix);
        
    }
    return 0;
}
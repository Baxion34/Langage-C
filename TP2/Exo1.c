#include <stdlib.h>
#include <stdio.h>

int main() {
    /* Initialisation de tableaux pouvant contenir 80 caractères */
    char cNom[81];
    char cArticle[81];
    /* Initialisation d'entiers pour les nombres, prix, le produit entre le nb et le prix ainsi que le numéro de la ligne */
    int iNombre, iPrix, i;
    int iPrix_produit;
    i = 1;
    /* Création d'un pointeur vers un fichier */
    FILE *fichier;

    /* On ouvre le fichier et on choisie le mode "read" */
    fichier=fopen("fichier.txt", "r");
    while(1) {
        /* Si on atteint la fin du fichier, on sort de la boucle */
        if(feof(fichier))
            break;
        
        /* Séparation de la ligne en 4 champs stockés dans les 2 tableaux et les 2 entiers iNombre et iPrix. */
        fscanf(fichier, "%s %s %d %d", cNom, cArticle, &iNombre, &iPrix);
        iPrix_produit = iNombre * iPrix;
        printf("L%d: %s | %s | %d\n", i, cNom, cArticle, iPrix_produit);
        i++;
    }
    /* Fermeture du fichier ouvert précédemment */
    fclose(fichier);

    return 0;
}
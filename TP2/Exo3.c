#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f_in, *f_out;
    char stock;

    f_in=fopen("exemple.txt", "r");
    f_out=fopen("copie.txt", "w");

    /* On lit le premier fichier caractère par caractère à chaque passage de boucle en stockant le caractère actuel dans
    une variable pour l'écrire dans le second fichier dans un même passage de boucle.*/
    while ((stock=fgetc(f_in)) != EOF) {    // Permet de lire le fichier input jusqu'à la fin du fichier sans inclure le caractère ÿ qui indique le EOF.
        /*if(feof(f_in))
            break ;*/
        fputc(stock, f_out);
    }
    fclose(f_in);
    fclose(f_out);

    return 0;
}
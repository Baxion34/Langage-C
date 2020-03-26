#include <stdio.h>
#include <string.h>

void inversion (char[], char[], int);

#define TAILLE 21

int main() {
    char ch[TAILLE];
    char chinverse[TAILLE];

    printf("Entrez une chaîne de caractères: ");
    fgets(ch,TAILLE,stdin);
	inversion(ch, chinverse, TAILLE);
	
	return 0;
}

void inversion (char* tab1, char* tab2, int longueur) {
	int i=0;
    int j=0;
	int lenmax=strlen(tab1)-1;
	for (i; i < lenmax; i++) {
		tab2[i]=tab1[lenmax-i-1];
		if (tab1[i] == tab2[i])
			j++;
	}
	if(j == lenmax)
		printf("La chaîne choisie est un palindrome.\nChaîne inverse: %s\n",tab2);
	else
		printf("La chaîne choisie n'est pas un palindrome.\nChaîne inverse: %s\n",tab2);
}
#include <stdio.h>
typedef union
{
    unsigned long complete;
    unsigned char octets[4];
} conversion;
/*********************************************
Vidage du buffer d’entrée
*********************************************/
void vidage_stdin(void)
{
    int c ;
    do {
    c=getchar() ;
    } while ((c != '\n') && (c != EOF)) ;
}

int main()
{
    conversion adr_ip, masque;
    conversion adr_reseau, adr_machine;
    int i0, i1, i2, i3; /* utilisées pour les saisies */
    int res; /* retour du scanf */
    /* affichage des adresses des membres */
    printf("Adresse de adr_ip.complete %p\n", &adr_ip.complete);
    printf("Adresse de adr_ip.octets[0] %p\n", &adr_ip.octets[0]);
    printf("Adresse de adr_ip.octets[1] %p\n", &adr_ip.octets[1]);
    printf("Adresse de adr_ip.octets[2] %p\n", &adr_ip.octets[2]);
    printf("Adresse de adr_ip.octets[3] %p\n", &adr_ip.octets[3]);
    printf("\n");
    /* Adresse IP -
    Note : on lit les octets à l'envers car on travaille sur un
    processeur little endian. Sur un processeur big endian il
    faudrait les lire dans l'autre sens.
    */
    do
    {
        printf("Entrez une adresse IP (exemple : 134.157.15.38):");
        
        res = scanf("%d.%d.%d.%d", &i3, &i2, &i1, &i0);
        vidage_stdin();
    }
    while ((res!=4) || (i0 < 0) || (i0 > 255) || (i1 < 0) || (i1 > 255) ||
    (i2 < 0) || (i2 > 255) || (i3 < 0) || (i3 > 255));
    /* affectation dans les octets de l'union */
    adr_ip.octets[0] = i0;
    adr_ip.octets[1] = i1;
    adr_ip.octets[2] = i2;
    adr_ip.octets[3] = i3;
    /* affichage du membre int sur 32 bits */
    printf("adr_ip.complete=%lx \n\n", adr_ip.complete);
    /* masque */
    do
    {
        printf("Entrez un masque (exemple : 255.255.0.0):");
        res = scanf("%d.%d.%d.%d", &i3, &i2, &i1, &i0);
        vidage_stdin();
    }
    while ((res!=4) || (i0 < 0) || (i0 > 255) || (i1 < 0) || (i1 > 255) ||
    (i2 < 0) || (i2 > 255) || (i3 < 0) || (i3 > 255));

    /* affectation dans les octets de l'union */
    masque.octets[0] = i0;
    masque.octets[1] = i1;
    masque.octets[2] = i2;
    masque.octets[3] = i3;
    /* affichage du membre int sur 32 bits */
    printf("masque.complete=%lx \n\n", masque.complete);
    /* calcul de l'adresse du reseau sur les 4 octets */
    adr_reseau.complete = adr_ip.complete & masque.complete;
    /* calcul de l'adresse de la machine sur les 4 octets */
    adr_machine.complete = adr_ip.complete & ~masque.complete;
    /* le ~ permet de prendre l’inverse soit 0.0.255.255 dans notre exemple */
    printf("l'adresse ");
    printf("%d.%d.", adr_ip.octets[3], adr_ip.octets[2]);
    printf("%d.%d", adr_ip.octets[1], adr_ip.octets[0]);
    printf(" est découpée en :\n");
    printf("Partie réseau : ");
    printf("%d.%d.", adr_reseau.octets[3], adr_reseau.octets[2]);
    printf("%d.%d\n", adr_reseau.octets[1], adr_reseau.octets[0]);
    printf("Partie machine : ");
    printf("%d.%d.", adr_machine.octets[3], adr_machine.octets[2]);
    printf("%d.%d\n", adr_machine.octets[1], adr_machine.octets[0]);
    return 0;
}
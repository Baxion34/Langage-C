#include <stdio.h>
/* Programme découpant une adresse IP entrée par
l'utilisateur en une partie réseau et une partie machine.*/

typedef union {
    unsigned int ip;
    unsigned char octets[4];
} conversion;

int main() {
    conversion adr_ip, s_masque, adr_reseau, adr_machine;

    printf("Entrez une adresse IP: ");
    if(scanf("%d.%d.%d.%d", &adr_ip.octets[0], &adr_ip.octets[1], &adr_ip.octets[2], &adr_ip.octets[3]) != 4) {
        printf("Adresse IP mal écrite.\n");
        return 1;
    }

    printf("Entrez le masque de sous-réseau: ");
    if(scanf("%d.%d.%d.%d", &s_masque.octets[0], &s_masque.octets[1], &s_masque.octets[2], &s_masque.octets[3]) != 4) {
        printf("Masque de sous-réseau mal écrit.\n");
        return 1;
    }

    for (int i=0; i < sizeof(adr_ip.octets); i++) {
        adr_reseau.octets[i] = adr_ip.octets[i] & s_masque.octets[i];
        if(i != 3)
            printf("%d.", adr_ip.octets[i]);
        else
            printf("%d\n", adr_ip.octets[i]);
    }
    printf("%", adr_ip.ip);

    // Affichage
    /* for (int i=0; i < sizeof(adr_ip.octets); i++) {
        if(i != 3)
            printf("%d.", adr_ip.octets[i]);
        else
            printf("%d\n", adr_ip.octets[i]);
    } */
    
    return 0;
}
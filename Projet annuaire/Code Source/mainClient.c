/**********************************************
 * 
 * Fichier contenant le fonctionnement global (main)
 * du client annuaire.
 * 
 * Créé et programmé par Clément BRONGNIART.
 * 
 * *******************************************/
#include "client.h"

int main() {
    reponse reponseC;
    requete reqDeconnexion;
    user utilisateur;
    int choix1;
    int retourRequete;
    int fini = 0;

    puts("******* Connexion *******");
    puts("Veuillez vous connecter…");
    printf("Login : ");
    fgets(utilisateur.login, sizeof(utilisateur.login), stdin);
    lire_chaine_stdin(utilisateur.login, sizeof(utilisateur.login));

	printf("Mot de passe : ");
    fgets(utilisateur.password, sizeof(utilisateur.password), stdin);
    lire_chaine_stdin(utilisateur.password, sizeof(utilisateur.password));

    Connexion(utilisateur.login, utilisateur.password, "13214");
    reponseC = Reception();

    // Si le serveur nous répond que l'authentification est OK :
    if (reponseC.code == AUTH_OK) {
        puts("Connexion avec le serveur réussie.");

        while (!fini) {
            do {
                AffichageMenuPrincipal();
                scanf("%d", &choix1);
                vidage_stdin();
                printf("\n");
            
                /* Utilisation de fonctions selon le choix sélectionné. */
                switch(choix1) {
                    case 1:
                        retourRequete = EnvoyerRequeteAffichage(utilisateur.login, utilisateur.password);
                        break;
                    case 2:
                        retourRequete = EnvoyerRequeteCreation(utilisateur.login, utilisateur.password);
                        break;
                    case 3:
                        retourRequete = EnvoyerRequeteModification(utilisateur.login, utilisateur.password);
                        break;
                    case 4:
                        retourRequete = EnvoyerRequeteSuppression(utilisateur.login, utilisateur.password);
                        break;
                    case 5:
                        retourRequete = EnvoyerRequeteDroits(utilisateur.login, utilisateur.password);
                        puts("Fonction non implémentée par manque de temps...");
                        break;
                    case 6:
                        fini = 1;
                        retourRequete = 0;

                        // Création d'une requête de Déconnexion.
                        reqDeconnexion.type = UNBIND;
                        strcpy(reqDeconnexion.login, utilisateur.login);
                        strcpy(reqDeconnexion.password, utilisateur.password);
                        strcpy(reqDeconnexion.data.message, "DisconnectReq");
                        Emission(reqDeconnexion);

                        reponseC = Reception();
                        if (reponseC.code == DISCONNECT_CONFIRM) {
                            puts("Déconnexion...");
                            Deconnexion();
                        } else {
                            puts("Erreur lors de la déconnexion");
                        }
                        break;
                    default:
                        puts("Ce choix n'existe pas.");
                        break;
                }
            // retourRequete utile pour les choix "retour en arrière" des sous-menus suivants.
            } while (choix1 != 1 && choix1 != 2 && choix1 != 3 && choix1 != 4 && choix1 != 5 && choix1 != 6 || retourRequete == 1);
        }
    } else if (reponseC.code == AUTH_ERR) {
        puts("Connexion échouée.");
        Deconnexion();
    }
    return 0;
}
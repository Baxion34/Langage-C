/**********************************************
 * 
 * Fichier contenant le fonctionnement global (main)
 * du serveur annuaire.
 * 
 * Créé et programmé par Clément BRONGNIART.
 * 
 * *******************************************/

#include "serveur.h"

int main() {
    requete req;
    reponse rep;

    // Initialisation et démarrage du serveur sur le port 13214
    InitialisationAvecService("13214");

    while(1) {
        int fini = 0;

        AttenteClient();

        while(!fini) {
            req = Reception();

            // Séparation des traitements des requêtes selon leur type.
            if (req.type == CREATE_CONTACT || req.type == CREATE_CONTACTSBOOK || req.type == CREATE_USER || req.type == CREATE_RIGHTS) {
                printf("\nReçu une requête de type CREATE : %d\n", req.type);
                traiterRequeteCREATE(req);
            } else if (req.type == UPDATE_CONTACT || req.type == UPDATE_USER) { 
                printf("\nReçu une requête de type UPDATE : %d\n", req.type);
                traiterRequeteUPDATE(req);
            } else if (req.type == DELETE_CONTACT || req.type == DELETE_CONTACTSBOOK || req.type == DELETE_USER || req.type == DELETE_RIGHTS) { 
                printf("\nReçu une requête de type DELETE : %d\n", req.type);
                traiterRequeteDELETE(req);
            } else if (req.type == GET_CONTACT || req.type == GET_CONTACTSBOOK || req.type == GET_RIGHTS) { 
                printf("\nReçu une requête de type GET : %d\n", req.type);
                traiterRequeteGET(req);
            } else if (req.type == UNBIND) {
                printf("\nReçu une requête de déconnexion : %d\n", req.type);
                rep.code = DISCONNECT_CONFIRM;
                strcpy(rep.data.message, "DisconnectConfirmed");
                Emission(rep);
                DeconnexionClient();
                fini = 1;
            }
        }
    }
    return 0;
}
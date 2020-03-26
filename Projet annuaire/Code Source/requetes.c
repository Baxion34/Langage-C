/**********************************************
 * 
 * Fichier contenant les fonctions servant à effectuer et
 * émettre les requêtes du client annuaire.
 * 
 * 
 * Créé et programmé par Clément BRONGNIART.
 * 
 * *******************************************/
#include "client.h"

/* Fonction permettant d'afficher un sous-menu Affichage après le menu principal
 * puis d'envoyer une requête au serveur correspondant au choix de l'utilisateur.
 */
int EnvoyerRequeteAffichage(char *login, char *password) {
    requete req;
    reponse rep;
    int choix2;
    int i;
    int input;
    strcpy(req.login, login);
    strcpy(req.password, password);

    if (strcmp(req.login, "admin") != 0) {
        do {
            printf("\033[1;34m");
            puts("******* Menu Affichage *******");
            puts("1. Contact");
            puts("2. Annuaire");
            puts("3. Retour en arrière");
            
            printf("\033[0m");
            printf("\nChoisissez un élément : ");
            scanf("%d", &choix2);
            vidage_stdin();

            switch(choix2) {
                case 1: // Affiche un contact de l'annuaire de l'utilisateur courant.
                    req.type = GET_CONTACT;

                    // On envoie le nom et prénom du contact à chercher dans l'annuaire.         
                    printf("\nNom du contact à chercher : ");
                    fgets(req.data.cont.Nom, sizeof(req.data.cont.Nom), stdin);
                    lire_chaine_stdin(req.data.cont.Nom, sizeof(req.data.cont.Nom));

                    printf("Prénom du contact à chercher : ");
                    fgets(req.data.cont.Prenom, sizeof(req.data.cont.Prenom), stdin);
                    lire_chaine_stdin(req.data.cont.Prenom, sizeof(req.data.cont.Prenom));

                    Emission(req);
                    rep = Reception();

                    // Si le contact est trouvé, on affiche les infos ::
                    if (rep.code == REQ_OK) {
                        puts("\n\033[1;34m***** Contact trouvé ! *****\033[0m");
                        printf("Nom : %s\n", rep.data.cont.Nom);
                        printf("Prénom : %s\n", rep.data.cont.Prenom);
                        printf("Mail : %s\n", rep.data.cont.Mail);

                        printf("\nSouhaitez-vous afficher des données supplémentaires ? (o/O/n/N) : ");
                        if (yesNo() == 0) {
                            printf("\nTél portable : %s\n", rep.data.cont.NumPortable);
                            printf("Adresse postale : %s\n", rep.data.cont.AdressePostale);
                            printf("Date de naissance : %s\n", rep.data.cont.DateNaissance);
                            printf("Remarques : %s\n", rep.data.cont.Remarques);
                        }
                    // Sinon, il se peut que le contact ou que l'annuaire n'ait pas été trouvé.
                    } else if (rep.code == CONTACT_NOT_FOUND) {
                        puts("Ce contact n'a pas été trouvé.");
                    } else if (rep.code == BOOK_NOT_FOUND) {
                        puts("L'utilisateur actuel ne possède pas d'annuaire.");
                    }
                    return 0;
                case 2: // Affiche tous les contacts dans l'annuaire de l'utilisateur courant.
                    req.type = GET_CONTACTSBOOK;
                    strcpy(req.data.message, "ReqCBook");
                    Emission(req);         

                    rep = Reception();
                    printf("\nSouhaitez-vous afficher des données supplémentaires ? (o/O/n/N) : ");
                    input = yesNo();
                    
                    if (rep.code == REQ_OK) {
                        // Affichage des infos des contacts de l'annuaire de l'utilisateur.
                        for (int i = 0; i <= rep.data.CBook.taille; i++) {
                            printf("\nNom : %s\n", rep.data.CBook.Tableau[i].Nom);
                            printf("Prénom : %s\n", rep.data.CBook.Tableau[i].Prenom);
                            printf("Mail : %s\n", rep.data.CBook.Tableau[i].Mail);
                            if (input == 0) {
                                printf("Tél portable : %s\n", rep.data.CBook.Tableau[i].NumPortable);
                                printf("Adresse postale : %s\n", rep.data.CBook.Tableau[i].AdressePostale);
                                printf("Date de naissance : %s\n", rep.data.CBook.Tableau[i].DateNaissance);
                                printf("Remarques : %s\n", rep.data.CBook.Tableau[i].Remarques);
                            }
                        }
                    } else if (rep.code == BOOK_NOT_FOUND) {
                        puts("Cet utilisateur ne possède pas d'annuaire.");
                    }
                    return 0;
                case 3: //retour au menu principal
                    return 1;
                default:
                    puts("Ce choix n'existe pas.\n");
                    break;
            }
        } while (choix2 != 1 && choix2 != 2 && choix2 != 3);
    } else {
        puts("Accès refusé en tant qu'administrateur.");
    }
}

/* Fonction permettant d'afficher un sous-menu Création après le menu principal
 * puis d'envoyer une requête au serveur correspondant au choix de l'utilisateur.
 */
int EnvoyerRequeteCreation(char *login, char *password) {
    requete req;
    reponse rep;
    int choix2;
    int i;
    strcpy(req.login, login);
    strcpy(req.password, password);

    /* Création de différents choix (et requêtes) dans le sous-menu selon si le login
     * de l'utilisateur connecté est admin ou non.
     */
    do {
        printf("\033[1;34m");
        puts("******* Menu Création *******");
        puts("1. Contact");
        puts("2. Annuaire");
        puts("3. Utilisateur");
        puts("4. Retour en arrière");
            
        printf("\033[0m");
        printf("\nChoisissez un élément : ");
        scanf("%d", &choix2);
        vidage_stdin();

        switch(choix2) {
            case 1: // Création d'un contact dans l'annuaire de l'utilisateur courant.
                if (strcmp(req.login, "admin") != 0) {
                    req.type = CREATE_CONTACT;
                    puts("\nVeuillez remplir les champs obligatoire ci-dessous : ");
                    // Boucles demandant de remplir les champs Nom, Prénom et Mail d'un contact à tout prix car ils sont obligatoires.
                    do {
                        printf("Nom du contact : ");
                        fgets(req.data.cont.Nom, sizeof(req.data.cont.Nom), stdin);
                        lire_chaine_stdin(req.data.cont.Nom, sizeof(req.data.cont.Nom));
                    } while(strcmp(req.data.cont.Nom, "")==0);
                    
                    do {
                        printf("Prénom du contact : ");
                        fgets(req.data.cont.Prenom, sizeof(req.data.cont.Prenom), stdin);
                        lire_chaine_stdin(req.data.cont.Prenom, sizeof(req.data.cont.Prenom));
                    } while(strcmp(req.data.cont.Prenom, "")==0);
                    
                    do {
                        printf("Mail du contact : ");
                        fgets(req.data.cont.Mail, sizeof(req.data.cont.Mail), stdin);
                        lire_chaine_stdin(req.data.cont.Mail, sizeof(req.data.cont.Mail));
                    } while(strcmp(req.data.cont.Mail, "")==0);

                    printf("\nSouhaitez-vous ajouter des données supplémentaires ? (o/O/n/N) : ");
                    if (yesNo() == 0) {
                        /* On peut remplir chaque champ quand il l'est demandé ou on peut également passer un champ en le laissant vide
                         * ce qui va le remplir avec "Non renseigné".
                         */
                        printf("Numéro de tél. portable du contact : ");
                        fgets(req.data.cont.NumPortable, sizeof(req.data.cont.NumPortable), stdin);
                        lire_chaine_stdin(req.data.cont.NumPortable, sizeof(req.data.cont.NumPortable));

                        printf("Adresse postale du contact : ");
                        fgets(req.data.cont.AdressePostale, sizeof(req.data.cont.AdressePostale), stdin);
                        lire_chaine_stdin(req.data.cont.AdressePostale, sizeof(req.data.cont.AdressePostale));

                        printf("Date de naissance du contact : ");
                        fgets(req.data.cont.DateNaissance, sizeof(req.data.cont.DateNaissance), stdin);
                        lire_chaine_stdin(req.data.cont.DateNaissance, sizeof(req.data.cont.DateNaissance));

                        printf("Remarques à propos du contact : ");
                        fgets(req.data.cont.Remarques, sizeof(req.data.cont.Remarques), stdin);
                        lire_chaine_stdin(req.data.cont.Remarques, sizeof(req.data.cont.Remarques));

                        if (strcmp(req.data.cont.NumPortable, "")==0)
                            strcpy(req.data.cont.NumPortable, "Non renseigné");
                        if (strcmp(req.data.cont.AdressePostale, "")==0)
                            strcpy(req.data.cont.AdressePostale, "Non renseigné");
                        if (strcmp(req.data.cont.DateNaissance, "")==0)
                            strcpy(req.data.cont.DateNaissance, "Non renseigné");
                        if (strcmp(req.data.cont.Remarques, "")==0)
                            strcpy(req.data.cont.Remarques, "Non renseigné");
                    } else if (yesNo() == 1) {
                        // Si on passe les champs secondaires, ils sont remplis avec "Non renseigné" par défaut.
                        strcpy(req.data.cont.NumPortable, "Non renseigné");
                        strcpy(req.data.cont.AdressePostale, "Non renseigné");
                        strcpy(req.data.cont.DateNaissance, "Non renseigné");
                        strcpy(req.data.cont.Remarques, "Non renseigné");
                    }

                    Emission(req);
                    rep = Reception();

                    if (rep.code == REQ_OK) {
                        puts("Contact créé avec succès.");
                    } else if (rep.code == BOOK_NOT_FOUND) {
                        puts("Veuillez créer un annuaire avant de créer un contact.");
                    }
                    return 0;
                } else {
                    puts("Accès refusé en tant qu'administrateur.");
                    return 1;
                }
            case 2: // Création d'un annuaire pour l'utilisateur courant.
                if (strcmp(req.login, "admin") != 0) {
                    req.type = CREATE_CONTACTSBOOK;
                    Emission(req);
                    rep = Reception();

                    if (rep.code == REQ_OK) {
                        puts("Annuaire créé avec succès.");
                    } else if (rep.code == BOOK_EXISTS) {
                        puts("Un annuaire existe déjà pour cet utilisateur.");
                    }
                    return 0;
                } else {
                    puts("Accès refusé en tant qu'administrateur.");
                    return 1;
                }
            case 3: // Création d'un utilisateur (+ son annuaire).
                if (strcmp(req.login, "admin") == 0) {
                    req.type = CREATE_USER;

                    printf("\nNom du nouvel utilisateur : ");
                    fgets(req.data.utilisateur.login, sizeof(req.data.utilisateur.login), stdin);
                    lire_chaine_stdin(req.data.utilisateur.login, sizeof(req.data.utilisateur.login));

                    printf("Mot de passe du nouvel utilisateur : ");
                    fgets(req.data.utilisateur.password, sizeof(req.data.utilisateur.password), stdin);
                    lire_chaine_stdin(req.data.utilisateur.password, sizeof(req.data.utilisateur.password));

                    Emission(req);
                    rep = Reception();

                    if (rep.code == REQ_OK) {
                        puts("Utilisateur créé avec succès.");
                    } else if (rep.code == USER_EXISTS) {
                        puts("Cet utilisateur existe déjà.");
                    } else if (rep.code == REQ_ERR) {
                        puts("Erreur de traitement du côté du serveur.");
                    }
                } else {
                    puts("\nVous n'avez pas les droits nécessaires pour effectuer cette requête.");
                }
                return 0;
            case 4: //retour au menu principal
                return 1;
            default:
                puts("Ce choix n'existe pas.\n");
                break;
        }
    } while (choix2 != 1 && choix2 != 2 && choix2 != 3 && choix2 != 4);
}

/* Fonction permettant d'afficher un sous-menu Modification après le menu principal
 * puis d'envoyer une requête au serveur correspondant au choix de l'utilisateur.
 */
int EnvoyerRequeteModification(char *login, char *password) {
    requete req;
    reponse rep;
    int choix2;
    int i;
    strcpy(req.login, login);
    strcpy(req.password, password);

    do {
        printf("\033[1;34m");
        puts("******* Menu Modification *******");
        puts("1. Contact");
        puts("2. Utilisateur");
        puts("3. Retour en arrière");
            
        printf("\033[0m");
        printf("\nChoisissez un élément : ");
        scanf("%d", &choix2);
        vidage_stdin();

        switch(choix2) {
            case 1: // Modification d'un contact de l'annuaire de l'utilisateur courant. A FAIRE...
                if (strcmp(req.login, "admin") != 0) {
                    return 0;
                } else {
                    puts("Accès refusé en tant qu'administrateur.");
                    return 1;
                }
            case 2: // Modification du mot de passe d'un utilisateur.
                if (strcmp(req.login, "admin") == 0) {
                    req.type = UPDATE_USER;
                    
                    printf("\nNom de l'utilisateur : ");
                    fgets(req.data.utilisateur.login, sizeof(req.data.utilisateur.login), stdin);
                    lire_chaine_stdin(req.data.utilisateur.login, sizeof(req.data.utilisateur.login));

                    printf("Nouveau mot de passe : ");
                    fgets(req.data.utilisateur.password, sizeof(req.data.utilisateur.password), stdin);
                    lire_chaine_stdin(req.data.utilisateur.password, sizeof(req.data.utilisateur.password));

                    Emission(req);
                    rep = Reception();

                    if (rep.code == REQ_OK)
                        puts("Mot de passe modifié avec succès.");
                    else if (rep.code == REQ_ERR) 
                        puts("Erreur lors de la modification du mot de passe.");
                } else {
                    puts("\nVous n'avez pas les droits nécessaires pour effectuer cette requête.");
                }
                return 0;
            case 3: //retour au menu principal
                return 1;
            default:
                puts("Ce choix n'existe pas.\n");
                break;
        }
    } while (choix2 != 1 && choix2 != 2 && choix2 != 3 && choix2 != 4);
}

/* Fonction permettant d'afficher un sous-menu Suppression après le menu principal
 * puis d'envoyer une requête au serveur correspondant au choix de l'utilisateur.
 */
int EnvoyerRequeteSuppression(char *login, char *password) {
    requete req;
    reponse rep;
    int choix2;
    int i;
    strcpy(req.login, login);
    strcpy(req.password, password);

    do {
        printf("\033[1;34m");
        puts("******* Menu Suppression *******");
        puts("1. Contact");
        puts("2. Annuaire");
        puts("3. Utilisateur");
        puts("4. Retour en arrière");
            
        printf("\033[0m");
        printf("\nChoisissez un élément : ");
        scanf("%d", &choix2);
        vidage_stdin();

        switch(choix2) {
            case 1: // Suppression d'un contact de l'annuaire de l'utilisateur courant.
                if (strcmp(req.login, "admin") != 0) {
                    req.type = DELETE_CONTACT;

                    // Nom et prénom du contact à chercher puis supprimer dans l'annuaire de l'utilisateur courant.
                    printf("\nNom du contact à supprimer: ");
                    fgets(req.data.cont.Nom, sizeof(req.data.cont.Nom), stdin);
                    lire_chaine_stdin(req.data.cont.Nom, sizeof(req.data.cont.Nom));

                    printf("Prénom du contact à supprimer: ");
                    fgets(req.data.cont.Prenom, sizeof(req.data.cont.Prenom), stdin);
                    lire_chaine_stdin(req.data.cont.Prenom, sizeof(req.data.cont.Prenom));

                    Emission(req);
                    rep = Reception();

                    if (rep.code == REQ_OK) {
                        puts("Contact supprimé avec succès.");
                    } else if (rep.code == BOOK_NOT_FOUND) {
                        puts("Annuaire de l'utilisateur non trouvé.");
                    }
                    return 0;
                } else {
                    puts("Accès refusé en tant qu'administrateur.");
                    return 1;
                }
            case 2: // Suppression de l'annuaire de l'utilisateur courant.
                if (strcmp(req.login, "admin") != 0) {
                    req.type = DELETE_CONTACTSBOOK;
                    printf("\nÊtes-vous sûr de vouloir supprimer votre annuaire ? (o/O/n/N) : ");

                    if (yesNo() == 0) {
                        Emission(req);
                        rep = Reception();

                        if (rep.code == REQ_OK) {
                            puts("Annuaire supprimé avec succès.");
                        } else if (rep.code == BOOK_NOT_FOUND) {
                            puts("Annuaire de l'utilisateur non trouvé.");
                        }
                        return 0;
                    } else {
                        return 1;
                    }
                } else {
                    puts("Accès refusé en tant qu'administrateur.");
                    return 1;
                }
            case 3: // Suppression d'un utilisateur.
                if (strcmp(req.login, "admin") == 0) {
                    req.type = DELETE_USER;

                    printf("\nNom de l'utilisateur à supprimer : ");
                    fgets(req.data.utilisateur.login, sizeof(req.data.utilisateur.login), stdin);
                    lire_chaine_stdin(req.data.utilisateur.login, sizeof(req.data.utilisateur.login));

                    printf("Mot de passe de l'utilisateur à supprimer : ");
                    fgets(req.data.utilisateur.password, sizeof(req.data.utilisateur.password), stdin);
                    lire_chaine_stdin(req.data.utilisateur.password, sizeof(req.data.utilisateur.password));

                    Emission(req);
                    rep = Reception();

                    if (rep.code == REQ_OK) {
                        puts("Utilisateur supprimé avec succès.");
                    } else {
                        puts("Erreur lors de la suppression de l'utilisateur.");
                    }
                } else {
                    puts("\nVous n'avez pas les droits nécessaires pour effectuer cette requête.");
                }
                return 0;
            case 4: //retour au menu principal
                return 1;
            default:
                puts("Ce choix n'existe pas.\n");
                break;
        }
    } while (choix2 != 1 && choix2 != 2 && choix2 != 3 && choix2 != 4);
}

/* Fonction permettant d'afficher un sous-menu Attribution des droits après le menu principal
 * puis d'envoyer une requête au serveur correspondant au choix de l'utilisateur.
 */
int EnvoyerRequeteDroits(char *login, char *password) { // FONCTION A FAIRE...


}
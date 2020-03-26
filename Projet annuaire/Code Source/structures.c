/**********************************************
 * 
 * Fichier contenant les différentes structures utiles
 * pour la forme des PDU des requêtes, des PDU des réponses,
 * ainsi que la création de types "contact", "annuaire" et "user".
 * 
 * Créé et programmé par Clément BRONGNIART.
 * 
 * *******************************************/

typedef struct user {
    char login[21];
    char password[31];
} user;

typedef struct contact {
    char Nom[21]; // Obligatoire
    char Prenom[21];    // Obligatoire
    char Mail[31];  // Obligatoire
    
    /* Infos complémentaires */
    char NumPortable[21];
    char AdressePostale[51];
    char DateNaissance[21];
    char Remarques[255];
} contact;

typedef struct annuaire {
    char fnom[41]; // Nom du fichier annuaire.
    int taille;     // Taille actuelle de l'annuaire.
    contact Tableau[100]; // Tableau de contacts, constitue un annuaire de 100 contacts.
} annuaire;

union data {
    annuaire CBook;
    contact cont;
    user utilisateur;
    char message[255];
} data;

typedef struct requete {
    int type;
    char login[21];
    char password[31];
    union data data; 
} requete;

typedef struct reponse {
    int code;
    union data data; 
} reponse;
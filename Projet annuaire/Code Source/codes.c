/**********************************************
 * 
 * Fichier contenant les différents codes pour les requêtes, 
 * réponses et codes d'erreurs du client et du serveur.
 * 
 * Créé et programmé par Clément BRONGNIART.
 *  _____________________________
 * |Code 0 = Connexion           |
 * |Code 1 = Déconnexion         |
 * |Codes 1x = Créations         |
 * |Codes 2x = Modifications     |
 * |Codes 3x = Suppressions      |
 * |Codes 4x = Affichages        |
 * |Codes 5x = Codes d'auth      |
 * |Codes 6x = GOOD/BAD Request  |
 * |Codes 7x = Codes Annuaire    |
 * |Codes 8x = Codes Utilisateurs|
 * |_____________________________|
 * 
 * *******************************************/

/* Codes pour les requêtes du client. */
#define BIND 0
#define UNBIND 1
#define CREATE_CONTACT 10
#define CREATE_CONTACTSBOOK 11
#define CREATE_RIGHTS 13
#define UPDATE_CONTACT 20
#define DELETE_CONTACT 30
#define DELETE_CONTACTSBOOK 31
#define DELETE_RIGHTS 33
#define GET_CONTACT 40
#define GET_CONTACTSBOOK 41
#define GET_RIGHTS 42

/* Codes requêtes uniquement disponibles à l'administrateur. */
#define CREATE_USER 12
#define UPDATE_USER 21
#define DELETE_USER 32

/* Codes réponses et erreurs pour le serveur. */
#define AUTH_OK 50
#define AUTH_ERR 51
#define DISCONNECT_CONFIRM 52
#define REQ_OK 60
#define REQ_ERR 61
#define NOT_ALLOWED 70
#define BOOK_NOT_FOUND 71
#define CONTACT_NOT_FOUND 72
#define BOOK_EXISTS 73
#define USER_EXISTS 80
#define USER_NOT_FOUND 81
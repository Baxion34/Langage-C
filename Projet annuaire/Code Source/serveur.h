#ifndef __SERVEUR_H__
#define __SERVEUR_H__

#include "serveur.c"
#include "traitements.c"

/*##################### Fichier purge.c #####################*/

/* Vide le buffer */
void vidage_stdin(void);

/* Remplace le caractère '\n' à la fin d'une chaîne de caractères par '\0'. */
char * lire_chaine_stdin(char * chaine, int taille);

/*##################### Fichier purge.c #####################*/

/*##################### Fichier serveur.c #####################*/

/* Initialisation.
 * Création du serveur en précisant le service ou numéro de port.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int InitialisationAvecService(char *service);

/* Attends qu'un client se connecte. */
int AttenteClient();

/* Vérifie si la combinaison login/password envoyée par le client correspond
 * à ce que connait le serveur dans son fichier utilisateurs.txt.
 */
int VerificationConnexion(requete req);

/* Reçoie une requête du client. */
requete Reception();

/* Envoie une réponse au client. */
int Emission(reponse rep);

/* Ferme la connexion avec le client. */
void DeconnexionClient();

/* Arrete le serveur. */
void Terminaison();

/*##################### Fichier serveur.c #####################*/

/*##################### Fichier traitements.c #####################*/

/* Permet de vérifier si un utilisateur existe déjà ou non en cherchant
 * le login demandé dans une requête dans le fichier "utilisateurs.txt".
 * Retourne 1 si l'utilisateur existe, 0 s'il n'existe pas.
 */
int rechercheUser(char *login);

/* Permet de voir si un utilisateur possède un annuaire.
 * Retourne 1 si trouvé, 0 sinon.
 */
int rechercheAnnuaire(char *CBook);

/* Créé un contact demandé dans l'annuaire de l'utilisateur courant. */
int CreateContact(char *fname, contact contDemande);

/* Permet de vérifier si l'annuaire demandé existe (retourne 1).
 * Sinon, le crée et retourne 0.
 */
int CreateCBook(char *CBook);

/* Supprime un contact cherché dans l'annuaire de l'utilisateur courant. */
int DELContact(contact contDemande, char *CBook);

/* Permet de vérifier si l'annuaire demandé existe et le supprime (retourne 0).
 * Sinon, affiche une erreur du côté du serveur et retourne 1.
 */
int DeleteCBook(char *CBook);

/* Permet de voir si un contact existe dans l'annuaire pointé 
 * et d'envoyer ses informations au client.
 * Retourne 1 si trouvé, 0 sinon.
 */
int GETContact(contact cont, char *CBook);

/* Permet de récupérer les informations de tous les contacts
 * enregistrés dans l'annuaire et de les envoyer au client.
 */
int GETAllContacts(char *CBook);

/* Traitement des différentes requêtes disponibles dans le menu Création. */
int traiterRequeteCREATE(requete req);

/* Traitement des différentes requêtes disponibles dans le menu Modification. */
int traiterRequeteUPDATE(requete req);

/* Traitement des différentes requêtes disponibles dans le menu Suppression. */
int traiterRequeteDELETE(requete req);

/* Traitement des différentes requêtes disponibles dans le menu Affichage. */
int traiterRequeteGET(requete req);

/*##################### Fichier traitements.c #####################*/

#endif
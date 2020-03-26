#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "client.c"
#include "purge.c"
#include "requetes.c"

/*##################### Fichier purge.c #####################*/

/* Vide le buffer */
void vidage_stdin(void);

/* Remplace le caractère '\n' à la fin d'une chaîne de caractères par '\0'. */
char * lire_chaine_stdin(char * chaine, int taille);

/*##################### Fichier purge.c #####################*/

/*##################### Fichier requetes.c #####################*/

/* Fonction permettant d'afficher un sous-menu Affichage après le menu principal
 * puis d'envoyer une requête au serveur correspondant au choix de l'utilisateur.
 */
int EnvoyerRequeteAffichage(char *login, char *password);

/* Fonction permettant d'afficher un sous-menu Création après le menu principal
 * puis d'envoyer une requête au serveur correspondant au choix de l'utilisateur.
 */
int EnvoyerRequeteCreation(char *login, char *password);

/* Fonction permettant d'afficher un sous-menu Modification après le menu principal
 * puis d'envoyer une requête au serveur correspondant au choix de l'utilisateur.
 */
int EnvoyerRequeteModification(char *login, char *password);

/* Fonction permettant d'afficher un sous-menu Suppression après le menu principal
 * puis d'envoyer une requête au serveur correspondant au choix de l'utilisateur.
 */
int EnvoyerRequeteSuppression(char *login, char *password);

/* Fonction permettant d'afficher un sous-menu Attribution des droits après le menu principal
 * puis d'envoyer une requête au serveur correspondant au choix de l'utilisateur.
 */
int EnvoyerRequeteDroits(char *login, char *password);

/*##################### Fichier requetes.c #####################*/

/*##################### Fichier client.c #####################*/

/* Initialisation.
 * Connexion au serveur sur le service donné.
 */
int Connexion(char *login, char *password, char *service);

/* On demande si l'utilisateur veut afficher toutes les données
 * ou seulement les données "obligatoires" des contacts.
 * Retourne 0 si 'O' ou 'o' sélectionné, retourne 1 si 'n' ou 'N'.
 */
int yesNo();

/* Affiche le menu principal après la phase de connexion. */
void AffichageMenuPrincipal();

/* Envoie une requête au serveur.
 * Retourne 1 si tout c'est bien passé.
 */
int Emission(requete req);

/* Recoit une réponse envoyée par le serveur
 * et la retourne.
 */
reponse Reception();

/* Ferme la connexion. */
void Deconnexion();

/*##################### Fichier client.c #####################*/
#endif
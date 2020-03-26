/**********************************************
 * 
 * Fichier contenant les fonctions du serveur permettant de
 * traiter les requêtes du client.
 * 
 * Créé et programmé par Clément BRONGNIART.
 * 
 * *******************************************/

#include "serveur.h"

/* Permet de vérifier si un utilisateur existe déjà ou non en cherchant
 * le login demandé dans une requête dans le fichier "utilisateurs.txt".
 * Retourne 1 si l'utilisateur existe, 0 s'il n'existe pas.
 */
int rechercheUser(char *login) {
	char str[255];
	char *log;
	FILE *f;

	f = fopen("utilisateurs.txt", "r");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier.");
		return -1;
	}
 
    while (fgets(str,sizeof(str),f)) {
		// Récupération du login (avant chaque ";" dans le fichier utilisateurs.txt) sur chaque ligne.
		log = strtok(str, ";");

		/* Vérification si le login inscrit et le login demandé correspondent.
		 * S'ils correspondent, l'utilisateur existe déjà.
		 */ 
		if (strcmp(log, login) == 0) {
			fclose(f);
			return 1;
		}
    }
    fclose(f);
	return 0;
}

/* Permet de voir si un utilisateur possède un annuaire.
 * Retourne 1 si trouvé, 0 sinon.
 */
int rechercheAnnuaire(char *CBook) {
	if(access(CBook, F_OK) != -1)
    	return 1;
	else
    	return 0;
}

/* Créé un contact demandé dans l'annuaire de l'utilisateur courant.
 * Créé par Dorian ISSALIS.
 */
int CreateContact(char *fname, contact contDemande) {
	FILE *f;

	f = fopen(fname, "a");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier.");
		return -1;
	}

	fprintf(f,"%s;%s;%s;%s;%s;%s;%s;\r", contDemande.Nom, contDemande.Prenom, contDemande.Mail,
	contDemande.NumPortable, contDemande.AdressePostale, contDemande.DateNaissance, contDemande.Remarques);

	fclose(f);
	return 0;
}

/* Permet de vérifier si l'annuaire demandé existe (retourne 1).
 * Sinon, le crée et retourne 0.
 * Créé par Dorian ISSALIS.
 */
int CreateCBook(char *CBook) {
	FILE *f;

	if (rechercheAnnuaire(CBook) == 0) {
		f = fopen(CBook, "w");
		if (f == NULL) {
			perror("Erreur lors de l'ouverture du fichier.");
			return -1;
		}
		fclose(f);
		return 0;
	} else {
		return 1;
	}
}

/* Supprime un contact cherché dans l'annuaire de l'utilisateur courant. */
int DELContact(contact contDemande, char *CBook) {
	char str[255];
	char *delim;
	char temp[30] = "temp.txt";
	FILE *replique;
	FILE *f;
	reponse rep;
	contact tmp;
	
	f = fopen(CBook, "r");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier.");
		return -1;
	}

	replique = fopen(temp, "w");
	if (replique == NULL) {
		perror("Erreur lors de l'ouverture du fichier.");
		return -1;
	}

	/* Récupération des différents champs avant chaque ";" de chaque ligne du fichier
	 * pour les stocker dans les champs correspondants de la structure contact.
	 */
	while (fgets(str,sizeof(str),f)) {
		delim = strtok(str, ";");
		strcpy(tmp.Nom, delim);

		delim = strtok(NULL, ";");
		strcpy(tmp.Prenom, delim);
		
		delim = strtok(NULL, ";");
		strcpy(tmp.Mail, delim);
		
		delim = strtok(NULL, ";");
		strcpy(tmp.NumPortable, delim);
		
		delim = strtok(NULL, ";");
		strcpy(tmp.AdressePostale, delim);
		
		delim = strtok(NULL, ";");
		strcpy(tmp.DateNaissance, delim);

		delim = strtok(NULL, ";");
		strcpy(tmp.Remarques, delim);

		lire_chaine_stdin(tmp.Remarques, sizeof(tmp.Remarques));
		
		
		if (strcmp(tmp.Nom, contDemande.Nom) == 0 && strcmp(tmp.Prenom, contDemande.Prenom) != 0) {
			fprintf(replique, "%s;%s;%s;%s;%s;%s;%s;\n", tmp.Nom, tmp.Prenom, tmp.Mail, tmp.NumPortable, tmp.AdressePostale, tmp.DateNaissance, tmp.Remarques);
		} else if (strcmp(tmp.Nom, contDemande.Nom) != 0 && strcmp(tmp.Prenom, contDemande.Prenom) == 0) {
			fprintf(replique, "%s;%s;%s;%s;%s;%s;%s;\n", tmp.Nom, tmp.Prenom, tmp.Mail, tmp.NumPortable, tmp.AdressePostale, tmp.DateNaissance, tmp.Remarques);
		} else if (strcmp(tmp.Nom, contDemande.Nom) != 0 && strcmp(tmp.Prenom, contDemande.Prenom) != 0) {
			fprintf(replique, "%s;%s;%s;%s;%s;%s;%s;\n", tmp.Nom, tmp.Prenom, tmp.Mail, tmp.NumPortable, tmp.AdressePostale, tmp.DateNaissance, tmp.Remarques);
		}
    }

	fclose(f);
	fclose(replique);
	remove(CBook);
	rename(temp, CBook);
	return 0;
}

/* Permet de vérifier si l'annuaire demandé existe et le supprime (retourne 0).
 * Sinon, affiche une erreur du côté du serveur et retourne 1.
 */
int DeleteCBook(char *CBook) {
	if (rechercheAnnuaire(CBook) == 1) {
		remove(CBook);
		return 0;
	} else {
		puts("ERROR: CBook not Found.");
		return 1;
	}
}

/* Permet de voir si un contact existe dans l'annuaire pointé 
 * et d'envoyer ses informations au client.
 * Retourne 1 si trouvé, 0 sinon.
 */
int GETContact(contact cont, char *CBook) {
	char str[255];
	char *delim;
	FILE *f;
	reponse rep;
	
	f = fopen(CBook, "r");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier.");
		return -1;
	}

	/* Récupération des différents champs avant chaque ";" de chaque ligne du fichier
	 * pour les stocker dans les champs correspondants de la structure contact.
	 */
	while (fgets(str,sizeof(str),f)) {
		delim = strtok(str, ";");
		strcpy(rep.data.cont.Nom, delim);

		delim = strtok(NULL, ";");
		strcpy(rep.data.cont.Prenom, delim);
		
		delim = strtok(NULL, ";");
		strcpy(rep.data.cont.Mail, delim);
		
		delim = strtok(NULL, ";");
		strcpy(rep.data.cont.NumPortable, delim);
		
		delim = strtok(NULL, ";");
		strcpy(rep.data.cont.AdressePostale, delim);
		
		delim = strtok(NULL, ";");
		strcpy(rep.data.cont.DateNaissance, delim);

		delim = strtok(NULL, ";");
		strcpy(rep.data.cont.Remarques, delim);

		lire_chaine_stdin(rep.data.cont.Remarques, sizeof(rep.data.cont.Remarques));
		
		/* S'il y a correspondance entre le nom et prénom écrits sur une ligne du fichier et
		 * le nom et prénom du contact recherché par le client, on arrête de lire le fichier
		 * et on envoie les informations du contact au client.
		 */
		if (strcmp(rep.data.cont.Nom, cont.Nom) == 0 && strcmp(rep.data.cont.Prenom, cont.Prenom) == 0) {
			rep.code = REQ_OK;
			Emission(rep);
			return 1;
		}
    }

	if (strcmp(rep.data.cont.Nom, cont.Nom) == 0 && strcmp(rep.data.cont.Prenom, cont.Prenom) != 0) {
		rep.code = CONTACT_NOT_FOUND;
		strcpy(rep.data.message, "ContactNotFound");
		Emission(rep);
	} else if (strcmp(rep.data.cont.Nom, cont.Nom) != 0 && strcmp(rep.data.cont.Prenom, cont.Prenom) == 0) {
		rep.code = CONTACT_NOT_FOUND;
		strcpy(rep.data.message, "ContactNotFound");
		Emission(rep);
	}

	/* S'il n'y a aucune correspondance même après avoir lu le fichier complet,
	 * on envoie une réponse avec le code CONTACT_NOT_FOUND au client.
	 */
 	else if (strcmp(rep.data.cont.Nom, cont.Nom) != 0 && strcmp(rep.data.cont.Prenom, cont.Prenom) != 0) {
		rep.code = CONTACT_NOT_FOUND;
		strcpy(rep.data.message, "ContactNotFound");
		Emission(rep);
	}

	fclose(f);
	return 0;
}

/* Permet de récupérer les informations de tous les contacts
 * enregistrés dans l'annuaire et de les envoyer au client.
 */
int GETAllContacts(char *CBook) {
	char str[255];
	char *delim;
	FILE *f;
    contact tmp;
    reponse rep;
    int i = 0;
	
	f = fopen(CBook, "r");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier.");
        return -1;
	}

	/* Récupération des différents champs avant chaque ";" de chaque ligne du fichier
	 * pour les stocker dans les champs correspondants de la structure contact.
	 */
	while (fgets(str,sizeof(str),f)) {
        delim = strtok(str, ";");
        strcpy(tmp.Nom, delim);

        delim = strtok(NULL, ";");
        strcpy(tmp.Prenom, delim);
            
        delim = strtok(NULL, ";");
        strcpy(tmp.Mail, delim);
        
        delim = strtok(NULL, ";");
        strcpy(tmp.NumPortable, delim);
            
        delim = strtok(NULL, ";");
        strcpy(tmp.AdressePostale, delim);
            
        delim = strtok(NULL, ";");
        strcpy(tmp.DateNaissance, delim);

        delim = strtok(NULL, ";");
        strcpy(tmp.Remarques, delim);

        lire_chaine_stdin(tmp.Remarques, sizeof(tmp.Remarques));

		/* Tant qu'on ne dépasse pas la taille limite de l'annuaire (100 contacts, donc 100 lignes),
		 * on recopie le contact lu dans le fichier vers un tableau de contact qui sera envoyé au
		 * client pour afficher tous les contacts présents dans l'annuaire de l'utilisateur.
		 */
        if (i < 100) {
            rep.data.CBook.Tableau[i] = tmp;
        } else {
            puts("Erreur : Plus de 100 contacts trouvés dans un annuaire.");
            rep.code = REQ_ERR;
            strcpy(rep.data.message, "TooManyContacts");
            Emission(rep);

            return 0;
        }
        i++;
    }
    rep.code = REQ_OK;
	/* Le champ taille est un indicateur pour savoir combien de contacts sont présents
	 * dans l'annuaire de l'utilisateur afin de créer une boucle pour les afficher.
	 */
    rep.data.CBook.taille = i-1;
	Emission(rep);
		
    fclose(f);
}

/* Traitement des différentes requêtes disponibles dans le menu Création. */
int traiterRequeteCREATE(requete req) {
	FILE *f;
	reponse rep;
	annuaire CBook;
	char tmp[51];
	strcpy(CBook.fnom, req.login);
	strcat(CBook.fnom,"_annuaire.txt");

	/* Création d'un contact dans l'annuaire de l'utilisateur courant.
	 * Créé par Dorian ISSALIS.
	 */
	if (req.type == CREATE_CONTACT) {
		if (rechercheAnnuaire(CBook.fnom) == 1) {
			CreateContact(CBook.fnom,req.data.cont);
			rep.code = REQ_OK;
			strcpy(rep.data.message, "RequestSuccessfull");
			Emission(rep);
		} else {
			rep.code = BOOK_NOT_FOUND;
			strcpy(rep.data.message, "CBookNotFound");
			Emission(rep);
		}
	}

	/* Création d'un annuaire pour un utilisateur 
	 * Créé par Dorian ISSALIS.
	 */
	if (req.type == CREATE_CONTACTSBOOK) {
		if (CreateCBook(CBook.fnom) == 0) {
			rep.code = REQ_OK;
			strcpy(rep.data.message, "RequestSuccessfull");
			Emission(rep);
			return 0;
		} else {
			rep.code = BOOK_EXISTS;
			strcpy(rep.data.message, "CBookAlreadyExists");
			Emission(rep);
			return 1;
		}
	}

	/* Création d'un utilisateur, fonction uniquement disponible à l'admin. */
	if ((strcmp(req.login, "admin") == 0) && (req.type == CREATE_USER)) {
		// Si l'utilisateur n'existe pas :
		if (rechercheUser(req.data.utilisateur.login) == 0) {
			f = fopen("utilisateurs.txt", "a");
			if (f == NULL) {
				perror("Erreur lors de l'ouverture du fichier.");
				return -1;
			}

			strcpy(CBook.fnom, req.data.utilisateur.login);
			strcat(CBook.fnom,"_annuaire.txt");

			/* Concaténation du login et password sous le même format 
			* que dans le fichier utilisateurs.txt.
			*/
			strcpy(tmp, req.data.utilisateur.login);
			strcat(tmp, ";");
			strcat(tmp, req.data.utilisateur.password);
			strcat(tmp, "\r\n");

			// Ecriture du login et password dans le fichier et émission d'une réponse REQ_OK.
			fprintf(f, "%s", tmp);
			fclose(f);

			// Création automatique d'un annuaire pour un nouvel utilisateur.
			if ((rechercheUser(req.data.utilisateur.login) == 1) && (CreateCBook(CBook.fnom) == 0)) {
				rep.code = REQ_OK;
				strcpy(rep.data.message, "RequestSuccessfull");
				Emission(rep);
				return 0;
			} else {
				rep.code = REQ_ERR;
				strcpy(rep.data.message, "Error");
				Emission(rep);
				return 1;
			}
		// Si l'utilisateur demandé existe déjà dans le fichier d'utilisateurs :
		} else {
			rep.code = USER_EXISTS;
			strcpy(rep.data.message, "UserAlreadyExists");
			Emission(rep);
			return 1;
		}
	// Si un utilisateur autre que l'admin essaie de créer un utilisateur :
	} else if ((strcmp(req.login, "admin") != 0) && (req.type == CREATE_USER)) {
		rep.code = NOT_ALLOWED;
        strcpy(rep.data.message, "UserNotAllowed");
        Emission(rep);
		return 2;
	}

	// A Faire...
	if (req.type == CREATE_RIGHTS) {
		//...
	}
}

/* Traitement des différentes requêtes disponibles dans le menu Modification. */
int traiterRequeteUPDATE(requete req) {
	FILE *f;
	FILE *replique;
	char contenufichier[51];
	char concatUser[51];
	char fname[30] = "utilisateurs.txt";
	char temp[30] = "temp.txt";
	char tmp[51];
	char *log;
	reponse rep;
	int fini = 0;

	/* Modification d'un contact dans l'annuaire de l'utilisateur courant.
	 * A FAIRE...
	 */
	if (req.type == UPDATE_CONTACT) {
		// ...
	}

	/* Modification du mot de passe d'un utilisateur.*/
	if ((strcmp(req.login, "admin") == 0) && (req.type == UPDATE_USER)) {
		if (rechercheUser(req.data.utilisateur.login) == 1) {
			f = fopen(fname, "r");
			if (f == NULL) {
				perror("Erreur lors de l'ouverture du fichier.");
				return -1;
			}
			
			/* Création d'un fichier temporaire pour écrire toutes les données d'utilisateurs.txt
			 * dans le nouveau en "oubliant" la ligne avec le même login que dans la requête et
			 * en ajoutant le nouveau mot de passe indiqué.
			 */
			replique = fopen(temp, "w");
			if (replique == NULL) {
				perror("Erreur lors de l'ouverture du fichier.");
				return -1;
			}

			strcpy(concatUser, req.data.utilisateur.login);
			strcat(concatUser, ";");
			strcat(concatUser, req.data.utilisateur.password);
			strcat(concatUser, "\r\n");

			while (fgets(contenufichier, 51, f)) {
				// Stockage de contenuFichier dans tmp pour éviter que strtok() modifie celui-ci.
				strcpy(tmp, contenufichier);
				// Récupération du login (avant chaque ";" dans le fichier utilisateurs.txt) sur chaque ligne.
				log = strtok(tmp, ";");

				/* Vérification si le login inscrit et le login demandé correspondent.
				* S'ils correspondent, l'utilisateur existe déjà.
				*/ 
				if (strcmp(log, req.data.utilisateur.login) != 0)
					fprintf(replique, "%s", contenufichier);
				else {
					fprintf(replique, "%s", concatUser);
					rep.code = REQ_OK;
					strcpy(rep.data.message, "RequestSuccessfull");
					Emission(rep);
					fini = 1;
				}
			}

			// Vérification au cas où une erreur arrive lors de la modification du mot de passe.
			if (fini != 1) {
				rep.code = REQ_ERR;
				strcpy(rep.data.message, "RequestError");
				Emission(rep);
			}

			// On ferme les fichiers et on supprime l'ancien pour renommer temp.txt en utilisateurs.txt.
			fclose(f);
			fclose(replique);
			remove(fname);
			rename(temp, fname);
			return 0;
		} else {
			rep.code = USER_NOT_FOUND;
            strcpy(rep.data.message, "UserNotFound");
            Emission(rep);
			return 1;
		}
	} else if ((strcmp(req.login, "admin") != 0) && (req.type == UPDATE_USER)) {
        rep.code = NOT_ALLOWED;
        strcpy(rep.data.message, "UserNotAllowed");
        Emission(rep);
		return 2;
	}
}

/* Traitement des différentes requêtes disponibles dans le menu Suppression. */
int traiterRequeteDELETE(requete req) {
	FILE *f;
	FILE *replique;
	reponse rep;
	annuaire CBook;
	char contenufichier[51];
	char concatUser[51];
	char fname[30] = "utilisateurs.txt";
	char temp[30] = "temp.txt";

	if (strcmp(req.login, "admin") == 0) {
		strcpy(CBook.fnom, req.data.utilisateur.login);
		strcat(CBook.fnom,"_annuaire.txt");
	} else {
		strcpy(CBook.fnom, req.login);
		strcat(CBook.fnom,"_annuaire.txt");
	}

	/* Suppression d'un contact pour l'utilisateur courant. */
	if (req.type == DELETE_CONTACT) {
		if (rechercheAnnuaire(CBook.fnom)==1) {
			DELContact(req.data.cont, CBook.fnom);
			rep.code = REQ_OK;
			strcpy(rep.data.message, "RequestSuccessfull");
			Emission(rep);
			return 0;
		} else {
			rep.code = BOOK_NOT_FOUND;
			strcpy(rep.data.message, "CBookDoesntExist");
			Emission(rep);
			return 1;
		}
	}

	/* Suppression de l'annuaire pour l'utilisateur courant. */
	if (req.type == DELETE_CONTACTSBOOK) {
		if (DeleteCBook(CBook.fnom) == 0) {
			rep.code = REQ_OK;
			strcpy(rep.data.message, "RequestSuccessfull");
			Emission(rep);
			return 0;
		} else {
			rep.code = BOOK_NOT_FOUND;
			strcpy(rep.data.message, "CBookDoesntExist");
			Emission(rep);
			return 1;
		}
	}

	/* Suppression d'un utilisateur demandé. */
	if ((strcmp(req.login, "admin") == 0) && (req.type == DELETE_USER)) {
		if (rechercheUser(req.data.utilisateur.login) == 1) {

			/* Création d'un fichier temporaire pour écrire toutes les données d'utilisateurs.txt
			* dans le nouveau à l'exception de la ligne contenant le login et password de
			* l'utilisateur à supprimer.
			*/
			f = fopen(fname, "r");
			if (f == NULL) {
				perror("Erreur lors de l'ouverture du fichier.");
				return -1;
			}

			replique = fopen(temp, "w");
			if (replique == NULL) {
				perror("Erreur lors de l'ouverture du fichier.");
				return -1;
			}

			strcpy(concatUser, req.data.utilisateur.login);
			strcat(concatUser, ";");
			strcat(concatUser, req.data.utilisateur.password);
			strcat(concatUser, "\r\n");

			while (fgets(contenufichier, 51, f)) {
				if (strcmp(contenufichier, concatUser) != 0)
					fprintf(replique, "%s", contenufichier);
			}

			/* Suppression d'utilisateurs.txt puis on renomme le fichier temporaire par "utilisateurs.txt"
			* pour qu'il devienne la nouvelle version de ce fichier avec l'utilisateur supprimé.
			*/
			fclose(f);
			fclose(replique);
			remove(fname);
			rename(temp, fname);

			if ((rechercheUser(req.data.utilisateur.login) == 0)) {
				DeleteCBook(CBook.fnom);
				rep.code = REQ_OK;
				strcpy(rep.data.message, "RequestSuccessfull");
				Emission(rep);
				return 0;
			} else {
				rep.code = REQ_ERR;
				strcpy(rep.data.message, "Error");
				Emission(rep);
				return 1;
			}
		} else {
            rep.code = USER_NOT_FOUND;
            strcpy(rep.data.message, "UserNotFound");
            Emission(rep);
			return 1;
		}
	} else if ((strcmp(req.login, "admin") != 0) && (req.type == DELETE_USER)) {
        rep.code = NOT_ALLOWED;
        strcpy(rep.data.message, "UserNotAllowed");
        Emission(rep);
		return 2;
	}
}

/* Traitement des différentes requêtes disponibles dans le menu Affichage. */
int traiterRequeteGET(requete req) {
	reponse rep;
	annuaire CBook;
	strcpy(CBook.fnom, req.login);
	strcat(CBook.fnom,"_annuaire.txt");

	/* Affiche les informations d'un contact spécifique contenu
	 * dans l'annuaire de l'utilisateur courant.
	 */
	if (req.type == GET_CONTACT) {
		if (rechercheAnnuaire(CBook.fnom) == 1) {
			GETContact(req.data.cont, CBook.fnom);
		} else {
			rep.code = BOOK_NOT_FOUND;
			strcpy(rep.data.message, "CBookNotFound");
			Emission(rep);
		}
	}

	/* Affiche les informations de tous les contacts de l'annuaire
	 * de l'utilisateur courant.
	 */
	if (req.type == GET_CONTACTSBOOK) {
		if (rechercheAnnuaire(CBook.fnom) == 1) {
            GETAllContacts(CBook.fnom);
		} else {
			rep.code = BOOK_NOT_FOUND;
			strcpy(rep.data.message, "CBookNotFound");
			Emission(rep);
		}
	}

	// A FAIRE...
	if (req.type == GET_RIGHTS) {
		// ...
	}
}
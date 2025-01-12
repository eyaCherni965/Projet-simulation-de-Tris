/********************************************************************/
/* Fichier   : FILE.H												*/
/*																	*/
/* Cette librairie impl�mente une file d'operations.				*/
/* Les operations sont des LECTURES ou des ECRITURES.				*/
/********************************************************************/

#if !defined (MODULE_FILE_OPERATIONS)
#define MODULE_FILE_OPERATIONS


/********************************************************************/
/*					DEFINITIONS DE CONSTANTES						*/
/********************************************************************/
//La taille maximale de la file (nb. max d'�l�ments)
#define  TAILLE_MAXIMALE	200000


/********************************************************************/
/*			     DEFINITIONS DES TYPES POUR LA FILE				    */
/********************************************************************/
//Type ENUM pour les deux types d'op�rations
typedef enum {LECTURE, ECRITURE} enum_operation;

//Type-enregistrement d'une op�ration
typedef struct {
	enum_operation type_operation;  //le type d'op�ration (LECTURE/ECRITURE)
	int indice;						//la position-tableau de l'op�ration
	int valeur;						//la valeur lue/�crite dans le tableau
} t_operation;

//Type-enregistrement de la file d'op�rations
struct t_file {
	t_operation donnees[TAILLE_MAXIMALE];   //le tableau des op�rations
	int debut, fin,							//les 2 indices de position relative
		total;								//la longueur de la file (nb. d'�l�ments)
};

/********************************************************************/
/*			DEFINITIONS DU TYPE POUR UNE FILE DYNAMIQUE  			*/
/********************************************************************/
//Type-pointeur � un "struct t_file" (la file est DYNAMIQUE)
typedef struct t_file * t_ptr_file;


/********************************************************************/
/*					DECLARATIONS DES FONCTIONS						*/
/********************************************************************/
t_ptr_file creer_file(void);
/* Cette fonction permet de creer une file dynamique vide (malloc).	*/
/* Elle retourne l'adresse en cas de succes et NULL sinon.			*/

int enfiler(t_ptr_file, const t_operation *);
/* Cette fonction ajoute un �l�ment dans la file.					*/
/* Elle retourne 1 en cas de succes et 0 sinon (file pleine).		*/
/* PARAMETRES :														*/
/*	- t_ptr_file : La file ou l'on veut ajouter.					*/
/*	- t_operation * : L'�l�ment a ajouter.							*/
/* ATTENTION : On suppose que la file a d�j� �t� cr�e et n'a pas	*/
/*			   �t� lib�r�e.											*/

int defiler(t_ptr_file, t_operation *);
/* Cette fonction retire un element de la file.						*/
/* Elle retourne 1 en cas de succes et 0 sinon.						*/
/* Si le defilement a fonction, on affecte l'element pointe par le	*/
/* t_operation * de la valeur defilee.								*/
/* PARAMETRES :														*/
/*	- t_ptr_file : La file ou l'on veut ajouter.					*/
/*	- t_operation * : L'�l�ment a retirer (SORTIE).					*/
/* ATTENTION : On suppose que la file a d�j� �t� cr�e et n'a pas	*/
/*			   �t� lib�r�e.											*/

int est_pleine(const t_ptr_file);
/* Cette fonction retourne 1 si la file est pleine et 0 sinon.		*/
/* PARAMETRE :														*/
/*	- t_ptr_file : La file a consulter.								*/
/* ATTENTION : On suppose que la file a d�j� �t� cr�e et n'a pas	*/
/*			   �t� lib�r�e.											*/

int est_vide(const t_ptr_file);
/* Cette fonction retourne 1 si la file est vide et 0 sinon.		*/
/* PARAMETRE :														*/
/*	- t_ptr_file : La file a consulter.								*/
/* ATTENTION : On suppose que la file a d�j� �t� cr�e et n'a pas	*/
/*			   �t� lib�r�e.											*/

int longueur(const t_ptr_file);
/* Cette fonction retourne le nombre d'�l�ment dans la file.		*/
/* PARAMETRE :														*/
/*	- t_ptr_file : La file a consulter.								*/
/* ATTENTION : On suppose que la file a d�j� �t� cr�e et n'a pas	*/
/*			   �t� lib�r�e.											*/

void liberer_file(t_ptr_file);
/* Cette fonction d�truit la file dynamique (free).					*/
/* Pour pouvoir l'utiliser � nouveau, vous devez la recr�er.		*/
/* PARAMETRE :														*/
/*	- t_ptr_file : La file � d�truire.								*/
/* ATTENTION : On suppose que la file a d�j� �t� cr�e et n'a pas	*/
/*			   �t� lib�r�e.											*/

#endif

/*******************************************************************************
    Module qui contient les fonctions de gestion de l'affichage des tris en
    mode graphique avec des pixels. Offre aussi 3 petites fonctions utilitaires.
********************************************************************************/
#if !defined (NOIR)

// Les 3 couleurs à utiliser
#define NOIR  0
#define JAUNE 14
#define BLANC 15

/* Cette fonction permet de passer au mode graphique.				 */
/* Retourne 1 en cas de succes, 0 sinon.							 */
int ouvrir_mode_graphique(void);

/* Cette fonction permet de terminer le mode graphique.				 */
/* ATTENTION : Le mode graphique doit avoir été ouvert.				 */
void fermer_mode_graphique(void);

/* Permet d'afficher un message "mess" dans le haut de l'écran.      */
/* PARAMÈTRE: mess - la chaine de caractères à affciher.             */
void afficher_message(const char * mess);

/* Cette fonction affiche le cadre d'un tri au depart, avec le titre */
/* et le nombre d'opérations affiché en bas du cadre #indice.        */
/* Elle suppose que l'indice du tri est entre 0 et NB_TRIS - 1.		 */
/* PARAMÈTRE: indice - le numéro du tri à afficher (0 à NB_TRIS-1).  */
/*            nom_tri - le nom du tri à afficher au dessus du cadre. */
/*            taille - le nombre total d'éléments à trier.           */
/*            nb_oper - nombre total d'opérations pour faire ce tri. */
/* ATTENTION : Le mode graphique doit avoir ete ouvert.				 */
/* ATTENTION : Elle supporte AU MAXIMUM 6 tris (indice < 6).    	 */
void afficher_cadre_tri(int indice, const char * nom_tri, int taille, int nb_oper);


/* Cette fonction affiche un point avec la "couleur" désirée pour la */
/* "valeur" à la position de tableau "[pos]" du tri #indice_tri.     */
/* PARAMÈTRE: indice - le numéro du tri à afficher (0 à NB_TRIS-1).  */
/*            pos - position-tableau de la valeur (sur l'axe des X). */
/*            valeur - la valeur à cette posiiton (sur l'axe des Y). */
/*            taille - le nombre total d'éléments à trier.           */
/*            couleur - la couleur de pixel désirée (entre 0 et 15). */
/* ATTENTION : Le mode graphique doit avoir ete ouvert.			     */
/* ATTENTION : Le cadre pour illustrer ce tri doit avoir été dessiné */
/* ATTENTION : Elle supporte AU MAXIMUM 6 tris (indice < 6).         */
void afficher_point(int indice, int pos, int valeur, int taille, int couleur);

/* Permet de faire une pause de "msec" millisecondes à l'écran.      */
/* PARAMÈTRE: msec - le temps de délai désiré en millisecondes.      */
void delai_ecran(int msec);
	
/* Retourne 1 si une touche a été pesée, 0 sinon.                    */
int  touche_pesee();

/* Pour récupérer un caractère saisi dans la console graphique.      */
char obtenir_touche();
	
#endif

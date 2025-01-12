/*******************************************************************************
    AFFICHAGES.h  (version pour le TP2, A24)  *** Ce module est DONN� aux �l�ves
    Auteurs : E.Th�

    Module qui contient les fonctions de gestion de l'affichage des tris en
    mode graphique avec des pixels. Offre aussi 3 petites fonctions utilitaires.
********************************************************************************/
#if !defined (NOIR)

// Les 3 couleurs � utiliser
#define NOIR  0
#define JAUNE 14
#define BLANC 15

/* Cette fonction permet de passer au mode graphique.				 */
/* Retourne 1 en cas de succes, 0 sinon.							 */
int ouvrir_mode_graphique(void);

/* Cette fonction permet de terminer le mode graphique.				 */
/* ATTENTION : Le mode graphique doit avoir �t� ouvert.				 */
void fermer_mode_graphique(void);

/* Permet d'afficher un message "mess" dans le haut de l'�cran.      */
/* PARAM�TRE: mess - la chaine de caract�res � affciher.             */
void afficher_message(const char * mess);

/* Cette fonction affiche le cadre d'un tri au depart, avec le titre */
/* et le nombre d'op�rations affich� en bas du cadre #indice.        */
/* Elle suppose que l'indice du tri est entre 0 et NB_TRIS - 1.		 */
/* PARAM�TRE: indice - le num�ro du tri � afficher (0 � NB_TRIS-1).  */
/*            nom_tri - le nom du tri � afficher au dessus du cadre. */
/*            taille - le nombre total d'�l�ments � trier.           */
/*            nb_oper - nombre total d'op�rations pour faire ce tri. */
/* ATTENTION : Le mode graphique doit avoir ete ouvert.				 */
/* ATTENTION : Elle supporte AU MAXIMUM 6 tris (indice < 6).    	 */
void afficher_cadre_tri(int indice, const char * nom_tri, int taille, int nb_oper);


/* Cette fonction affiche un point avec la "couleur" d�sir�e pour la */
/* "valeur" � la position de tableau "[pos]" du tri #indice_tri.     */
/* PARAM�TRE: indice - le num�ro du tri � afficher (0 � NB_TRIS-1).  */
/*            pos - position-tableau de la valeur (sur l'axe des X). */
/*            valeur - la valeur � cette posiiton (sur l'axe des Y). */
/*            taille - le nombre total d'�l�ments � trier.           */
/*            couleur - la couleur de pixel d�sir�e (entre 0 et 15). */
/* ATTENTION : Le mode graphique doit avoir ete ouvert.			     */
/* ATTENTION : Le cadre pour illustrer ce tri doit avoir �t� dessin� */
/* ATTENTION : Elle supporte AU MAXIMUM 6 tris (indice < 6).         */
void afficher_point(int indice, int pos, int valeur, int taille, int couleur);

/* Permet de faire une pause de "msec" millisecondes � l'�cran.      */
/* PARAM�TRE: msec - le temps de d�lai d�sir� en millisecondes.      */
void delai_ecran(int msec);
	
/* Retourne 1 si une touche a �t� pes�e, 0 sinon.                    */
int  touche_pesee();

/* Pour r�cup�rer un caract�re saisi dans la console graphique.      */
char obtenir_touche();
	
#endif
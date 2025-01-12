/*===========================================================*/
/*
 * Module : tri.h
 * Par    : Eya Cherni 
 * Date   : 2024-12-10
 *
 * Description :
 * Ce module contient les d�clarations des fonctions de tri
 *  appliqu�es � des tableaux dynamiques.

 /*===========================================================*/

#if !defined(tri)
#define tri 0


#include<assert.h>

#include "FILE.h" 

#define _CRT_SECURE_NO_WARNINGS 


 /*
 Nom : tri_insertion

 Param�tres :
 - int* tab : le tableau � trier.
 - int taille : la taille totale du tableau.
 -t_ptr_file historique

 Valeur de retour :
 aucune

 M�thode :
 Cette fonction effectue un tri par insertion classique. Elle utilise la fonction
 priv�e `tri_insertion_partiel` avec un intervalle de saut �gal � 1 pour ins�rer
 chaque �l�ment � sa position correcte dans le tableau.
 */

void tri_insertion(int* tab, int taille, t_ptr_file historique);



/*
Nom : tri_selection

Param�tres :
- int* tab : le tableau � trier.
- int taille : la taille totale du tableau.
-t_ptr_file historique

Valeur de retour :
aucune

M�thode :
Cette fonction impl�mente le tri par s�lection. Pour chaque position dans le tableau,
elle identifie l'�l�ment minimum dans la portion non tri�e � l'aide de la fonction
priv�e `pos_minimum` et �change cet �l�ment avec celui � la position actuelle
en utilisant `permuter_tab`.
*/

void tri_selection(int* tab, int taille, t_ptr_file historique);



/*
Nom : tri_cocktail

Param�tres :
- int* tab : le tableau � trier.
- int taille : la taille totale du tableau.
-t_ptr_file historique

Valeur de retour :
aucune

M�thode :
Cette fonction impl�mente le tri cocktail, une variante am�lior�e du tri � bulles.
Elle effectue des passes successives dans les deux sens (gauche-droite et
droite-gauche) pour d�placer les plus grands �l�ments vers la fin et les plus
petits vers le d�but, tout en r�duisant la plage de tri � chaque it�ration.
*/

void tri_cocktail(int* tab, int taille, t_ptr_file historique);


/* Nom : tri_shell
Param�tres :
�	int a : index qui parcours les �l�ments du tableau
�	int saut : l'intervalle courant
Valeur de retour : aucune
M�thode : Cette fonction impl�mente le tri Shell,
en faisant appel � la fonciton tri_insertion_partiel
pour l'enti�ret� des valeurs du tableau. */
void tri_Shell(int tab[], int taille, t_ptr_file historiques);


/********************************************
// Nom : tri_monceau
//********************************************
/* Param�tres :
   � int tab[] : tableau d'entiers � trier.
   � int taille : taille initiale du tableau.
   � t_ptr_file historiques : pointeur vers la file pour enregistrer les op�rations.
   Valeur de retour : aucune.
   M�thode : Cette fonction effectue un tri par tas (Heap Sort) en deux �tapes :
   1. Construction d'un tas max � partir du tableau.
   2. Extraction des �l�ments tri�s en r�organisant le tas apr�s chaque extraction. */

void tri_monceau(int tab[], int taille, t_ptr_file historiques);

/* Nom : tri_rapide
Param�tres :
�	int tab[]: le tableau des donn�es
�	int taille: la taille du tableau
�	t_ptr_fil historiques: l'historique
Valeur de retour : aucune
M�thode : Cette fonction vient faire appel � la fonction priv� du quicksort pour effectuer
l'algorithme r�cursif de la fonction */

void tri_rapide(int tab[], int taille, t_ptr_file historiques);

#endif
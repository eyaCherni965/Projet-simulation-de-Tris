/*===========================================================*/
/*
 * Module : tri.h
 * Par    : Eya Cherni 
 * Date   : 2024-12-10
 *
 * Description :
 * Ce module contient les déclarations des fonctions de tri
 *  appliquées à des tableaux dynamiques.

 /*===========================================================*/

#if !defined(tri)
#define tri 0


#include<assert.h>

#include "FILE.h" 

#define _CRT_SECURE_NO_WARNINGS 


 /*
 Nom : tri_insertion

 Paramètres :
 - int* tab : le tableau à trier.
 - int taille : la taille totale du tableau.
 -t_ptr_file historique

 Valeur de retour :
 aucune

 Méthode :
 Cette fonction effectue un tri par insertion classique. Elle utilise la fonction
 privée `tri_insertion_partiel` avec un intervalle de saut égal à 1 pour insérer
 chaque élément à sa position correcte dans le tableau.
 */

void tri_insertion(int* tab, int taille, t_ptr_file historique);



/*
Nom : tri_selection

Paramètres :
- int* tab : le tableau à trier.
- int taille : la taille totale du tableau.
-t_ptr_file historique

Valeur de retour :
aucune

Méthode :
Cette fonction implémente le tri par sélection. Pour chaque position dans le tableau,
elle identifie l'élément minimum dans la portion non triée à l'aide de la fonction
privée `pos_minimum` et échange cet élément avec celui à la position actuelle
en utilisant `permuter_tab`.
*/

void tri_selection(int* tab, int taille, t_ptr_file historique);



/*
Nom : tri_cocktail

Paramètres :
- int* tab : le tableau à trier.
- int taille : la taille totale du tableau.
-t_ptr_file historique

Valeur de retour :
aucune

Méthode :
Cette fonction implémente le tri cocktail, une variante améliorée du tri à bulles.
Elle effectue des passes successives dans les deux sens (gauche-droite et
droite-gauche) pour déplacer les plus grands éléments vers la fin et les plus
petits vers le début, tout en réduisant la plage de tri à chaque itération.
*/

void tri_cocktail(int* tab, int taille, t_ptr_file historique);


/* Nom : tri_shell
Paramètres :
•	int a : index qui parcours les éléments du tableau
•	int saut : l'intervalle courant
Valeur de retour : aucune
Méthode : Cette fonction implémente le tri Shell,
en faisant appel à la fonciton tri_insertion_partiel
pour l'entièreté des valeurs du tableau. */
void tri_Shell(int tab[], int taille, t_ptr_file historiques);


/********************************************
// Nom : tri_monceau
//********************************************
/* Paramètres :
   • int tab[] : tableau d'entiers à trier.
   • int taille : taille initiale du tableau.
   • t_ptr_file historiques : pointeur vers la file pour enregistrer les opérations.
   Valeur de retour : aucune.
   Méthode : Cette fonction effectue un tri par tas (Heap Sort) en deux étapes :
   1. Construction d'un tas max à partir du tableau.
   2. Extraction des éléments triés en réorganisant le tas après chaque extraction. */

void tri_monceau(int tab[], int taille, t_ptr_file historiques);

/* Nom : tri_rapide
Paramètres :
•	int tab[]: le tableau des données
•	int taille: la taille du tableau
•	t_ptr_fil historiques: l'historique
Valeur de retour : aucune
Méthode : Cette fonction vient faire appel à la fonction privé du quicksort pour effectuer
l'algorithme récursif de la fonction */

void tri_rapide(int tab[], int taille, t_ptr_file historiques);

#endif
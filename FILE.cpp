/*===========================================================*/
/*

 Module : FILE.cpp

 Par    : Eya Cherni

 Date   : 2024-12-10

 Ce module implémente les opérations de base sur une file dynamique,
 notamment la création, l'ajout, la suppression, et les vérifications
 d'état (pleine, vide).

*/
/*===========================================================*/

#include<stdlib.h>
#include "FILE.h" 

//******************************
// CREER FILE
//******************************
// Crée une nouvelle file dynamique vide, 
// prête à être utilisée pour y ajouter des éléments.

t_ptr_file creer_file(void)
{

	t_ptr_file file = (t_file*)(malloc(sizeof(t_file)));

	if (file == NULL) return NULL;


	file->debut = 0;

	file->fin = TAILLE_MAXIMALE - 1;

	file->total = 0;

	return file;

}


//******************************
// ENFILER
//******************************
// Ajoute un élément à la fin de la file, déplaçant les
// éléments si nécessaire pour laisser de la place.

int enfiler(t_ptr_file file, const t_operation* ajout)
{

	if (file->total == TAILLE_MAXIMALE) {    //si file plaine
		return 0;
	}

	file->fin = (file->fin + 1) % TAILLE_MAXIMALE;

	file->donnees[file->fin] = *ajout;

	file->total++;

	return 1;

}


//******************************
// DEFILER
//******************************
// Retire l'élément situé en tête de la file et réorganise 
// les autres éléments pour combler l'espace laissé.

int defiler(t_ptr_file file, t_operation* soustrait)
{
	if (file->total == 0) {   //si file vide 
		return 0;
	}

	*soustrait = file->donnees[file->debut];

	file->debut = (file->debut + 1) % TAILLE_MAXIMALE;

	file->total--;

	return 1;
}


//******************************  
// EST PLEINE
//******************************
// Vérifie si la file a atteint sa capacité maximale, empêchant ainsi l'ajout 
// d'autres éléments.

int est_pleine(const t_ptr_file file)
{
	return (file->total == TAILLE_MAXIMALE);

}


//******************************
// EST VIDE
//******************************
// Vérifie si la file ne contient aucun élément, ce qui empêche toute tentative de retrait.

int est_vide(const t_ptr_file file) {

	return (file->total == 0);

}


//******************************
// LONGUEUR
//******************************
// Calcule et renvoie le nombre actuel d'éléments présents dans la file.

int longueur(const t_ptr_file file)
{
	return file->total;
}


//******************************
// LIBERER FILE
//******************************
// Libère la mémoire allouée pour la file et détruit sa structure, 
// permettant de la recréer si nécessaire.

void liberer_file(t_ptr_file file)
{
	free(file);

	file = NULL;
}
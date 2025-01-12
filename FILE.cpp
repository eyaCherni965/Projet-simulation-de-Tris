/*===========================================================*/
/*

 Module : FILE.cpp

 Par    : Eya Cherni

 Date   : 2024-12-10

 Ce module impl�mente les op�rations de base sur une file dynamique,
 notamment la cr�ation, l'ajout, la suppression, et les v�rifications
 d'�tat (pleine, vide).

*/
/*===========================================================*/

#include<stdlib.h>
#include "FILE.h" 

//******************************
// CREER FILE
//******************************
// Cr�e une nouvelle file dynamique vide, 
// pr�te � �tre utilis�e pour y ajouter des �l�ments.

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
// Ajoute un �l�ment � la fin de la file, d�pla�ant les
// �l�ments si n�cessaire pour laisser de la place.

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
// Retire l'�l�ment situ� en t�te de la file et r�organise 
// les autres �l�ments pour combler l'espace laiss�.

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
// V�rifie si la file a atteint sa capacit� maximale, emp�chant ainsi l'ajout 
// d'autres �l�ments.

int est_pleine(const t_ptr_file file)
{
	return (file->total == TAILLE_MAXIMALE);

}


//******************************
// EST VIDE
//******************************
// V�rifie si la file ne contient aucun �l�ment, ce qui emp�che toute tentative de retrait.

int est_vide(const t_ptr_file file) {

	return (file->total == 0);

}


//******************************
// LONGUEUR
//******************************
// Calcule et renvoie le nombre actuel d'�l�ments pr�sents dans la file.

int longueur(const t_ptr_file file)
{
	return file->total;
}


//******************************
// LIBERER FILE
//******************************
// Lib�re la m�moire allou�e pour la file et d�truit sa structure, 
// permettant de la recr�er si n�cessaire.

void liberer_file(t_ptr_file file)
{
	free(file);

	file = NULL;
}
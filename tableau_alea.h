/*===========================================================*/
/*
 * Module : ALEA.h
 * Par    : Eya Cherni 
 * Date   : 2024-12-10
 *
 * Description :
 * Ce module contient les fonctions pour initialiser un tableau
 * avec des valeurs aléatoires et pour copier les valeurs d'un
 * tableau source vers un tableau destination.
 /*===========================================================*/

#if !defined(ALEA)
#define ALEA 0

#include <stdlib.h> 


void initialiser_tableau_aleatoire(int tab[], int taille);


void copier_tableau(int tab_dest[], const int tab_src[], int taille);

#endif


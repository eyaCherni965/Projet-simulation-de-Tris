/*===========================================================*/
/*
 Module : Module principal
 Par    : Eya Eya Cherni 
 Date   : 2024-12-10

 Description :
 Ce module implémente la simulation graphique de six tris
 (insertion, sélection, cocktail, etc.) à partir de tableaux dynamiques.
 Il permet d'initialiser les tableaux, de trier, et de visualiser les
 opérations dans un environnement graphique.
*/
/*===========================================================*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles à inclure 
#include<stdio.h>

#include<stdlib.h>

#include<math.h>

#include <time.h>

#include <stdio.h>

#include "tri.h" 

#include "tableau_alea.h"

#include "Affichages.h"  

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
#define TAILLE_TAB  300       //taille maximale du tableau

#define NB_TRIS  6           //nombre de tris possible


/*=========================================================*/
/*=========================================================*/

typedef struct {
	char nom[25];		  /* Le nom du tri */
	int* tab_tri;         /* Le tableau des valeurs à trier */
	t_ptr_file historiques;
} t_info_tri;



int creer_tab_tris(t_info_tri tris[]);

void liberer_tris(t_info_tri tris[]);



void afficher_tris_depart(const int tab[], t_info_tri tris[]);



void afficher_points_depart(const int tab[], int indice_tri);


void creer_historiques_tris(const int tab[], t_info_tri tris_a_tester[]);



void afficher_operation_tri(int no_tri, int tab[], t_operation* oper);



void simulation(t_info_tri tris[], int delai);

//Programme principal:
int main(void)
{

	int tab_alea[TAILLE_TAB];

	int nb_oper;   // Pour recevoir le nombre d'opérations dans les historiques.

	int delai = 5;    // Délai pour la simulation (peut être ajusté).


	t_info_tri tris_a_tester[NB_TRIS] = { {"Tri par Insertion", NULL,NULL},
										{"Tri par Selection", NULL,NULL},
										{"Tri Cocktail",      NULL,NULL},
										{"Tri Shell",         NULL,NULL},
										{"Tri par Monceau",   NULL,NULL},
										{"Tri Quicksort",     NULL,NULL} };


	srand(time(NULL));  // Initialiser le générateur de nombres aléatoires

	initialiser_tableau_aleatoire(tab_alea, TAILLE_TAB);


	// 2. Création des tableaux dynamiques
	if (!creer_tab_tris(tris_a_tester))
	{
		printf("Erreur lors de l'allocation des tableaux dynamiques. Fin du programme.\n");
		return 1;
	}

	// 3. Création des historiques de tris
	creer_historiques_tris(tab_alea, tris_a_tester);

	// 4. Initialisation du mode graphique
	ouvrir_mode_graphique();


	// 5. Affichage de l'état initial des tris
	afficher_tris_depart(tab_alea, tris_a_tester);


	// Simulation graphique
	simulation(tris_a_tester, delai);

	//libération de l'espace une fois terminé
	fermer_mode_graphique();

	liberer_tris(tris_a_tester);

	return 0;
}


//******************************
// creer_tab_tris
//******************************
/* Cette fonction initialise un tableau de structures "t_info_tri".
   Elle alloue dynamiquement la mémoire pour chaque tableau de tri et sa file historique.
   En cas d'échec d'une allocation, les ressources précédentes sont libérées,
   un message d'erreur est affiché, et la fonction retourne 0.
   Retourne 1 si toutes les allocations réussissent. */

int creer_tab_tris(t_info_tri tris[])
{
	int i; //les éléments du tableau

	//boucle for pour inclure l'ensemble des éléments du tableau
	for (i = 0; i < NB_TRIS; i++)
	{
		//allocation de la mémoire
		tris[i].tab_tri = (int*)malloc(TAILLE_TAB * sizeof(int));

		//si l'allocation échoue
		if (tris[i].tab_tri == NULL)
		{
			//on libère les allocations précédentes, on affiche un message
			printf("L'allocation a échoué pour le tri : %s\n", tris[i].nom);
			liberer_tris(tris);

			//et on retourne 0
			return 0;
		}

		// Appel à creer_file() pour initialiser historiques
		tris[i].historiques = creer_file();


		if (tris[i].historiques == NULL) {

			printf("L'allocation de la file a échoué pour le tri : %s\n", tris[i].nom);

			liberer_tris(tris); // Libère les ressources précédentes

			return 0; // Retourne 0 si l'allocation échoue
		}
	}

	//on retourne 1 si toutes les allocation sont réussies
	return 1;

}

//******************************
// liberer_tris
//******************************
/* Cette fonction libère la mémoire allouée pour les tableaux de tri
  et leurs files historiques dans le tableau "tris".
  Elle met les pointeurs à NULL pour éviter les accès invalides. */

void liberer_tris(t_info_tri tris[])
{
	int i;  //index pour la boucle


	//boucle for qui inclue l'ensemble des éléments
	for (i = 0; i < NB_TRIS; i++)
	{
		//on libère l'espace mémoire
		free(tris[i].tab_tri);

		//le pointeur devient NULL
		tris[i].tab_tri = NULL;

		liberer_file(tris[i].historiques);

		tris[i].historiques = NULL;
	}

}

//******************************
// afficher_points_depart
//******************************
/* Cette fonction affiche les points de départ d'un tableau "tab" pour un tri donné.
   Chaque point est affiché en couleur blanche à l'aide de la fonction "afficher_point". */

void afficher_points_depart(const int tab[], int indice_tri)
{
	int i; //index pour la boucle


	for (i = 0; i < TAILLE_TAB; i++)
	{
		//on affiche les point en couleur BLANCHE grâce à la fonction

		afficher_point(indice_tri, i, tab[i], TAILLE_TAB, BLANC);

	}

}

//******************************
// afficher_tris_depart
//******************************
/* Cette fonction affiche les points de départ pour chaque tri dans le tableau "tris".
   Pour chaque tri, elle copie le tableau de tri, affiche le cadre associé,
   puis affiche les points de départ à l'aide de la fonction "afficher_points_depart". */

void afficher_tris_depart(const int tab[], t_info_tri tris[])
{
	int i; //index pour la boucle

	//pour l’ensemble des tris

	for (i = 0; i < NB_TRIS; i++)
	{
		//on copie le tableau
		copier_tableau(tris[i].tab_tri, tab, TAILLE_TAB);

		//on affiche son cadre
		afficher_cadre_tri(i, tris[i].nom, TAILLE_TAB, longueur(tris[i].historiques));

		//et on affiche les points de départs
		afficher_points_depart(tris[i].tab_tri, i);

	}


}

//******************************
//  CREER HISTORIQUES TRIS
//******************************
/* Cette fonction trie une copie de « tab[] » (dans « .tab_tri[] »)  */
/* pour chaque tri dans « tris_a_tester[] ». Elle crée l'historique  */
/* (la file des lectures et écritures)
pour chacun des NB_TRIS tris.(commentaire pris de l`énoncé */


void creer_historiques_tris(const int tab[], t_info_tri tris_a_tester[])
{

	for (int i = 0; i < NB_TRIS; i++) {

		copier_tableau(tris_a_tester[i].tab_tri, tab, TAILLE_TAB);

		switch (i)
		{
		case 0: tri_insertion(tris_a_tester[i].tab_tri, TAILLE_TAB,
			tris_a_tester[i].historiques);

			break;

		case 1: tri_selection(tris_a_tester[i].tab_tri, TAILLE_TAB,
			tris_a_tester[i].historiques);
			break;


		case 2: tri_cocktail(tris_a_tester[i].tab_tri, TAILLE_TAB,
			tris_a_tester[i].historiques);

			break;

		case 3: tri_Shell(tris_a_tester[i].tab_tri, TAILLE_TAB,
			tris_a_tester[i].historiques);

			break;

		case 4: tri_monceau(tris_a_tester[i].tab_tri, TAILLE_TAB,
			tris_a_tester[i].historiques);

			break;

		case 5: tri_rapide(tris_a_tester[i].tab_tri, TAILLE_TAB,
			tris_a_tester[i].historiques);

			break;

		}
	}
}


//******************************
//  AFFICHER OPÉRATION TRI
//******************************
// Permet d'afficher une opération d'écriture dans l'interface graphique
// pour le tri #no_tri. Efface le point actuel dans le tableau à l'indice
// "oper->indice" (en le dessinant en NOIR), effectue la mise à jour
// dans le tableau avec "oper->valeur", puis réaffiche le point
// mis à jour en JAUNE.

void afficher_operation_tri(int no_tri, int tab[], t_operation* oper)
{

	afficher_point(no_tri, oper->indice, tab[oper->indice], TAILLE_TAB, NOIR);

	tab[oper->indice] = oper->valeur;

	afficher_point(no_tri, oper->indice, tab[oper->indice], TAILLE_TAB, JAUNE);

}


//******************************
// simulation
//******************************
/* Cette fonction simule l'exécution de plusieurs tris en parallèle.
 Elle extrait et traite les opérations des files "historiques" associées à chaque tri,
 les affiche si nécessaire, et contrôle l'arrêt via une touche ou la fin des opérations. */

void simulation(t_info_tri tris[], int delai) {

	int i; //le nombre de tris

	int nb_operations; //compte le nombre d’opérations extraits à chaque tour de boucle

	int termine = 1; //indique si tous les tris sont terminés ou non

	t_operation une_operation;  //pour récupérer une opération d’une des files d’historiques 


    //message pour débuter la simulation
	afficher_message("appuyez sur une touche pour demarrer\n"); 

	//attente d'une touche pour démarrer le programme
	obtenir_touche();

	//message pour terminer la simulation
	afficher_message("simulation en cours,appuyez sur une touche pour l'arreter\n");

	do
	{
		nb_operations = 0;

		for (i = 0; i < NB_TRIS; i++)
		{
			if (!est_vide(tris[i].historiques))
			{
				defiler(tris[i].historiques, &une_operation);
				nb_operations++;


				if (une_operation.type_operation == ECRITURE)
				{
					afficher_operation_tri(i, tris[i].tab_tri, &une_operation);
				}
			}
		}

		delai_ecran(delai);

		if (touche_pesee())
		{
			termine = 0;
			break;
		}


	} while (nb_operations > 0);

	if (termine == 1)
	{
		afficher_message("simulation terminee\n");
	}

	else
	{
		afficher_message("simulation avortee\n");
	}

}


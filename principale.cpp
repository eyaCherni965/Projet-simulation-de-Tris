/*===========================================================*/
/*
 Module : Module principal
 Par    : Eya Eya Cherni 
 Date   : 2024-12-10

 Description :
 Ce module impl�mente la simulation graphique de six tris
 (insertion, s�lection, cocktail, etc.) � partir de tableaux dynamiques.
 Il permet d'initialiser les tableaux, de trier, et de visualiser les
 op�rations dans un environnement graphique.
*/
/*===========================================================*/

//Permet de d�sactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles � inclure 
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
	int* tab_tri;         /* Le tableau des valeurs � trier */
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

	int nb_oper;   // Pour recevoir le nombre d'op�rations dans les historiques.

	int delai = 5;    // D�lai pour la simulation (peut �tre ajust�).


	t_info_tri tris_a_tester[NB_TRIS] = { {"Tri par Insertion", NULL,NULL},
										{"Tri par Selection", NULL,NULL},
										{"Tri Cocktail",      NULL,NULL},
										{"Tri Shell",         NULL,NULL},
										{"Tri par Monceau",   NULL,NULL},
										{"Tri Quicksort",     NULL,NULL} };


	srand(time(NULL));  // Initialiser le g�n�rateur de nombres al�atoires

	initialiser_tableau_aleatoire(tab_alea, TAILLE_TAB);


	// 2. Cr�ation des tableaux dynamiques
	if (!creer_tab_tris(tris_a_tester))
	{
		printf("Erreur lors de l'allocation des tableaux dynamiques. Fin du programme.\n");
		return 1;
	}

	// 3. Cr�ation des historiques de tris
	creer_historiques_tris(tab_alea, tris_a_tester);

	// 4. Initialisation du mode graphique
	ouvrir_mode_graphique();


	// 5. Affichage de l'�tat initial des tris
	afficher_tris_depart(tab_alea, tris_a_tester);


	// Simulation graphique
	simulation(tris_a_tester, delai);

	//lib�ration de l'espace une fois termin�
	fermer_mode_graphique();

	liberer_tris(tris_a_tester);

	return 0;
}


//******************************
// creer_tab_tris
//******************************
/* Cette fonction initialise un tableau de structures "t_info_tri".
   Elle alloue dynamiquement la m�moire pour chaque tableau de tri et sa file historique.
   En cas d'�chec d'une allocation, les ressources pr�c�dentes sont lib�r�es,
   un message d'erreur est affich�, et la fonction retourne 0.
   Retourne 1 si toutes les allocations r�ussissent. */

int creer_tab_tris(t_info_tri tris[])
{
	int i; //les �l�ments du tableau

	//boucle for pour inclure l'ensemble des �l�ments du tableau
	for (i = 0; i < NB_TRIS; i++)
	{
		//allocation de la m�moire
		tris[i].tab_tri = (int*)malloc(TAILLE_TAB * sizeof(int));

		//si l'allocation �choue
		if (tris[i].tab_tri == NULL)
		{
			//on lib�re les allocations pr�c�dentes, on affiche un message
			printf("L'allocation a �chou� pour le tri : %s\n", tris[i].nom);
			liberer_tris(tris);

			//et on retourne 0
			return 0;
		}

		// Appel � creer_file() pour initialiser historiques
		tris[i].historiques = creer_file();


		if (tris[i].historiques == NULL) {

			printf("L'allocation de la file a �chou� pour le tri : %s\n", tris[i].nom);

			liberer_tris(tris); // Lib�re les ressources pr�c�dentes

			return 0; // Retourne 0 si l'allocation �choue
		}
	}

	//on retourne 1 si toutes les allocation sont r�ussies
	return 1;

}

//******************************
// liberer_tris
//******************************
/* Cette fonction lib�re la m�moire allou�e pour les tableaux de tri
  et leurs files historiques dans le tableau "tris".
  Elle met les pointeurs � NULL pour �viter les acc�s invalides. */

void liberer_tris(t_info_tri tris[])
{
	int i;  //index pour la boucle


	//boucle for qui inclue l'ensemble des �l�ments
	for (i = 0; i < NB_TRIS; i++)
	{
		//on lib�re l'espace m�moire
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
/* Cette fonction affiche les points de d�part d'un tableau "tab" pour un tri donn�.
   Chaque point est affich� en couleur blanche � l'aide de la fonction "afficher_point". */

void afficher_points_depart(const int tab[], int indice_tri)
{
	int i; //index pour la boucle


	for (i = 0; i < TAILLE_TAB; i++)
	{
		//on affiche les point en couleur BLANCHE gr�ce � la fonction

		afficher_point(indice_tri, i, tab[i], TAILLE_TAB, BLANC);

	}

}

//******************************
// afficher_tris_depart
//******************************
/* Cette fonction affiche les points de d�part pour chaque tri dans le tableau "tris".
   Pour chaque tri, elle copie le tableau de tri, affiche le cadre associ�,
   puis affiche les points de d�part � l'aide de la fonction "afficher_points_depart". */

void afficher_tris_depart(const int tab[], t_info_tri tris[])
{
	int i; //index pour la boucle

	//pour l�ensemble des tris

	for (i = 0; i < NB_TRIS; i++)
	{
		//on copie le tableau
		copier_tableau(tris[i].tab_tri, tab, TAILLE_TAB);

		//on affiche son cadre
		afficher_cadre_tri(i, tris[i].nom, TAILLE_TAB, longueur(tris[i].historiques));

		//et on affiche les points de d�parts
		afficher_points_depart(tris[i].tab_tri, i);

	}


}

//******************************
//  CREER HISTORIQUES TRIS
//******************************
/* Cette fonction trie une copie de � tab[] � (dans � .tab_tri[] �)  */
/* pour chaque tri dans � tris_a_tester[] �. Elle cr�e l'historique  */
/* (la file des lectures et �critures)
pour chacun des NB_TRIS tris.(commentaire pris de l`�nonc� */


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
//  AFFICHER OP�RATION TRI
//******************************
// Permet d'afficher une op�ration d'�criture dans l'interface graphique
// pour le tri #no_tri. Efface le point actuel dans le tableau � l'indice
// "oper->indice" (en le dessinant en NOIR), effectue la mise � jour
// dans le tableau avec "oper->valeur", puis r�affiche le point
// mis � jour en JAUNE.

void afficher_operation_tri(int no_tri, int tab[], t_operation* oper)
{

	afficher_point(no_tri, oper->indice, tab[oper->indice], TAILLE_TAB, NOIR);

	tab[oper->indice] = oper->valeur;

	afficher_point(no_tri, oper->indice, tab[oper->indice], TAILLE_TAB, JAUNE);

}


//******************************
// simulation
//******************************
/* Cette fonction simule l'ex�cution de plusieurs tris en parall�le.
 Elle extrait et traite les op�rations des files "historiques" associ�es � chaque tri,
 les affiche si n�cessaire, et contr�le l'arr�t via une touche ou la fin des op�rations. */

void simulation(t_info_tri tris[], int delai) {

	int i; //le nombre de tris

	int nb_operations; //compte le nombre d�op�rations extraits � chaque tour de boucle

	int termine = 1; //indique si tous les tris sont termin�s ou non

	t_operation une_operation;  //pour r�cup�rer une op�ration d�une des files d�historiques 


    //message pour d�buter la simulation
	afficher_message("appuyez sur une touche pour demarrer\n"); 

	//attente d'une touche pour d�marrer le programme
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


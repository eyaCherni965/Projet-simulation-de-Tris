/*===========================================================*/
/*
 * Module : tableau_alea.cpp
 * Par    : Eya Cherni 
 * Date   : 2024-12-10
 *
 * Description :
 *
 * Ce module contient les fonctions n�cessaires pour g�n�rer
 * des tableaux al�atoires et effectuer des permutations entre
 * les �l�ments de tableaux. Il permet de remplir un tableau
 * avec des valeurs uniques et de m�langer ces valeurs � l'aide
 * de permutations al�atoires. Le module inclut aussi une fonction
 * pour copier un tableau dans un autre.Contient 2 fonction priv�
 */
 /*===========================================================*/

#include "tableau_alea.h"

static int alea(int min, int max);


static void permuter(int* val1, int* val2);

static void permuter(int* val1, int* val2);



//******************************
// alea
//******************************
/*cette fonction permet de g�nerer des valeurs
al�atoires qui se situent entre min et max
gr�ce � la fonction rand()*/
static int alea(int min, int max)
{
	return min + rand() % (max - min + 1);
}


//******************************
// permuter
//******************************
/*cette fonction permet d'effectuer la permutation
entre deux valeurs enti�res*/
static void permuter(int* val1, int* val2)
{
	int temp; //variable suppl�mentaire pour faire la permutation

	temp = *val1;
	*val1 = *val2;
	*val2 = temp;

}


//******************************
// initialiser_tableau_aleatoire
//******************************
/*Cette fonction ins�re les valeurs de "taille" � 1 dans le tableau "tab".
Ensuite, elle effectue "2 * taille" permutations al�atoires pour ainsi
m�langer les "taille" valeurs sans qu'aucune valeur soit r�p�t�e.*/
void initialiser_tableau_aleatoire(int tab[], int taille)
{
	int i;  //chaque �l�ment du tableau
	int ind_1; //indice 1
	int ind_2; //indice 2

	//boucle for pour remplir le tableau de 1 � taille
	for (i = 0; i < taille; i++)
	{
		tab[i] = taille - i;
	}

	//boucle for pour m�langer les valeurs
	for (i = 0; i < 2 * taille; i++)
	{
		ind_1 = alea(0, taille - 1);
		ind_2 = alea(0, taille - 1);

		permuter(&tab[ind_1], &tab[ind_2]);
	}


}

//******************************
// copier_tableau
//******************************
/* Cette fonction copie les "taille" �l�ments de "tab_src" dans "tab_dest". */

void copier_tableau(int tab_dest[], const int tab_src[], int taille)
{
	int i; //les �l�ments du tableau

	//boucle for pour inclure l'ensemble du tableau
	for (i = 0; i < taille; i++)
	{
		tab_dest[i] = tab_src[i];
	}
}

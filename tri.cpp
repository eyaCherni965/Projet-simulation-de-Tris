
/*===========================================================*/
/*
 Module : tri.cpp
 Par    : Eya Eya Cherni 
 Date   : 2024-12-10

 Ce module offre une impl�mentation compl�te de plusieurs algorithmes
 de tri et de gestion de structures de donn�es, con�us pour fonctionner
 avec un m�canisme de journalisation des op�rations � l'aide d'une file
 historique.Il contient 5 fonctions priv�

/*=========================================================*/

#include "tri.h"
#include "FILE.h" 

//Prototype des fonctions priv�  



static int pos_minimum(const int* tab, int debut, int taille, t_ptr_file historique);



static void permuter_tab(int* tab, int a, int b, t_ptr_file historique);


static void tri_insertion_partiel(int* tab, int taille, int saut, t_ptr_file historique);


static int  lecture(const int* tab, int indice, t_ptr_file file);


static void ecriture(int* tab, int indice, int valeur, t_ptr_file file);

                                                                           
static void maintenir_monceau(int tab[], int pos_depart, int taille, t_ptr_file historique);


static void quicksort(int* tab, int debut, int fin, t_ptr_file histo);



//******************************
// pos_minimum
//******************************
/* Fonction qui retourne l�indice de la valeur minimale du tableau qui
se trouve entre les cases [d�but] et [taille-1] inclusivement. */

static int pos_minimum(const int* tab, int debut, int taille, t_ptr_file historique)
{
	int ligne;

	int pos_min = debut; // Initialise la position minimum � debut 

	int valeur_actuelle;

	int valeur_min = lecture(tab, debut, historique); // Lecture unique 

	// Boucle pour trouver la position du min 
	for (ligne = debut + 1; ligne < taille; ligne++) {

		valeur_actuelle = lecture(tab, ligne, historique); // Lecture unique 

		// Si �l�ment actuel est plus petit que le minimum 
		if (valeur_actuelle < valeur_min) {

			pos_min = ligne;   // pos_min = l'indice de l'�l�ment le plus petit trouv� 

			valeur_min = valeur_actuelle;

		}

	}

	return pos_min;
}


//******************************
// tri_selection
//******************************
/*Effectue un tri par s�lection sur un tableau.
Pour chaque position i, trouve l'�l�ment minimum dans la partie restante du tableau gr�ce
� la fonction pos_minimum.
�change la valeur minimale trouv�e avec celle � la position i en utilisant la
fonction permuter_tab.*/

void tri_selection(int* tab, int taille, t_ptr_file historique)

{
	int i;

	int pos_min;  //la position du minimum 

	int droite;

	for (i = 0; i < taille - 1; ++i) {   //la position de d�part de la recherche du min 

	    lecture(tab, i, historique);

		pos_min = pos_minimum(tab, i, taille, historique);

		permuter_tab(tab, i, pos_min, historique);


	}


}


//******************************
//permuter_tab
//******************************
/*�change deux �l�ments dans le tableau tab, entre les positions a et b.
Utilise une variable temporaire pour effectuer l'�change.
*/

static void permuter_tab(int* tab, int a, int b, t_ptr_file historique)
{
	int temp;

	int valeur_b;

	temp = lecture(tab, a, historique); // Lecture pour `temp` 

	valeur_b = lecture(tab, b, historique); // Lecture pour `tab[b]` 


	ecriture(tab, a, valeur_b, historique);  // Place l'�l�ment de `b` dans `a`
	ecriture(tab, b, temp, historique);       // Place la valeur sauvegard�e dans `b` 

}

//******************************
// tri_insertion_partiel
//******************************
/* Impl�mente une variante du tri par insertion qui permet de travailler avec des
intervalles d�finis par saut.
Ins�re chaque �l�ment � sa position correcte dans une sous-s�quence d�finie par saut.*/

static void tri_insertion_partiel(int* tab, int taille, int saut, t_ptr_file historique)

{
	int  i;

	int a_inserer;    //copie de la valeur � ins�rer 

	int position;    //indique la position APR�S laquelle on va ins�rer   

	int val; // pour lecture

	// On insere les n-1 elements de x[] dans la portion triee. 

	for (i = saut; i < taille; i += 1) {

		a_inserer = lecture(tab, i, historique);

		position = i - saut;

		// Tant que l'element a inserer est plus petit que ses precedents, 
		// on les deplacent. 

		while (position >= 0 && (val = lecture(tab, position, historique)) > a_inserer)
		{
			//ecriture(tab, pos + saut, val, file)
			ecriture(tab, position + saut, val, historique);

			position -= saut;

		}

		// On insere l'element tab[i] au bon endroit parmi les valeurs 
		// deja triees. 

		ecriture(tab, position + saut, a_inserer, historique);

	}

}



//******************************
// tri_insertion
//******************************
/*Effectue un tri par insertion classique.
Utilise la fonction tri_insertion_partiel avec un saut de 1 pour parcourir
le tableau de mani�re lin�aire.*/

void tri_insertion(int* tab, int taille, t_ptr_file historique)

{
	//tri effectu� avec des sauts de 1 
	tri_insertion_partiel(tab, taille, 1, historique);
}


//******************************
// tri_cocktail
//******************************
/*Impl�mente le tri cocktail (ou tri shake), une am�lioration du tri � bulles.
Alterne des passes gauche-droite et droite-gauche pour trier le tableau.
R�duit la plage de tri � chaque it�ration en d�pla�ant les plus
grands �l�ments vers la fin et les plus petits vers le d�but.*/

void tri_cocktail(int* tab, int taille, t_ptr_file historique)

{
	int debut = 0;         // Indice du d�but de la plage � trier 

	int fin = taille - 1;  // Indice de la fin de la plage � trier 

	int permutations = 1;  // Bool�en indiquant si une permutation a eu lieu 

	int j;

	int valeur_j;

	int valeur_j1;

	while (permutations) {

		permutations = 0; // R�initialiser � faux pour v�rifier s'il y a eu des �changes 


		// Passe gauche-droite 

		for (j = debut; j < fin; j++) {

			valeur_j = lecture(tab, j, historique);       // Lecture pour `tab[j]` 

			valeur_j1 = lecture(tab, j + 1, historique);  // Lecture pour `tab[j + 1]` 

			if (valeur_j > valeur_j1) {

				// �changer les �l�ments 

				ecriture(tab, j, valeur_j1, historique);
				ecriture(tab, j + 1, valeur_j, historique);

				permutations = 1; // Marquer qu'un �change a eu lieu 

			}

		}

		// R�duire la plage � droite (le dernier �l�ment est tri�) 

		fin--;

		// Passe droite-gauche 
		if (permutations)
			for (j = fin; j > debut; j--) {

				valeur_j = lecture(tab, j, historique);       // Lecture pour `tab[j]` 

				valeur_j1 = lecture(tab, j - 1, historique);  // Lecture pour `tab[j - 1]` 

				if (valeur_j1 > valeur_j) {

					// �changer les �l�ments 
					ecriture(tab, j, valeur_j1, historique);
					ecriture(tab, j - 1, valeur_j, historique);

					permutations = 1; // Marquer qu'un �change a eu lieu 
				}
			}
		// R�duire la plage � gauche (le premier �l�ment est tri�) 
		debut++;

	}
}



//******************************
// tri_Shell 
//******************************
/*Impl�mente le tri Shell en faisant appel � la fonction
tri_insertion_partiel pour l'enti�ret�
des valeurs du tableau*/

void tri_Shell(int tab[], int taille, t_ptr_file historiques)
{
	/* Liste des sauts pour semi-ordonner les donn�es. */

	const int tab_increments[6] = { 112, 48, 22, 7, 3, 1 };

	int i; //index qui parcours les �l�ments du tableau

	int saut; //l'intervalle courant


	//pour l'enti�ret� des valeurs du tableau
	for (i = 0; i < 6; i++)
	{

		saut = tab_increments[i];
		//on fait appel � la fonction tri_insertion_partiel
		//pour effectuer le tri
		tri_insertion_partiel(tab, taille, saut, historiques);

	}

}


//******************************
//  MAINTENIR LA STRUCTURE DU MONCEAU
//******************************
// R�organise un tableau pour pr�server la propri�t� de monceau (tas binaire max)
// en v�rifiant et permutant la valeur � "pos_depart" avec le plus grand de ses fils,
// tout en enregistrant les permutations dans "historique".

static void maintenir_monceau(int tab[], int pos_depart, int taille, t_ptr_file historique) {


	int valeur;        // La valeur � la position pos_depart

	int fils_gauche;   // La valeur du fils-gauche

	int fils_droite;   // La valeur du fils-droit


	// �tape 1 : Si la position � pos_depart � a un fils-gauche valide
	if ((2 * pos_depart + 1) < taille) {

		//  valeur -> la valeur dans � tab[pos_depart] �
		valeur = lecture(tab, pos_depart, historique);

		// fils_gauche ->la valeur dans � tab[pos_depart*2 + 1] �
		fils_gauche = lecture(tab, 2 * pos_depart + 1, historique);


		if (2 * pos_depart + 2 < taille) {

			fils_droite = lecture(tab, 2 * pos_depart + 2, historique);


			// V�rifier si le fils-droit est plus grand que le fils-gauche
			if (fils_droite > fils_gauche) {

				//  Si � valeur � est plus petite que celle du fils-droit
				if (valeur < fils_droite) {

					permuter_tab(tab, pos_depart, 2 * pos_depart + 2, historique);

					// Appel r�cursif pour r�organiser l�arbre sous le fils droit

					maintenir_monceau(tab, 2 * pos_depart + 2, taille, historique);
				}
			}
			else

				//  Si � valeur � est plus petite que celle du fils-gauche
				if (valeur < fils_gauche) {

					permuter_tab(tab, pos_depart, 2 * pos_depart + 1, historique);

					// Appel r�cursif pour r�organiser l�arbre sous le fils gauche
					maintenir_monceau(tab, 2 * pos_depart + 1, taille, historique);
				}
		}

		else

			//  Si � valeur � est plus petite que celle du fils-gauche
			if (valeur < fils_gauche) {

				permuter_tab(tab, pos_depart, 2 * pos_depart + 1, historique);

				// Appel r�cursif pour r�organiser l�arbre sous le fils gauche
				maintenir_monceau(tab, 2 * pos_depart + 1, taille, historique);
			}

	}
}


//******************************
// Tri_Monceau
//******************************
/* Cette fonction effectue un tri par tas (Heap Sort) sur un tableau d'entiers donn�.
   Elle utilise une structure de file pour enregistrer les op�rations historiques
   r�alis�es pendant le tri.*/

void tri_monceau(int tab[], int taille, t_ptr_file historiques)
{

	// Construction du monceau
	for (int pos = taille - 1; pos >= 0; pos--) {
		maintenir_monceau(tab, pos, taille, historiques);
	}

	while (taille > 1) {
		// �changer la racine avec le dernier �l�ment du tas
		permuter_tab(tab, 0, taille - 1, historiques);

		// R�duire la taille du tas
		taille--;

		// R�organiser le tas � partir de la racine
		maintenir_monceau(tab, 0, taille, historiques);
	}
}


//******************************
// quicksort
//******************************
/* Cette fonction r�alise un tri rapide sur un tableau d'entiers,
   en enregistrant les op�rations dans la file "histo". */

static void quicksort(int* tab, int debut, int fin, t_ptr_file histo) {

	int i = debut;

	int j = fin;

	int vdebut; int v1; int v2;
	do {

		vdebut = lecture(tab, debut, histo);

		while ((i <= fin) && ((v1 = lecture(tab, i, histo)) <= vdebut)) i++;
		while ((j >= debut) && ((v2 = lecture(tab, j, histo)) > vdebut)) j--;

		if (i < j)
		{

			ecriture(tab, j, v1, histo);
			ecriture(tab, i, v2, histo);
			//permuter_tab(tab, i, j, histo);    //faire deux ecriture()
			i++;
			j--;
		}

	} while (i <= j);

	permuter_tab(tab, debut, j, histo);

	if (debut < j - 1)
	{
		quicksort(tab, debut, j - 1, histo);
	}

	if (fin > j + 1)
	{
		quicksort(tab, j + 1, fin, histo);
	}

}


//******************************
 // tri_rapide
//******************************
/* Cette fonction applique le tri rapide sur un tableau d'entiers,
en utilisant "historiques" pour suivre les op�rations. */

void tri_rapide(int tab[], int taille, t_ptr_file historiques)
{

	quicksort(tab, 0, taille - 1, historiques);

}

//******************************
// lecture
//******************************
/* Effectue une op�ration de lecture sur un tableau d'entiers en fonction de l'indice sp�cifi�.
  La fonction cr�e une op�ration de type LECTURE et l'enfile dans une file.
  Si l'enfilage est r�ussi, elle renvoie la valeur lue � partir du tableau � l'indice donn�.
  Si l'enfilage �choue, elle renvoie 0. */

static int  lecture(const int* tab, int indice, t_ptr_file file)

{
	t_operation oper;

	oper.type_operation = LECTURE;  // Type d'op�ration : LECTURE  

	oper.indice = indice;           // L'indice de la valeur dans le tableau 

	oper.valeur = tab[indice];      // La valeur � lire depuis le tableau 

	if (enfiler(file, &oper)) {


		return tab[indice];

	}

	return 0;

}


//******************************
// ecriture
//******************************
/* Effectue une op�ration d'�criture dans un tableau d'entiers
� l'indice sp�cifi�. La fonction cr�e une op�ration de type
ECRITURE et l'enfile dans une file.Si l'enfilage r�ussit, elle �crit
la valeur dans le tableau � l'indice donn�. */

static void ecriture(int* tab, int indice, int valeur, t_ptr_file file)
{

	t_operation oper;   //variable locale pour stocker les d�tails n�cessaires � l'op�ration


	oper.type_operation = ECRITURE;  //sp�cifie letype d'op�ration (�criture)

	oper.indice = indice;  //indice o� �crire la valeur

	oper.valeur = valeur; //la valeur � �crire dans le tableau

	assert(enfiler(file, &oper)); //un assert pour ajouter l'op�ration � la file et v�rifier que �a a �t� r�ussi

	tab[indice] = valeur;  //�crit la valeur dans le tableau � l'indice sp�cifi�

}

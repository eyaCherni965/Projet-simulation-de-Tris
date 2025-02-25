/*******************************************************************************
	AFFICHAGES.h  (version pour le TP2, A24)  *** Ce module est DONN� aux �l�ves
	Auteurs : E.Th�

	Module qui contient les fonctions de gestion de l'affichage des tris en
	mode graphique avec des pixels. Offre aussi 3 petites fonctions utilitaires.
********************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>     //pour strlen()
#include "Affichages.h"
#include "winbgim.h"	//le module graphique est ENCAPSUL�E dans cette librairie

//Marge verticale avant la zone de visualisation des tris 
const int Y0 = 5;		//ajustez pour laisser de la place aux messages

//******************************
//  OUVRIR MODE GRAPHIQUE
//******************************
//Permet de cr�er et d'ouvrir la fen�tre d'affichage graphique
int ouvrir_mode_graphique(void) {
	int gdriver = DETECT, gmode, errorcode;

	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();

	return errorcode == grOk;
}

//******************************
//  FERMER MODE GRAPHIQUE
//******************************
//Permet de fermer la fen�tre d'affichage graphique
void fermer_mode_graphique(void) {
	closegraph();
}

//******************************
//  AFFICHER MESSAGE
//******************************
//Permet d'afficher un message dans la partie haut de la fen�tre graphique
void afficher_message(const char* mess) {
	/* On efface toute la zone du haut de l'�cran (22 pixels de hauteur) */
	setfillstyle(SOLID_FILL, BLACK);
	bar(0, 0, getmaxx(), 22);		//une barre horizontale noire sur toute la largueur

	settextstyle(1, HORIZ_DIR, 1);
	setcolor(JAUNE);
	/* Le texte sera centr� horizontalement avec: strlen()/2 * 12 (pixels par char) */
	outtextxy(getmaxx() / 2 - ((strlen(mess)/2) * 12), 2, mess);  
	setcolor(BLANC);
}

//******************************
//  AFFICHER CADRE TRI
//******************************
//Permet d'afficher le cadre #indice (de 0 � 5) d'un tri de "taille" valeurs.
//Affiche aussi le le nom du tri "nom_tri" au dessus du cadre et le nombre total 
//d'op�rations du tri "nb_oper" en bas du cadre.
void afficher_cadre_tri(int indice, const char* nom_tri, int taille, int nb_oper) {
	char buff[40];

	/* On affiche les axes et le titre.								*/
	settextstyle(1 /*SMALL_FONT*/, HORIZ_DIR, 2);

	/* Si l'indice inf�rieur � 3, nous sommes dans la premi�re moiti� de l'�cran. */
	if (indice < 3) {
		/* On affiche le titre.										*/
		outtextxy((indice + 1) * (getmaxx() - 3 * taille) / 4 + indice * taille
			      + (taille - textwidth(nom_tri)) / 2, 
			      Y0 + (getmaxy() / 2 - taille) / 4, nom_tri);

		/* On dessine l'axe des y.									*/
		line((indice + 1) * (getmaxx() - 3 * taille) / 4 + indice * taille,
			Y0 + (getmaxy() / 2 - taille) / 2,
			(indice + 1) * (getmaxx() - 3 * taille) / 4 + indice * taille,
			Y0 + getmaxy() / 2 - (getmaxy() / 2 - taille) / 2);

		/* On dessine l'axe des x.									*/
		line((indice + 1) * (getmaxx() - 3 * taille) / 4 + indice * taille,
			Y0 + getmaxy() / 2 - (getmaxy() / 2 - taille) / 2,
			(indice + 1) * (getmaxx() - 3 * taille) / 4 + (indice + 1) * taille + 1,
			Y0 + getmaxy() / 2 - (getmaxy() / 2 - taille) / 2);

		/* On affiche le nombre d'op�rations de la file pour ce tri. */
		sprintf(buff, "%d op�rations", nb_oper);
		settextstyle(0, HORIZ_DIR, 1);
		outtextxy((indice + 1) * (getmaxx() - 3 * taille) / 4 + indice * taille
			      + (taille - textwidth(buff)) / 2, Y0 + taille + 135, buff);
	}
	/* Sinon, nous sommes dans la deuxi�me moiti� de l'�cran. */
	else {
		/* On affiche le titre.										*/
		outtextxy((indice - 2) * (getmaxx() - 3 * taille) / 4 + (indice - 3) * taille
			      + (taille - textwidth(nom_tri)) / 2, 
				  Y0 + getmaxy() / 2 + (getmaxy() / 2 - taille) / 4, nom_tri);

		/* On dessine l'axe des y.									*/
		line((indice - 2) * (getmaxx() - 3 * taille) / 4 + (indice - 3) * taille,
			Y0 + getmaxy() / 2 + (getmaxy() / 2 - taille) / 2,
			(indice - 2) * (getmaxx() - 3 * taille) / 4 + (indice - 3) * taille,
			Y0 + getmaxy() - (getmaxy() / 2 - taille) / 2);

		/* On dessine l'axe des x.									*/
		line((indice - 2) * (getmaxx() - 3 * taille) / 4 + (indice - 3) * taille,
			Y0 + getmaxy() - (getmaxy() / 2 - taille) / 2,
			(indice - 2) * (getmaxx() - 3 * taille) / 4 + (indice - 2) * taille + 1,
			Y0 + getmaxy() - (getmaxy() / 2 - taille) / 2);

		/* On affiche le nombre d'op�rations de la file pour ce tri. */
		sprintf(buff, "%d op�rations", nb_oper);
		settextstyle(0, HORIZ_DIR, 1);
		outtextxy((indice - 2) * (getmaxx() - 3 * taille) / 4 + (indice - 3) * taille
			      + (taille - textwidth(buff)) / 2, Y0 + getmaxy() / 2 + taille + 135, buff);
	}
}

//******************************
//  AFFICHER POINT
//******************************
//Permet d'afficher le point "valeur" � la position "pos" (un pixel) avec la "couleur" 
//demand�e dans le cadre de tri #indice (de 0 � 5) d'un tri de "taille" valeurs.
void afficher_point(int indice, int pos, int valeur, int taille, int couleur) {

	/* Si l'indice inf�rieur � 3, nous sommes dans la premi�re moiti� de l'�cran. */
	if (indice < 3)
		/* Afficher le pixel � la position [x, y] re�ue avec la "couleur" donn�e. */
		putpixel((indice + 1) * (getmaxx() - 3 * taille) / 4 + indice * taille + 1 + pos,
			     Y0 + getmaxy() / 2 - (getmaxy() / 2 - taille) / 2 - 1 - valeur, couleur);
	/* Sinon, nous sommes dans la deuxi�me moiti� de l'�cran. */
	else
		/* Afficher le pixel � la position [x, y] re�ue avec la "couleur" donn�e. */
		putpixel((indice - 2) * (getmaxx() - 3 * taille) / 4 + (indice - 3) * taille + 1 + pos,
			     Y0 + getmaxy() - (getmaxy() / 2 - taille) / 2 - 1 - valeur, couleur);
}

//******************************
//  DELAI �CRAN
//******************************
//Permet de faire une pause de "msec" millisecondes � l'�cran
void delai_ecran(int msec) {
	delay_graph(msec);
}

//******************************
//  TOUCHE PESEE
//******************************
//Retourne 1 si une touche a �t� pes�e, 0 sinon.
int  touche_pesee() {
	return kbhit_graph();
}

//******************************
//  OBTENIR TOUCHE
//******************************
//Pour r�cup�rer un caract�re saisi dans la console graphique.
char obtenir_touche() {
	return getch_graph();
}

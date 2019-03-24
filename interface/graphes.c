/*
Copyright mars 2019, Stephan Runigo
runigo@free.fr
SiCF 2.0  simulateur de corde vibrante et spectre
Ce logiciel est un programme informatique servant à simuler l'équation
d'une corde vibrante, à calculer sa transformée de fourier, et à donner
une représentation graphique de ces fonctions.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée. Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard l'attention de l'utilisateur est attirée sur les risques
associés au chargement, à l'utilisation, à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant des connaissances informatiques approfondies. Les
utilisateurs sont donc invités à charger et tester l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "graphes.h"

int grapheInitialiseTaille(grapheT * graphe, int xZero, int yZero, int zoneX, int zoneY);

int grapheInitialise(grapheT * graphe, int nombre, int graisse, int r, int g, int b)
	{
		//		Initialisation du graphe

	grapheInitialiseTaille(graphe, 0, 0, FENETRE_X, FENETRE_Y);

	int i;

	for(i=0;i<NOMBRE_MAX;i++)
		{
		(*graphe).point[i].x=0;
		(*graphe).point[i].y=0;
		}

	(*graphe).couleur.r = r;
	(*graphe).couleur.g = g;
	(*graphe).couleur.b = b;
	(*graphe).couleur.a = 255;

	(*graphe).nombre = nombre; // Nombre de point
	(*graphe).graisse = graisse; // Epaisseur du trait

	return 0;
	}

int grapheInitialiseCorde(grapheT * graphe, int largeur, int hauteur)
	{
		//		Position et taille du graphe

	(*graphe).xZero = MARGE_X*largeur; // Positon de l'origine
	(*graphe).yZero = MARGE_Y*hauteur + GRAPHE_CORDE_Y*(hauteur/2); // Positon de l'origine

	(*graphe).largeur = GRAPHE_CORDE_X*largeur; // axe x
	(*graphe).hauteur = GRAPHE_CORDE_Y*hauteur; // axe y

	(*graphe).graisse = 5; // Positon de l'origine

	int i;
	float dx=(*graphe).largeur/(*graphe).nombre;
	for(i=0;i<(*graphe).nombre;i++)
		{
		(*graphe).point[i].x=(*graphe).xZero + (int)(i*dx);
		}
	return 0;
	}

int grapheInitialiseSpectre(grapheT * graphe, int largeur, int hauteur)
	{
		//		Position et taille du graphe

	(*graphe).xZero = MARGE_X*largeur; // Positon de l'origine
	(*graphe).yZero = MARGE_Y*hauteur + GRAPHE_SPECTRE_Y*(hauteur/2); // Positon de l'origine

	(*graphe).largeur = GRAPHE_SPECTRE_X*largeur; // axe x
	(*graphe).hauteur = GRAPHE_SPECTRE_Y*hauteur; // axe y

	(*graphe).graisse = 5; // Positon de l'origine

	int i;
	float dx=(*graphe).largeur/(*graphe).nombre;
	for(i=0;i<(*graphe).nombre;i++)
		{
		(*graphe).point[i].x=(*graphe).xZero + (int)(i*dx);
		}
	return 0;
	}

int grapheInitialiseTaille(grapheT * graphe, int xZero, int yZero, int zoneX, int zoneY)
	{
		//		Position et taille du graphe

	(*graphe).xZero = xZero; // Positon de l'origine
	(*graphe).yZero = yZero; // Positon de l'origine

	(*graphe).largeur = zoneX; // axe x
	(*graphe).hauteur = zoneY; // axe y

	return 0;
	}

//////////////////////////////////////////////////////////////////

/*
Copyright mars 2018, Stephan Runigo
runigo@free.fr
SiCP 1.6 simulateur de chaîne de pendules
Ce logiciel est un programme informatique servant à simuler l'équation
d'une chaîne de pendules et à en donner une représentation graphique.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies. Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "pendule.h"


	// Force de gravitation
double gravitationPendul(penduleT * pendule, int choix);
	// dt * vitesse du pendule
double vitessePendul(penduleT * pendule);
	// Somme des forces
double forcesPendul(penduleT * pendule, int choix, float courantJosephson);

	// Variation des parametres reduits
void changeAlpha(penduleT * pendule, float facteur);
void changeKapa(penduleT * pendule, float facteur);
void changeGamma(penduleT * pendule, float facteur);


void penduleJauge(penduleT * pendule, float jauge)
	{
	(*pendule).ancien = (*pendule).ancien + jauge;
	(*pendule).actuel = (*pendule).actuel + jauge;
	(*pendule).nouveau = (*pendule).nouveau + jauge;
	return;
	}

// Initialisation des parametres
void penduleInitialiseParametre(penduleT * pendule, float masse, float longueur, float dissipation)
	{
	(*pendule).masse = masse;
	(*pendule).longueur = longueur;
	(*pendule).dissipation = dissipation;
	return;
	}
void penduleInitialiseExterieur(penduleT * pendule, float couplage, float gravitation, float dt)
	{
	(*pendule).couplage = couplage;
	(*pendule).gravitation = gravitation;
	penduleInitialiseKapa(pendule, couplage, dt);
	penduleInitialiseGamma(pendule, gravitation, dt);
	penduleInitialiseAlpha(pendule, (*pendule).dissipation, dt);
	return;
	}
void penduleReinitialiseMasse(penduleT * pendule, float masse, float dt)
	{
	(*pendule).masse = masse;
	penduleInitialiseKapa(pendule, (*pendule).couplage, dt);
	penduleInitialiseGamma(pendule, (*pendule).gravitation, dt);
	penduleInitialiseAlpha(pendule, (*pendule).dissipation, dt);
	return;
	}
void penduleInitialisePosition(penduleT * pendule, float ancien, float actuel)
	{
	((*pendule).ancien) = ancien;
	((*pendule).actuel) = actuel;
	((*pendule).nouveau) = 2 * actuel - ancien;
	return;
	}
void penduleInitialiseDephasage(penduleT * pendule, float dephasage)
	{
	((*pendule).dephasage)=dephasage;
	return;
	}

// Initialisation des parametres reduits
void penduleInitialiseAlpha(penduleT * pendule, float dissipation, float dt)
	{
	if((*pendule).masse!=0.0)
		{
		(*pendule).alpha = - dt * dissipation / (*pendule).masse / (*pendule).longueur;
		}
	else
		{// si masse nulle, nouvelle définition de alpha
		(*pendule).alpha = - dt * dissipation;
		}
	return;
	}
void penduleInitialiseKapa(penduleT * pendule, float couplage, float dt)
	{
	if((*pendule).masse!=0.0)
		{
		(*pendule).kapa = - dt * dt * couplage / (*pendule).masse;
		}
	else
		{// si masse nulle, nouvelle définition de kapa
		(*pendule).kapa = - dt * dt * couplage;
		}
	return;
	}
void penduleInitialiseGamma(penduleT * pendule, float gravitation, float dt)
	{
	if((*pendule).longueur!=0.0)
		{
		(*pendule).gamma = - dt * dt * gravitation / (*pendule).longueur;
		}
	else
		{// si longueur nulle, nouvelle définition de gamma
		(*pendule).gamma = - dt * dt * gravitation;
		}
	return;
	}



// Variation des parametres
void penduleChangeMasse(penduleT * pendule, float facteur)
	{
	if(facteur != 0.0)
		{
		(*pendule).masse = (*pendule).masse * facteur;
		(*pendule).alpha = (*pendule).alpha / facteur;
		(*pendule).kapa = (*pendule).kapa / facteur;
		}
	return;
	}
void penduleChangeLongueur(penduleT * pendule, float facteur)
	{
	if(facteur != 0.0)
		{
		(*pendule).longueur = (*pendule).longueur * facteur;
		(*pendule).gamma = (*pendule).gamma / facteur;
		}
	return;
	}
void penduleChangeDissipation(penduleT * pendule, float facteur)
	{
	(*pendule).dissipation = (*pendule).dissipation * facteur;
	(*pendule).alpha = (*pendule).alpha * facteur;
	return;
	}
void penduleChangeCouplage(penduleT * pendule, float facteur)
	{
	(*pendule).couplage = (*pendule).couplage * facteur;
	(*pendule).kapa = (*pendule).kapa * facteur;
	return;
	}
void penduleChangeGravitation(penduleT * pendule, float facteur)
	{
	(*pendule).gamma = (*pendule).gamma * facteur;
	return;
	}
void penduleAjouteDephasage(penduleT * pendule, float dephasage)
	{
	(*pendule).dephasage = (*pendule).dephasage + dephasage;
	return;
	}

// Evolution temporelle du pendule

void penduleIncremente(penduleT * pendule)
	{
		// incrementation des positions
	((*pendule).ancien)=((*pendule).actuel);
	((*pendule).actuel)=((*pendule).nouveau);
	return;
	}

void penduleInertie(penduleT * pendule, int choix, float courantJosephson)
	{
		// application du principe d'inertie
	(*pendule).nouveau = forcesPendul(pendule, choix, courantJosephson) + 2*((*pendule).actuel) - (*pendule).ancien;
	return;
	}

double forcesPendul(penduleT * pendule, int choix, float courantJosephson)
	{
		// somme des forces sur le pendule
	return ((*pendule).forceCouplage + gravitationPendul(pendule, choix) + ((*pendule).alpha)*vitessePendul(pendule) + courantJosephson);
	}

void penduleCouplage(penduleT * m1, penduleT * m2, penduleT * m3)
	{
		// calcul des forces de couplage
	double gauche, droite;

	gauche = (*m1).kapa * ( (*m2).actuel - (*m1).actuel + (*m1).dephasage );
	droite = (*m2).kapa * ( (*m2).actuel - (*m3).actuel - (*m2).dephasage );

	(*m2).forceCouplage = gauche + droite;

	return;
	}

double gravitationPendul(penduleT * pendule, int choix)
	{
		// Calcul de la FORCE DE RAPPEL
	double forceRappel;

	switch(choix)
		{
		case 1:// gravitation
			forceRappel = (*pendule).gamma * sin((*pendule).actuel);
		break;
		case 2:// linearisation harmonique
			forceRappel = (*pendule).gamma * (*pendule).actuel;
		break;
		case 3:// corde vibrante
			forceRappel = 0.0;
		break;
		default:// corde vibrante
			forceRappel = 0.0;
		break;
		}

	return forceRappel;
	}

double vitessePendul(penduleT * pendule)
	{
		// Retourne vdt
	return (*pendule).actuel - (*pendule).ancien;
	}


void penduleAffiche(penduleT * pendule)
	{
		// Affichage des positions et des parametres
	printf("   ancien    %f\n",(*pendule).ancien);
	printf("   actuel    %f\n",(*pendule).actuel);
	printf("   nouveau   %f\n",(*pendule).nouveau);

	printf("    masse     %f\n",(*pendule).masse);
	printf("    longueur  %f\n",(*pendule).longueur);
	printf("    alpha    %f\n",(*pendule).alpha);
	printf("    kapa     %f\n",(*pendule).kapa);
	printf("    gamma    %f\n",(*pendule).gamma);

	printf("forceCouplage %f\n",(*pendule).forceCouplage);
	printf("  forceTotale %f\n",(*pendule).forceTotale);

	return;
	}

////////////////////////////////////////////////////////////

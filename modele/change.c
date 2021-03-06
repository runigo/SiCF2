/*
Copyright avril 2019, Stephan Runigo
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

#include "change.h"

void changeLimite(systemeT * systeme);
void changeDioptre(systemeT * systeme);

int changeCouplage(systemeT * systeme, float facteur)
	{// Multiplie le couplage par facteur
	float couplage;
	int limite=0;
	int i;

	couplage = (*systeme).couplage * facteur / (*systeme).nombre;

	if(couplage < COUPLAGE_MAX && couplage > COUPLAGE_MIN)
		{
		(*systeme).couplage=(*systeme).couplage*facteur;
		for(i=0;i<(*systeme).nombre;i++)
			{
			penduleChangeCouplage(&(*systeme).pendule[i], facteur);
			}
		}
	else
		{
		printf("Limite du couplage. ");
		limite=1;
		}

	printf("Couplage = %6.3f\n", (*systeme).couplage);

	return limite;
	}

int changeCouplageMoyenne(systemeT * systeme)
	{// Fixe le couplage à un couplage moyen
	float couplage;
	float moyenne = sqrt(COUPLAGE_MAX * COUPLAGE_MIN );

	couplage = (*systeme).couplage / (*systeme).nombre;

	if(couplage > moyenne)
		{
		do
			{
			if(changeCouplage(systeme, 0.91)==0)
				{
				couplage = (*systeme).couplage / (*systeme).nombre;
				}
			else { printf("\n  ERREUR changeCouplageMoyen\n"); return 1; }
			}
		while(couplage > moyenne);
		}
	else
		{
		do
			{
			if(changeCouplage(systeme, 1.1)==0)
				{
				couplage = (*systeme).couplage / (*systeme).nombre;
				}
			else { printf("\n  ERREUR changeCouplageMoyen\n"); return 1; }
			}
		while(couplage < moyenne);
		}

	return 0;
	}

void changeGravitation(systemeT * systeme, float facteur)
	{
	int i;
	float nouveau = (*systeme).gravitation*facteur;
	if(facteur > 1)
		{
		if(nouveau < GRAVITATION_MAX)
			{
			(*systeme).gravitation=nouveau;
			for(i=0;i<(*systeme).nombre;i++)
				{
				penduleChangeGravitation(&(*systeme).pendule[i], facteur);
				}

			printf("Gravitation = %6.3f\n", (*systeme).gravitation);
			}
		else
			{
			printf("Gravitation maximal atteint : ");
			printf("gravitation = %6.3f\n", (*systeme).gravitation);
			}
		}

	if(facteur < 1 )
		{
		if(nouveau > GRAVITATION_MIN)
			{
			(*systeme).gravitation=nouveau;
			for(i=0;i<(*systeme).nombre;i++)
				{
				penduleChangeGravitation(&(*systeme).pendule[i], facteur);
				}

			printf("Gravitation = %6.3f\n", (*systeme).couplage);
			}
		else
			{
			printf("Gravitation minimal atteint : ");
			printf("gravitation = %6.3f\n", (*systeme).couplage);
			}
		}

	return;
	}
/*
void changeDioptre(systemeT * systeme)
	{
	int i;
	if((*systeme).equation==4)
		{
		for(i=(*systeme).nombre/2;i<(*systeme).nombre;i++)
			{
			penduleReinitialiseMasse(&(*systeme).pendule[i], (*systeme).masseDroite, (*systeme).moteurs.dt);
			}
		}
	else
		{
		for(i=0;i<(*systeme).nombre;i++)
			{
			penduleReinitialiseMasse(&(*systeme).pendule[i], (*systeme).masseGauche, (*systeme).moteurs.dt);
			}
		}
	return;
	}
*/
void changeMasse(systemeT * systeme, float facteur)
	{
	float droite = (*systeme).masseDroite;
	//float gauche = (*systeme).masseGauche;
	float masse = droite*facteur;
	int i;

	if(masse < MASSE_MAX && masse > MASSE_MIN)
		{
		(*systeme).masseDroite=masse;
		if((*systeme).equation==4)
			{
			for(i=(*systeme).nombre/2;i<(*systeme).nombre;i++)
				{
				penduleChangeMasse(&(*systeme).pendule[i], facteur);
				}
			printf("Masse à gauche = %6.3f, masse à droite = %6.3f\n", (*systeme).masseGauche, masse);
			}
		else
			{
			for(i=0;i<(*systeme).nombre;i++)
				{
				penduleChangeMasse(&(*systeme).pendule[i], facteur);
				}
			printf("Masse = %6.3f\n", masse);
			}
		}
	else
		{
		printf("Masse limite atteinte\n");
		}

	return;
	}

int changeDissipation(systemeT * systeme, float facteur)
	{
	int i;
	int limite=0;

	float dissipation = (*systeme).dissipation * facteur;

	if(dissipation < DISSIPATION_MAX && dissipation > DISSIPATION_MIN)
		{
			// Enregistre la dissipation
		(*systeme).dissipation = dissipation;
			// Mise à jour des pendules
		for(i=0;i<(*systeme).nombre;i++)
			{
			penduleChangeDissipation(&(*systeme).pendule[i], facteur);
			}
		}
	else
		{
		printf("dissipation limite atteinte\n");
		limite=1;
		}
	printf("Dissipation = %6.3f\n", (*systeme).dissipation);

	return limite;
	}

int changeDissipationMoyenne(systemeT * systeme)
	{// Fixe la dissipation à une dissipation moyennne
	float dissipation = (*systeme).dissipation;
	float moyenne = sqrt(DISSIPATION_MAX * DISSIPATION_MIN );

	if(dissipation > moyenne)
		{
		do
			{
			if(changeDissipation(systeme, 0.91)==0)
				{
				dissipation = (*systeme).dissipation;
				}
			else { printf("\n  ERREUR changeDissipationMoyenne\n"); return 1; }
			}
		while(dissipation > moyenne);
		}
	else
		{
		do
			{
			if(changeDissipation(systeme, 1.1)==0)
				{
				dissipation = (*systeme).dissipation;
				}
			else { printf("\n  ERREUR changeDissipationMoyenne\n"); return 1; }
			}
		while(dissipation < moyenne);
		}

	return 0;
	}

void changeFormeDissipation(systemeT * systeme, int forme)
	{// initialise une dissipation nulle(0), uniforme(1) ou extremite absorbante(2)
	float dissipation = (*systeme).dissipation;
	int i;

	if ( forme == 0 )
		{
		dissipation = 0.0;
		(*systeme).modeDissipation = 0;
		for(i=0;i<(*systeme).nombre;i++)
			{
				// Reinitialisation de alpha
			penduleInitialiseAlpha(&(*systeme).pendule[i], 0.0, (*systeme).moteurs.dt);
			}
		printf("Dissipation = %6.3f\n", 0.0);
		}

	if (  forme == 1 )
		{
		(*systeme).modeDissipation = 1;
		for(i=0;i<(*systeme).nombre;i++)
			{
				// Reinitialisation de alpha
			penduleInitialiseAlpha(&(*systeme).pendule[i], dissipation, (*systeme).moteurs.dt);
			}
		printf("Dissipation = %6.3f\n", dissipation);
		}

	if ( forme == 2 )
		{
		(*systeme).modeDissipation = 2;
		for(i=0;i<(*systeme).nombre;i++)
			{
				// Reinitialisation de alpha
			penduleInitialiseAlpha(&(*systeme).pendule[i], (*systeme).pendule[i].absorbance*dissipation, (*systeme).moteurs.dt);
			}
		printf("Dissipation premier= %6.3f\n", (*systeme).pendule[0].dissipation);
		printf("Dissipation dernier= %6.3f\n", (*systeme).pendule[(*systeme).nombre-1].dissipation);
		}

	return;
	}

void changeEquation(systemeT * systeme, int equation)
	{// Choix de l'equation
	(void)equation;
/*
	switch(equation)
		{
		case 1: // Pendules
			(*systeme).equation = 1;
			printf("equation = Pendules\n");break;
		case 2: // Harmoniques
			(*systeme).equation = 2;
			printf("equation = Harmoniques\n");break;
		case 3: // Corde
			(*systeme).equation = 3;
			changeDioptre(systeme);
			printf("equation = Corde\n");break;
		case 4: // Corde asymétrique
			(*systeme).equation = 4;
			changeDioptre(systeme);
			printf("equation = Corde asymétrique\n");break;
		default:
			;
		}
*/
	printf("equation = %d \n\n", (*systeme).equation);
	return;
	}

void changeConditionsLimites(systemeT * systeme, int libreFixe)
	{
	(*systeme).libreFixe=libreFixe;
	printf("libreFixe = %d, ", (*systeme).libreFixe);

	switch(libreFixe)
		{
		case 0:
			printf(": conditions aux limites périodiques\n");
			break;
		case 1:
			printf(": extrémités libres\n");
			break;
		case 2:
			printf(": extrémités fixes\n");
			break;
		case 3:
			printf(": premier libre, dernier fixe\n");
			break;
		case 4:
			printf(": premier fixe, dernier libre\n");
			break;
		default:
			;
		}

	changeLimite(systeme);

	return;
	}

void changeLimite(systemeT * systeme)
	{// Initialise les conditions aux limites
	float couplage=0.0;
	if ((*systeme).libreFixe==0 || (*systeme).libreFixe==2)
		{
		couplage=(*systeme).couplage;
		}

	penduleInitialiseKapa(&(*systeme).pendule[(*systeme).nombre-1], couplage, (*systeme).moteurs.dt);

	printf("Couplage dernier = %6.3f\n", couplage);

	return;
	}

void changeFormeDioptre(systemeT * systeme, float facteur)
	{
	int i;
	for(i=(*systeme).nombre/2;i<(*systeme).nombre;i++)
		{
		penduleChangeMasse(&((*systeme).pendule[i]), facteur);
		}
	return;
	}

void changeDephasage(systemeT * systeme, float dephasage)
	{
	penduleAjouteDephasage(&(*systeme).pendule[(*systeme).nombre-1], dephasage);

	printf("Déphasage dernier = %6.3f\n", (*systeme).pendule[(*systeme).nombre-1].dephasage);

	}

/*--------------------------------------------------------------*/

//////////////////////////////////////////////////////////////////////////

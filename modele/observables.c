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

#include "observables.h"

int observablesMiseAJourAmplitudes(observablesT * observables);
float observablesMiseAJourAmplitude(observableT * observable);

int observablesMiseAJourNombre(observablesT * observables, systemeT * systeme);
int observablesMiseAJourLibreParcoursMoyen(observablesT * observables, systemeT * systeme);
int observablesMiseAJourTemperature(observablesT * observables, systemeT * systeme);

int observablesMiseAJourPression(observablesT * observables, systemeT * systeme);
int observablesMiseAJourDensite(observablesT * observables, systemeT * systeme);

float observablesAbsolue(float valeur);

float observablesAbsolue(float valeur)
	{
	if(valeur<0) return -valeur;
	return valeur;
	}

int observablesInitialise(observablesT * observables)
	{
	int i, j;
	for(j=0;j<CAPTEURS;j++)
		{
		(*observables).observable[j].dureeCapteur=DUREE_CAPTEURS;
		(*observables).observable[j].maximumCapteur = 0;
		for(i=0;i<DUREE_CAPTEURS;i++)
			{
			(*observables).observable[j].gauche[i]=0;
			(*observables).observable[j].droite[i]=0;
			}
		}

	//(*observables).observable[5].dureeCapteur=DY_ENERGIE;

	(*observables).index=0;

	return 0;
	}

float observablesMiseAJourAmplitude(observableT * observable)
	{
				// Calcul le maximum d'un capteur
	int i;
	float max;

	max = 0.0;
	for(i=0;i<DUREE_CAPTEURS;i++)
		{
		if((*observable).gauche[i] > max)
			{
			max = (*observable).gauche[i];
			}
		if((*observable).droite[i] > max)
			{
			max = (*observable).droite[i];
			}
		}
	(*observable).maximumCapteur = max;

	return max;
	}

int observablesMiseAJourAmplitudes(observablesT * observables)
	{
				// Mise à jour des maximum des capteurs
	int j;

	for(j=0;j<CAPTEURS;j++)
		{
		observablesMiseAJourAmplitude(&(*observables).observable[j]);
		}
	return 0;
	}

int observablesMiseAJour(observablesT * observables, systemeT * systeme)
	{
						// Évolution de l'index

	(*observables).index ++;
	if((*observables).index==DUREE_CAPTEURS)
		{
		(*observables).index=0;
		}

						// Mise à jour des observables

	observablesMiseAJourCinetique(observables,systeme);

	observablesMiseAJourGravitation(observables, systeme);

	observablesMiseAJourCouplage(observables, systeme);

	observablesMiseAJourPression(observables, systeme);

	//observablesMiseAJourDensite(observables, systeme);

	//observablesMiseAJourAmplitudes(observables);

	return 0;
	}

int observablesMiseAJourCinetique(observablesT * observables, systemeT * systeme)
	{
						// Calcul de l'énergie cinétique
	int i;
	double ecGauche=0.0;
	double ecDroite=0.0;

	for(i=0;i<(*systeme).nombre;i++)
		{
		if((*systeme).mobile[i].droite==0)
			{
			ecGauche=ecGauche+mobileEnergieCinetique(&(*systeme).mobile[i]);
			}
		else
			{
			ecDroite=ecDroite+mobileEnergieCinetique(&(*systeme).mobile[i]);
			}
		}

		// Mise à jour de l'énergie
	(*observables).observable[3].gauche[(*observables).index]=ecGauche;
	(*observables).observable[3].droite[(*observables).index]=ecDroite;

		// Mise à jour de la température
	if((*observables).observable[1].gauche[(*observables).index]!=0.0)
		{
		(*observables).observable[0].gauche[(*observables).index]=ecGauche/(*observables).observable[1].gauche[(*observables).index];
		}
	else
		{
		(*observables).observable[0].gauche[(*observables).index]=ecGauche;
		}

	if((*observables).observable[1].droite[(*observables).index]!=0.0)
		{
		(*observables).observable[0].droite[(*observables).index]=ecDroite/(*observables).observable[1].droite[(*observables).index];
		}
	else
		{
		(*observables).observable[0].droite[(*observables).index]=ecDroite;
		}

	observablesMiseAJourAmplitude(&(*observables).observable[3]);
	observablesMiseAJourAmplitude(&(*observables).observable[0]);

	return 0;
	}

int observablesMiseAJourGravitation(observablesT * observables, systemeT * systeme)
	{
						// Calcul de l'énergie de gravitation
	int i;
	double lpmGauche=0.0;
	double lpmDroite=0.0;

	for(i=0;i<(*systeme).nombre;i++)
		{
		if((*systeme).mobile[i].droite==0)
			{
			lpmGauche = lpmGauche + (*systeme).mobile[i].lpm;
			}
		else
			{
			lpmDroite = lpmDroite + (*systeme).mobile[i].lpm;
			}
		}

	if((*observables).observable[1].gauche[(*observables).index]!=0.0)
		{
		(*observables).observable[2].gauche[(*observables).index]=lpmGauche/(*observables).observable[1].gauche[(*observables).index];
		}
	else
		{
		(*observables).observable[2].gauche[(*observables).index]=lpmGauche;
		}

	if((*observables).observable[1].droite[(*observables).index]!=0.0)
		{
		(*observables).observable[2].droite[(*observables).index]=lpmDroite/(*observables).observable[1].droite[(*observables).index];
		}
	else
		{
		(*observables).observable[2].droite[(*observables).index]=lpmDroite;
		}

	observablesMiseAJourAmplitude(&(*observables).observable[2]);

	return 0;
	}

int observablesMiseAJourCouplage(observablesT * observables, systemeT * systeme)
	{
						// Calcul de l'énergie de couplage
	int i;
	float pressionGauche=0.0;
	float pressionDroite=0.0;

	for(i=0;i<(*systeme).nombre;i++)
		{
		//if(observablesAbsolue((*systeme).mobile[i].actuel.x) < DY_PRESSION)
			{
			if((*systeme).mobile[i].droite==0)
				{
				pressionGauche = pressionGauche + observablesAbsolue(((*systeme).mobile[i].actuel.y)-((*systeme).mobile[i].ancien.y));
				//pressionGauche = pressionGauche + observablesAbsolue(((*systeme).mobile[i].nouveau.y)-((*systeme).mobile[i].actuel.y));
				}
			else
				{
				pressionDroite = pressionDroite + observablesAbsolue(((*systeme).mobile[i].actuel.y)-((*systeme).mobile[i].ancien.y));
				//pressionDroite = pressionDroite + observablesAbsolue(((*systeme).mobile[i].actuel.y)-((*systeme).mobile[i].ancien.y));
				}
			}
		}

	(*observables).observable[4].gauche[(*observables).index]=pressionGauche;

	(*observables).observable[4].droite[(*observables).index]=pressionDroite;

	observablesMiseAJourAmplitude(&(*observables).observable[4]);

	return 0;
	}

int observablesAffiche(observablesT * observables)
	{
	printf("\nSTATISTIQUES\n");

	printf("	temperature à gauche %f \n", (*observables).observable[0].gauche[(*observables).index]);
	printf("	temperature à droite %f \n\n", (*observables).observable[0].droite[(*observables).index]);
	printf("	nombre à gauche %f \n", (*observables).observable[1].gauche[(*observables).index]);
	printf("	nombre à droite %f \n\n", (*observables).observable[1].droite[(*observables).index]);
	printf("	libre parcours moyen à gauche %f \n", (*observables).observable[2].gauche[(*observables).index]);
	printf("	libre parcours moyen à droite %f \n\n", (*observables).observable[2].droite[(*observables).index]);
	return 0;
	}


// double observablesEnergieCinetiquePendule(penduleT * pendule, float dt);
// double observablesEnergieGravitationPendule(penduleT * pendule, float dt);
// double observablesEnergieHarmoniquePendule(penduleT * pendule, float dt);
// double observablesEnergieCouplagePendule(penduleT * pendule, penduleT * suivant, float dt);
// double observablesEnergieCinetiqueSysteme(systemeT * systeme);
// double observablesEnergieGravitationSysteme(systemeT * systeme);
// double observablesEnergieCouplageSysteme(systemeT * systeme);

double observablesEnergieCinetiquePendule(penduleT * pendule, float dt)
	{
	double vitesse = (*pendule).actuel - (*pendule).ancien;

	return (0.5 * (*pendule).masse * (*pendule).longueur * (*pendule).longueur * vitesse * vitesse / dt / dt);
	}

double observablesEnergieGravitationPendule(penduleT * pendule, float dt)
	{	//(*pendule).gamma est négatif
	double h = (*pendule).longueur*(1.0-cos((*pendule).actuel));

	return ( - (*pendule).masse * (*pendule).gamma * h / dt / dt);
	}

double observablesEnergieHarmoniquePendule(penduleT * pendule, float dt)
	{	//	k(ressort) = masse.raideur.longueur
	double h = (*pendule).longueur * (*pendule).actuel * (*pendule).actuel;
	return ( - 0.5 * (*pendule).masse * (*pendule).gamma * h / dt / dt);
	}

double observablesEnergieCouplagePendule(penduleT * pendule, penduleT * suivant, float dt)
	{	//(*pendule).kapa est négatif
	double x, y;
	x=(*pendule).actuel;
	y=(*suivant).actuel - (*pendule).dephasage;
	return ( - 0.5 * (*pendule).longueur * (*pendule).longueur * (*pendule).masse * (*pendule).kapa *  (x-y) * (x-y) / dt / dt);
	}

double observablesEnergieCinetiqueSysteme(systemeT * systeme)
	{
	int i;
	double ectotal=0.0;
	float dt = (*systeme).moteur.dt;
	for(i=0;i<(*systeme).nombre;i++)
		{
		ectotal=ectotal+observablesEnergieCinetiquePendule(&((*systeme).pendule[i]), dt);
		}
	return ectotal;
	}

double observablesEnergieCouplageSysteme(systemeT * systeme)
	{
	int i;
	double ectotal=0.0;
	float dt = (*systeme).moteur.dt;
	for(i=1;i<(*systeme).nombre;i++)
		{
		ectotal=ectotal+observablesEnergieCouplagePendule(&((*systeme).pendule[i-1]), &((*systeme).pendule[i]), dt);
		}
	if((*systeme).libreFixe==0)
		ectotal=ectotal+observablesEnergieCouplagePendule(&((*systeme).pendule[N-1]), &((*systeme).pendule[0]), dt);
	return ectotal;
	}

double observablesEnergieGravitationSysteme(systemeT * systeme)
	{
	int i;
	double ectotal=0.0;
	float dt = (*systeme).moteur.dt;
	for(i=0;i<(*systeme).nombre;i++)
		{
		ectotal=ectotal+observablesEnergieGravitationPendule(&((*systeme).pendule[i]), dt);
		}
	return ectotal;
	}

double observablesEnergieHarmoniqueSysteme(systemeT * systeme)
	{
	int i;
	double ectotal=0.0;
	float dt = (*systeme).moteur.dt;
	for(i=0;i<(*systeme).nombre;i++)
		{
		ectotal=ectotal+observablesEnergieHarmoniquePendule(&((*systeme).pendule[i]), dt);
		}
	return ectotal;
	}

void observablesAfficheEnergie(systemeT * systeme)
	{
	double eCouplage, eGravitation, eCinetique;

		//printf("\nCalcul de l'énergie cinétique\n");
	eCinetique=observablesEnergieCinetiqueSysteme(systeme);
	printf("\n  Energie cinétique    %12.9f\n", eCinetique);

		//printf("Calcul de l'énergie de couplage\n");
	eCouplage=observablesEnergieCouplageSysteme(systeme);
	printf("  Energie de couplage  %12.9f\n", eCouplage);

		//	Pendule=1, Harmonique=2, Corde=3, Dioptre=4
	if((*systeme).equation == 1)
		{
		//printf("Calcul de l'énergie de gravitation\n");
		eGravitation=observablesEnergieGravitationSysteme(systeme);
		printf("  Energie de gravitation  %12.9f\n", eGravitation);
		}

	if((*systeme).equation == 2)
		{
		//printf("Calcul de l'énergie de raideur harmonique\n");
		eGravitation=observablesEnergieHarmoniqueSysteme(systeme);
		printf("  Energie  de raideur harmonique  %12.9f\n", eGravitation);
		}

	if((*systeme).equation == 3 || (*systeme).equation == 4)
		{
		//printf("Calcul de l'énergie de raideur harmonique\n");
		eGravitation=0.0;
		}

	printf("\nEnergie totale      %12.9f\n\n", eCouplage + eGravitation + eCinetique);
	return;
	}

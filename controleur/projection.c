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

#include "projection.h"

float projectionValeurAbsolue(float valeur);

int projectionInitialise(projectionT * projection)
	{
	(*projection).logCouplage = 1.0 / log( (COUPLAGE_MAX/COUPLAGE_MIN) );
	(*projection).logDissipation = 1.0 / log( DISSIPATION_MAX/DISSIPATION_MIN );
	(*projection).logJosephson = 1.0 / log( JOSEPHSON_MAX/JOSEPHSON_MIN );
	(*projection).logAmplitude = 1.0 / log( AMPLITUDE_MAX/AMPLITUDE_MIN );
	(*projection).logFrequence = 1.0 / log( FREQUENCE_MAX/FREQUENCE_MIN );
	return 0;
	}

int projectionInitialiseLongueurs(projectionT * projection, int largeur, int hauteur)
	{
	(*projection).largeur = largeur;
	(*projection).hauteur = hauteur;
	return 0;
	}

float projectionValeurAbsolue(float valeur)
	{
	if(valeur<0) return -valeur;
	return valeur;
	}
/*
void projectionSystemeFonction(systemeT * systeme, fonction * spectreG, fonction * spectreD)
	{
	//	Projette les parties gauche et droite du système sur deux fonctions
	int i;
	for(i=0;i<Ne;i++)
		{

		(*spectreG).reel[i]=(*systeme).pendule[i].nouveau;
		(*spectreG).imag[i]=0.0;

		(*spectreD).reel[i]=(*systeme).pendule[i+Ne].nouveau;
		(*spectreD).imag[i]=0.0;

		}
	return;
	}
*/
int projectionSystemeGraphe(systemeT * systeme, projectionT * projection, grapheT * graphe)
	{
	(void)systeme;
	(void)projection;
	(void)graphe;

	int i;

	for(i=0;i<(*systeme).nombre;i++)
		{
		(*graphe).point[i].y = (int)(*systeme).pendule[i].nouveau;
		}
	return 0;
	}

int projectionSystemeCommandes(systemeT * systeme, projectionT * projection, commandesT * commandes, int duree, int mode)
	{		// Projette le système sur les commandes
	float theta;
	float ratioRotatif = 0.9;

				//	Projection sur les boutons rotatifs
	 //	Couplage
	theta = DEUXPI * (*projection).logCouplage * log( (*systeme).couplage / (COUPLAGE_MIN * (*systeme).nombre) );
	(*commandes).rotatifPositionX[0]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[0]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	theta = DEUXPI * (*projection).logDissipation * log( (*systeme).dissipation/DISSIPATION_MIN );
	(*commandes).rotatifPositionX[1]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[1]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Amplitude du moteur josephson
	theta = DEUXPI * (*projection).logJosephson * log( projectionValeurAbsolue((*systeme).moteurs.courant/JOSEPHSON_MIN) );
	(*commandes).rotatifPositionX[2]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[2]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Amplitude du moteur périodique
	theta = DEUXPI * (*projection).logAmplitude * log( (*systeme).moteurs.amplitude/AMPLITUDE_MIN );
	(*commandes).rotatifPositionX[3]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[3]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	//	Fréquence du moteurs
	theta = DEUXPI * (*projection).logFrequence * log( (*systeme).moteurs.frequence/FREQUENCE_MIN );
	(*commandes).rotatifPositionX[4]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[4]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

		//int rotatifPositionX[ROTATIF_COMMANDES]; // Position du bouton rotatif
		//int rotatifPositionY[ROTATIF_COMMANDES];


	int i;
	for(i=0;i<BOUTON_COMMANDES;i++) (*commandes).boutonEtat[i]=0;

		//int libreFixe;		//	0 : périodiques 1 : libres, 2 : fixes, 
							//		3 libre-fixe, 4 fixe-libre
	switch((*systeme).libreFixe)	//	
		{
		case 0:
			(*commandes).boutonEtat[0]=1;break; // 32	Périodique
		case 1:
			(*commandes).boutonEtat[1]=1;break; // 62	Libre
		case 2:
			(*commandes).boutonEtat[2]=1;break; // 88 	Fixe
		case 3:
			(*commandes).boutonEtat[3]=1;break; // 115	Mixte
		case 4:
			(*commandes).boutonEtat[3]=1;break; // 115	Mixte
		default:
			;
		}

	//	int modeDissipation;	//	0 : nulle 1 : uniforme, 2 : extrémité absorbante.
	switch((*systeme).modeDissipation)	//	
		{
		case 0:
			(*commandes).boutonEtat[5]=1;break; // 198	Nulle
		case 1:
			(*commandes).boutonEtat[4]=1;break; // 167	Uniforme
		case 2:
			(*commandes).boutonEtat[6]=1;break; // 230	Extrémité
		default:
			;
		}
/*
	(*commandes).boutonEtat[4]=1;
	(*commandes).boutonEtat[5]=1;
	(*commandes).boutonEtat[6]=1;
*/
	if((*systeme).moteurs.josephson > 0.0)
		{
		(*commandes).boutonEtat[7]=1; // 284	Marche
		(*commandes).boutonEtat[9]=1; // 339	Droite
		}
	else
		{
		if((*systeme).moteurs.josephson < 0.0)
			{
			(*commandes).boutonEtat[7]=1; // 284	Marche
			(*commandes).boutonEtat[10]=1; // 367	Gauche
			}
		else
			{
			(*commandes).boutonEtat[8]=1; // 311	Arrêt
			}
		}

	switch((*systeme).moteurs.generateur)	//	0:eteint, 1:sinus, 2:carre, 3:impulsion
		{
		case 0:
			(*commandes).boutonEtat[11]=1;break; // 421	Arrêt
		case 1:
			(*commandes).boutonEtat[12]=1;break; // 449	Sinus
		case 2:
			(*commandes).boutonEtat[13]=1;break; // 481	Carré
		case 3:
			(*commandes).boutonEtat[14]=1;break; // 509	Impulsion
		default:
			;
		}
	//(*commandes).boutonEtat[15]=0; // 536	Fluxon
	//(*commandes).boutonEtat[16]=0; // 563	Anti F.

	for(i=0;i<TRIANGLE_COMMANDES;i++) (*commandes).triangleEtat[i]=0;
/*
	switch((*projection).rotation)	//	
		{
		case 3:
			(*commandes).triangleEtat[0]=1;break; // 
		case 1:
			(*commandes).triangleEtat[1]=1;break; // 
		case 0:
			(*commandes).triangleEtat[2]=0;break; // 
		case -1:
			(*commandes).triangleEtat[3]=1;break; // 
		case -3:
			(*commandes).triangleEtat[4]=1;break; // 
		default:
			;
		}
*/
		//	Vitesse de la simulation
	if(duree<DUREE)
		{
			if(duree==1) (*commandes).triangleEtat[5]=-1; else (*commandes).triangleEtat[6]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).a * duree + (*commandes).b);
		}
	else
		{
		if(duree>DUREE)
			{
			if(duree==DUREE_MAX) (*commandes).triangleEtat[10]=-1; else (*commandes).triangleEtat[9]=-1;
			(*commandes).lineairePositionX=(int)((*commandes).A * duree + (*commandes).B);
			}
		else
			{
			(*commandes).triangleEtat[8]=1;
			}
		}

	if(mode<0)
		{
		(*commandes).triangleEtat[7]=2;
		}
	return 0;
	}

int projectionObservablesCapteurs(observablesT * observables, projectionT * projection, capteursT * capteurs)
	{
	(void)projection;
	float a;
	int i, j, k, y0;

	for(j=0;j<CAPTEURS;j++)
		{
		if(j!=5)
			{
			if((*observables).observable[j].maximumCapteur!=0.0)
				{
				a = -(float)((*capteurs).capteur[j].hauteur) / (*observables).observable[j].maximumCapteur;
				}
			else
				{
				a = 0.0;
				}
			y0 = (*capteurs).capteur[j].yZero;
			for(i=0;i<DUREE_CAPTEURS;i++)
				{
				k=(i+(*observables).index+1)%DUREE_CAPTEURS;
				(*capteurs).capteur[j].gauche[i].y = (int)(a*(*observables).observable[j].gauche[k]) + y0;
				(*capteurs).capteur[j].droite[i].y = (int)(a*(*observables).observable[j].droite[k]) + y0;
				}
			}
		else
			{
			if((*observables).observable[j].maximumCapteur!=0.0)
				{
				a = -(float)((*capteurs).capteur[j].hauteur) / (*observables).observable[j].maximumCapteur;
				}
			else
				{
				a = 0.0;
				}
			y0 = (*capteurs).capteur[j].yZero;
			for(i=0;i<DY_ENERGIE;i++)
				{
				(*capteurs).capteur[j].gauche[i].y = (int)(a*(*observables).observable[j].gauche[i]) + y0;
				(*capteurs).capteur[j].droite[i].y = (int)(a*(*observables).observable[j].droite[i]) + y0;
				}
			}
		}

	return 0;
	}

int projectionAffiche(projectionT * projection)
	{
	(void)projection;
	/*
	fprintf(stderr, "  (*projection).logTrou   = %f\n",(*projection).logTrou);
	fprintf(stderr, "   (*projection).logParticule  = %f\n",(*projection).logParticule);
	fprintf(stderr, "  (*projection).logTemperature   = %f\n",(*projection).logTemperature);
	fprintf(stderr, "  (*projection).logGauche   = %f\n",(*projection).logGauche);
	fprintf(stderr, "  (*projection).logDroite   = %f\n",(*projection).logDroite);
	*/
	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////

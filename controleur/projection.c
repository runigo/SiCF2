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

	//-----------------    INITIALISATION      -----------------------//
int projectionInitialise(projectionT * projection)
	{
	(*projection).logCouplage = 1.0 / log( (COUPLAGE_MAX/COUPLAGE_MIN) );
	(*projection).logMasse = 1.0 / log( MASSE_MAX/MASSE_MIN );
	(*projection).logDissipation = 1.0 / log( DISSIPATION_MAX/DISSIPATION_MIN );
	(*projection).logJosephson = 1.0 / log( JOSEPHSON_MAX/JOSEPHSON_MIN );
	(*projection).logAmplitude = 1.0 / log( AMPLITUDE_MAX/AMPLITUDE_MIN );
	(*projection).logFrequence = 1.0 / log( FREQUENCE_MAX/FREQUENCE_MIN );
	(*projection).logSimulation = 1.0 / log( DUREE_MAX );
	(*projection).logNombre = 1.0 / log( NOMBRE_MAX/NOMBRE_MIN );
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

int projectionSystemeFourier(systemeT * systeme, fourierT * fourier)
	{
		//	Projection du système sur les fonctions de fourier
	int i;
	int j = (*systeme).nombre;

	for(i=0;i<j;i++)
		{
		(*fourier).spectre.reel[i]=(*systeme).pendule[i].nouveau;
		(*fourier).spectre.imag[i]=0.0;
		}

	j = (*systeme).nombre/2;

	for(i=0;i<j;i++)
		{
		(*fourier).gauche.reel[i]=(*systeme).pendule[i].nouveau;
		(*fourier).gauche.imag[i]=0.0;
		(*fourier).droite.reel[i]=(*systeme).pendule[i+j].nouveau;
		(*fourier).droite.imag[i]=0.0;
		}

	return 0;
	}

int projectionSystemeGraphe(systemeT * systeme, projectionT * projection, graphesT * graphes)
	{
		// Projection du système sur le graphe
	(void)projection;
	int maximum = (*graphes).corde.yZero + (*graphes).corde.hauteur/2;

	(*graphes).corde.nombre = (*systeme).nombre;

	int i;

	for(i=0;i<(*systeme).nombre;i++)
		{
		(*graphes).corde.point[i].y = (*graphes).corde.yZero + (int)((*graphes).corde.hauteur*(*systeme).pendule[i].nouveau);
		if((*graphes).corde.point[i].y > maximum)
			{
			(*graphes).corde.point[i].y = maximum;
			}
		}
	return 0;
	}

int projectionFourierGraphe(fourierT * fourier, projectionT * projection, graphesT * graphes)
	{
		// Projection des spectres sur les graphes
	(void)projection;

	(*graphes).spectre.nombre = (*fourier).spectre.nombre;
	(*graphes).gauche.nombre = (*fourier).gauche.nombre;
	(*graphes).droite.nombre = (*fourier).droite.nombre;

	int i;
	int j=(*fourier).spectre.nombre/2;
	int k=(*fourier).spectre.nombre;

	for(i=0;i<j;i++)
		{
		(*graphes).spectre.point[2*i].y = (*graphes).spectre.yZero - (int)( (*graphes).spectre.hauteur * (*fourier).spectre.module[i]);
		(*graphes).spectre.point[2*i+1].y = (*graphes).spectre.yZero - (int)( (*graphes).spectre.hauteur * (*fourier).spectre.module[k-i]);
		}

	j=(*fourier).gauche.nombre/2;
	k=(*fourier).gauche.nombre;
	for(i=0;i<(*fourier).gauche.nombre;i++)
		{
		(*graphes).gauche.point[2*i].y = (*graphes).gauche.yZero - (int)( (*graphes).gauche.hauteur * (*fourier).gauche.module[i]);
		(*graphes).gauche.point[2*i+1].y = (*graphes).gauche.yZero - (int)( (*graphes).gauche.hauteur * (*fourier).gauche.module[k-i]);
		}

	j=(*fourier).droite.nombre/2;
	k=(*fourier).droite.nombre;
	for(i=0;i<(*fourier).droite.nombre;i++)
		{
		(*graphes).droite.point[2*i].y = (*graphes).droite.yZero - (int)( (*graphes).droite.hauteur * (*fourier).droite.module[i]);
		(*graphes).droite.point[2*i+1].y = (*graphes).droite.yZero - (int)( (*graphes).droite.hauteur * (*fourier).droite.module[k-i]);
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

		//	Masse
	theta = DEUXPI * (*projection).logMasse * log( (*systeme).masseDroite/MASSE_MIN );
	(*commandes).rotatifPositionX[1]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[1]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

		//	Dissipation
	theta = DEUXPI * (*projection).logDissipation * log( (*systeme).dissipation/DISSIPATION_MIN );
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

		//	Simulation
	theta = 0.9 * DEUXPI * duree/DUREE_MAX;
	(*commandes).rotatifPositionX[5]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[5]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

		//	Nombre
	theta = 0.9 * ((DEUXPI * (*systeme).nombre)/NOMBRE_MAX);
	(*commandes).rotatifPositionX[6]=(int)(-ratioRotatif*(*commandes).rotatifX*sin(theta));
	(*commandes).rotatifPositionY[6]=(int)(ratioRotatif*(*commandes).rotatifY*cos(theta));

	int i;
	for(i=0;i<BOUTON_COMMANDES;i++) (*commandes).boutonEtat[i]=0;

		//int libreFixe;		//	0 : périodiques 1 : libres, 2 : fixes, 
							//		3 libre-fixe, 4 fixe-libre
	switch((*systeme).libreFixe)	//	
		{
		case 0:
			(*commandes).boutonEtat[0]=1;break; //		Périodique
		case 1:
			(*commandes).boutonEtat[1]=1;break; //		Libre
		case 2:
			(*commandes).boutonEtat[2]=1;break; //	 	Fixe
		case 3:
			(*commandes).boutonEtat[3]=1;break; //		Mixte
		case 4:
			(*commandes).boutonEtat[3]=1;break; //		Symétrique
		default:
			;
		}

	//	int modeDissipation;	//	0 : nulle 1 : uniforme, 2 : extrémité absorbante.
	switch((*systeme).modeDissipation)	//	
		{
		case 0:
			(*commandes).boutonEtat[6]=1;break; //		Nulle
		case 1:
			(*commandes).boutonEtat[5]=1;break; //		Uniforme
		case 2:
			(*commandes).boutonEtat[7]=1;break; //		Extrémité
		default:
			;
		}

	switch((*systeme).moteurs.generateur)	//	0:eteint, 1:sinus, 2:carre, 3:impulsion
		{
		case 0:
			(*commandes).boutonEtat[8]=1;break; //		Arrêt
		case 1:
			(*commandes).boutonEtat[9]=1;break; //		Sinus
		case 2:
			(*commandes).boutonEtat[10]=1;break; //		Carré
		case 3:
			(*commandes).boutonEtat[11]=1;break; //		Impulsion
		default:
			;
		}

	if(mode<0)
		{
		(*commandes).boutonEtat[12]=1;
		}

	if(duree==1)
		{
		(*commandes).boutonEtat[13]=1;
		}

	if(duree==DUREE_MAX)
		{
		(*commandes).boutonEtat[14]=1;
		}

	return 0;
	}

int projectionObservablesCapteurs(observablesT * observables, projectionT * projection, capteursT * capteurs) {

		//	Projette les observables sur les capteurs

	(void)projection;
	float a;
	int i, k, y0;
						// 0 : Energie, 1 : Cinetique, 2 : Couplage, 3 : Rappel
						//		0, 1, 2 : Somme, 3, 4, 5 : droite/gauche
		//	SOMME
	if((*observables).observable[0].maximumSomme!=0.0)
		{
		a = -(float)((*capteurs).capteur[0].hauteur) / (*observables).observable[0].maximumSomme;
		}
	else
		{
	//fprintf(stderr, "(*observables).observable[0].maximumSomme==0.0\n");
		a = 0.0;
		}
	y0 = (*capteurs).capteur[0].yZero;
	for(i=0;i<DUREE_CAPTEURS;i++)
		{
		k=(i+(*observables).index+1)%DUREE_CAPTEURS;
		(*capteurs).capteur[0].somme[i].y = (int)(a*(*observables).observable[0].somme[k]) + y0;
		(*capteurs).capteur[1].somme[i].y = (int)(a*(*observables).observable[1].somme[k]) + y0;
		(*capteurs).capteur[2].somme[i].y = (int)(a*(*observables).observable[2].somme[k]) + y0;
		}


		//	GAUCHE DROITE
	if((*observables).observable[0].maximumCapteur!=0.0)
		{
		a = -(float)((*capteurs).capteur[3].hauteur) / (*observables).observable[0].maximumCapteur;
		}
	else
		{
	//fprintf(stderr, "(*observables).observable[0].maximumSomme==0.0\n");
		a = 0.0;
		}
	y0 = (*capteurs).capteur[3].yZero;
	for(i=0;i<DUREE_CAPTEURS;i++)
		{
		k=(i+(*observables).index+1)%DUREE_CAPTEURS;
		(*capteurs).capteur[3].gauche[i].y = (int)(a*(*observables).observable[0].gauche[k]) + y0;
		(*capteurs).capteur[3].droite[i].y = (int)(a*(*observables).observable[0].droite[k]) + y0;
		(*capteurs).capteur[4].gauche[i].y = (int)(a*(*observables).observable[1].gauche[k]) + y0;
		(*capteurs).capteur[4].droite[i].y = (int)(a*(*observables).observable[1].droite[k]) + y0;
		(*capteurs).capteur[5].gauche[i].y = (int)(a*(*observables).observable[2].gauche[k]) + y0;
		(*capteurs).capteur[5].droite[i].y = (int)(a*(*observables).observable[2].droite[k]) + y0;
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

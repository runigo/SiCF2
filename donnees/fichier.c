/*
Copyright août 2019, Stephan Runigo
runigo@free.fr
SiCF 2.1  simulateur de corde vibrante et spectre
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

#include "fichier.h"

int fichierEcritureParametre(systemeT * systeme, int numero);
int fichierLectureParametre(systemeT * systeme, int numero);
int fichierEcriturePosition(systemeT * systeme, int numero);
int fichierLecturePosition(systemeT * systeme, int numero);

int fichierFonctionNulle(systemeT * systeme);
int fichierFonctionTriangle(systemeT * systeme, int numero);
int fichierFonctionCarre(systemeT * systeme, int numero);
int fichierFonctionSinus(systemeT * systeme, int numero);



int fichierEcriture(systemeT * systeme, int numero)
	{
	fichierEcritureParametre(systeme, numero);
	fichierEcriturePosition(systeme, numero);
	return 0;
	}

int fichierLecture(systemeT * systeme, int numero)
	{
	fichierLectureParametre(systeme, numero);
	fichierLecturePosition(systeme, numero);
	return 0;
	}

int fichierEcritureParametre(systemeT * systeme, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */
	double parametre;

	switch (numero)
		{
		case 0 :
			fichier = fopen("./donnees/enregistrement/parametre_a.sicf", "w");break;
		case 1 :
			fichier = fopen("./donnees/enregistrement/parametre_z.sicf", "w");break;
		case 2 :
			fichier = fopen("./donnees/enregistrement/parametre_e.sicf", "w");break;
		case 3 :
			fichier = fopen("./donnees/enregistrement/parametre_r.sicf", "w");break;
		case 4 :
			fichier = fopen("./donnees/enregistrement/parametre_t.sicf", "w");break;
		case 5 :
			fichier = fopen("./donnees/enregistrement/parametre_y.sicf", "w");break;
		case 6 :
			fichier = fopen("./donnees/enregistrement/parametre_u.sicf", "w");break;
		case 7 :
			fichier = fopen("./donnees/enregistrement/parametre_i.sicf", "w");break;
		case 8 :
			fichier = fopen("./donnees/enregistrement/parametre_o.sicf", "w");break;
		case 9 :
			fichier = fopen("./donnees/enregistrement/parametre_p.sicf", "w");break;
		case 10 :
			fichier = fopen("./donnees/enregistrement/parametre_q.sicf", "w");break;
		case 11 :
			fichier = fopen("./donnees/enregistrement/parametre_s.sicf", "w");break;
		case 12 :
			fichier = fopen("./donnees/enregistrement/parametre_d.sicf", "w");break;
		case 13 :
			fichier = fopen("./donnees/enregistrement/parametre_f.sicf", "w");break;
		case 14 :
			fichier = fopen("./donnees/enregistrement/parametre_g.sicf", "w");break;
		case 15 :
			fichier = fopen("./donnees/enregistrement/parametre_h.sicf", "w");break;
		case 16 :
			fichier = fopen("./donnees/enregistrement/parametre_j.sicf", "w");break;
		case 17 :
			fichier = fopen("./donnees/enregistrement/parametre_k.sicf", "w");break;
		case 18 :
			fichier = fopen("./donnees/enregistrement/parametre_l.sicf", "w");break;
		case 19 :
			fichier = fopen("./donnees/enregistrement/parametre_m.sicf", "w");break;
		case 20 :
			fichier = fopen("./donnees/enregistrement/parametre_w.sicf", "w");break;
		case 21 :
			fichier = fopen("./donnees/enregistrement/parametre_x.sicf", "w");break;
		case 22 :
			fichier = fopen("./donnees/enregistrement/parametre_c.sicf", "w");break;
		case 23 :
			fichier = fopen("./donnees/enregistrement/parametre_v.sicf", "w");break;
		case 24 :
			fichier = fopen("./donnees/enregistrement/parametre_b.sicf", "w");break;
		case 25 :
			fichier = fopen("./donnees/enregistrement/parametre_n.sicf", "w");break;
		default:
			;
		}

		// Initialisation du moteurs
		parametre = (*systeme).moteurs.dt;
		fprintf(fichier, "%f\n", parametre);
	
		parametre = (*systeme).moteurs.chrono;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).moteurs.courant;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).moteurs.josephson;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).moteurs.generateur;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).moteurs.amplitude;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).moteurs.frequence;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).moteurs.phi;
		fprintf(fichier, "%f\n", parametre);

		// Caractéristique de la chaîne
		parametre = (*systeme).libreFixe;
		fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).nombre;
		fprintf(fichier, "%f\n", parametre);
		parametre = (*systeme).equation;
		fprintf(fichier, "%f\n", parametre);

		// Paramètres physiques
		parametre = (*systeme).gravitation;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).masseDroite;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).masseGauche;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).longueur;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).dissipation;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).modeDissipation;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).couplage;
		fprintf(fichier, "%f\n", parametre);

		parametre = (*systeme).dephasage;
		fprintf(fichier, "%f\n", parametre);


		//fprintf(stderr, " Initialisation du système\n");
	//systemeInitialise(systeme);
	//changeFormeDissipation(systeme, (*systeme).modeDissipation);
	//changeConditionsLimites(systeme, (*systeme).libreFixe);

	fclose(fichier);

	return 0;
	}

int fichierLectureParametre(systemeT * systeme, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */
	float parametre = 0;

	switch (numero)
		{
		case 0 :
			fichier = fopen("./donnees/enregistrement/parametre_a.sicf", "r");break;
		case 1 :
			fichier = fopen("./donnees/enregistrement/parametre_z.sicf", "r");break;
		case 2 :
			fichier = fopen("./donnees/enregistrement/parametre_e.sicf", "r");break;
		case 3 :
			fichier = fopen("./donnees/enregistrement/parametre_r.sicf", "r");break;
		case 4 :
			fichier = fopen("./donnees/enregistrement/parametre_t.sicf", "r");break;
		case 5 :
			fichier = fopen("./donnees/enregistrement/parametre_y.sicf", "r");break;
		case 6 :
			fichier = fopen("./donnees/enregistrement/parametre_u.sicf", "r");break;
		case 7 :
			fichier = fopen("./donnees/enregistrement/parametre_i.sicf", "r");break;
		case 8 :
			fichier = fopen("./donnees/enregistrement/parametre_o.sicf", "r");break;
		case 9 :
			fichier = fopen("./donnees/enregistrement/parametre_p.sicf", "r");break;
		case 10 :
			fichier = fopen("./donnees/enregistrement/parametre_q.sicf", "r");break;
		case 11 :
			fichier = fopen("./donnees/enregistrement/parametre_s.sicf", "r");break;
		case 12 :
			fichier = fopen("./donnees/enregistrement/parametre_d.sicf", "r");break;
		case 13 :
			fichier = fopen("./donnees/enregistrement/parametre_f.sicf", "r");break;
		case 14 :
			fichier = fopen("./donnees/enregistrement/parametre_g.sicf", "r");break;
		case 15 :
			fichier = fopen("./donnees/enregistrement/parametre_h.sicf", "r");break;
		case 16 :
			fichier = fopen("./donnees/enregistrement/parametre_j.sicf", "r");break;
		case 17 :
			fichier = fopen("./donnees/enregistrement/parametre_k.sicf", "r");break;
		case 18 :
			fichier = fopen("./donnees/enregistrement/parametre_l.sicf", "r");break;
		case 19 :
			fichier = fopen("./donnees/enregistrement/parametre_m.sicf", "r");break;
		case 20 :
			fichier = fopen("./donnees/enregistrement/parametre_w.sicf", "r");break;
		case 21 :
			fichier = fopen("./donnees/enregistrement/parametre_x.sicf", "r");break;
		case 22 :
			fichier = fopen("./donnees/enregistrement/parametre_c.sicf", "r");break;
		case 23 :
			fichier = fopen("./donnees/enregistrement/parametre_v.sicf", "r");break;
		case 24 :
			fichier = fopen("./donnees/enregistrement/parametre_b.sicf", "r");break;
		case 25 :
			fichier = fopen("./donnees/enregistrement/parametre_n.sicf", "r");break;
		default:
			;
		}
	//fichier = fopen("fluxon.sicp", "r");  /* read */
	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier de réinitialisation\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		// Initialisation du moteurs
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.dt = parametre;
	
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.chrono = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.courant = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.josephson = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.generateur = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.amplitude = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.frequence = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).moteurs.phi = parametre;

		// Caractéristique de la chaîne
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).libreFixe = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).nombre = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).equation = parametre;


		// Paramètres physiques
		fscanf(fichier, "%f\n", &parametre);
		(*systeme).gravitation = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).masseDroite = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).masseGauche = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).longueur = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).dissipation = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).modeDissipation = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).couplage = parametre;

		fscanf(fichier, "%f\n", &parametre);
		(*systeme).dephasage = parametre;

		fclose(fichier);

			//fprintf(stderr, " Initialisation du système\n");
		systemeInitialise(systeme);
		changeFormeDissipation(systeme, (*systeme).modeDissipation);
		changeConditionsLimites(systeme, (*systeme).libreFixe);

		}

	return 0;
	}

int fichierEcriturePosition(systemeT * systeme, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */
	double ancien, actuel;
	int i;

	switch (numero)
		{
		case 0 :
			fichier = fopen("./donnees/enregistrement/position_a.sicf", "w");break;
		case 1 :
			fichier = fopen("./donnees/enregistrement/position_z.sicf", "w");break;
		case 2 :
			fichier = fopen("./donnees/enregistrement/position_e.sicf", "w");break;
		case 3 :
			fichier = fopen("./donnees/enregistrement/position_r.sicf", "w");break;
		case 4 :
			fichier = fopen("./donnees/enregistrement/position_t.sicf", "w");break;
		case 5 :
			fichier = fopen("./donnees/enregistrement/position_y.sicf", "w");break;
		case 6 :
			fichier = fopen("./donnees/enregistrement/position_u.sicf", "w");break;
		case 7 :
			fichier = fopen("./donnees/enregistrement/position_i.sicf", "w");break;
		case 8 :
			fichier = fopen("./donnees/enregistrement/position_o.sicf", "w");break;
		case 9 :
			fichier = fopen("./donnees/enregistrement/position_p.sicf", "w");break;
		case 10 :
			fichier = fopen("./donnees/enregistrement/position_q.sicf", "w");break;
		case 11 :
			fichier = fopen("./donnees/enregistrement/position_s.sicf", "w");break;
		case 12 :
			fichier = fopen("./donnees/enregistrement/position_d.sicf", "w");break;
		case 13 :
			fichier = fopen("./donnees/enregistrement/position_f.sicf", "w");break;
		case 14 :
			fichier = fopen("./donnees/enregistrement/position_g.sicf", "w");break;
		case 15 :
			fichier = fopen("./donnees/enregistrement/position_h.sicf", "w");break;
		case 16 :
			fichier = fopen("./donnees/enregistrement/position_j.sicf", "w");break;
		case 17 :
			fichier = fopen("./donnees/enregistrement/position_k.sicf", "w");break;
		case 18 :
			fichier = fopen("./donnees/enregistrement/position_l.sicf", "w");break;
		case 19 :
			fichier = fopen("./donnees/enregistrement/position_m.sicf", "w");break;
		case 20 :
			fichier = fopen("./donnees/enregistrement/position_w.sicf", "w");break;
		case 21 :
			fichier = fopen("./donnees/enregistrement/position_x.sicf", "w");break;
		case 22 :
			fichier = fopen("./donnees/enregistrement/position_c.sicf", "w");break;
		case 23 :
			fichier = fopen("./donnees/enregistrement/position_v.sicf", "w");break;
		case 24 :
			fichier = fopen("./donnees/enregistrement/position_b.sicf", "w");break;
		case 25 :
			fichier = fopen("./donnees/enregistrement/position_n.sicf", "w");break;
		default:
			;
		}
	//fichier = fopen("fluxon.sicp", "w");  /* write */

	for(i=0;i<(*systeme).nombre;i++)
		{
		//penduleInitialisePosition(&(*systeme).pendule[i], 0.0, 0.0);
		ancien = (*systeme).pendule[i].ancien;
		actuel =(*systeme).pendule[i].nouveau;
		fprintf(fichier, "%f %f\n", ancien, actuel);
		}
	fclose(fichier);

	return 0;
	}

int fichierLecturePosition(systemeT * systeme, int numero)
	{
	FILE *fichier; /* pointeur sur FILE */
	float ancien, actuel;
	int i;

	switch (numero)
		{
		case 0 :
			fichier = fopen("./donnees/enregistrement/position_a.sicf", "r");break;
		case 1 :
			fichier = fopen("./donnees/enregistrement/position_z.sicf", "r");break;
		case 2 :
			fichier = fopen("./donnees/enregistrement/position_e.sicf", "r");break;
		case 3 :
			fichier = fopen("./donnees/enregistrement/position_r.sicf", "r");break;
		case 4 :
			fichier = fopen("./donnees/enregistrement/position_t.sicf", "r");break;
		case 5 :
			fichier = fopen("./donnees/enregistrement/position_y.sicf", "r");break;
		case 6 :
			fichier = fopen("./donnees/enregistrement/position_u.sicf", "r");break;
		case 7 :
			fichier = fopen("./donnees/enregistrement/position_i.sicf", "r");break;
		case 8 :
			fichier = fopen("./donnees/enregistrement/position_o.sicf", "r");break;
		case 9 :
			fichier = fopen("./donnees/enregistrement/position_p.sicf", "r");break;
		case 10 :
			fichier = fopen("./donnees/enregistrement/position_q.sicf", "r");break;
		case 11 :
			fichier = fopen("./donnees/enregistrement/position_s.sicf", "r");break;
		case 12 :
			fichier = fopen("./donnees/enregistrement/position_d.sicf", "r");break;
		case 13 :
			fichier = fopen("./donnees/enregistrement/position_f.sicf", "r");break;
		case 14 :
			fichier = fopen("./donnees/enregistrement/position_g.sicf", "r");break;
		case 15 :
			fichier = fopen("./donnees/enregistrement/position_h.sicf", "r");break;
		case 16 :
			fichier = fopen("./donnees/enregistrement/position_j.sicf", "r");break;
		case 17 :
			fichier = fopen("./donnees/enregistrement/position_k.sicf", "r");break;
		case 18 :
			fichier = fopen("./donnees/enregistrement/position_l.sicf", "r");break;
		case 19 :
			fichier = fopen("./donnees/enregistrement/position_m.sicf", "r");break;
		case 20 :
			fichier = fopen("./donnees/enregistrement/position_w.sicf", "r");break;
		case 21 :
			fichier = fopen("./donnees/enregistrement/position_x.sicf", "r");break;
		case 22 :
			fichier = fopen("./donnees/enregistrement/position_c.sicf", "r");break;
		case 23 :
			fichier = fopen("./donnees/enregistrement/position_v.sicf", "r");break;
		case 24 :
			fichier = fopen("./donnees/enregistrement/position_b.sicf", "r");break;
		case 25 :
			fichier = fopen("./donnees/enregistrement/position_n.sicf", "r");break;
		default:
			;
		}

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier de réinitialisation\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		for(i=0;i<(*systeme).nombre;i++)
			{
			ancien = 0;
			actuel = 0;
			fscanf(fichier, "%f %f\n", &ancien, &actuel);
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			}
		fclose(fichier);
		}

	return 0;
	}

int fichierFonction(systemeT * systeme, int numero)
	{
	switch (numero)
		{
		case 0: // Touche A
			fichierFonctionNulle(systeme);break;
		case 1: // Touche Z
			fichierFonctionSinus(systeme, 1);break;
		case 2: // Touche E
			fichierFonctionTriangle(systeme, 2);break;
		case 3: // Touche R
			fichierFonctionTriangle(systeme, 3);break;
		case 4: // Touche T
			fichierFonctionTriangle(systeme, 4);break;
		case 5: // Touche Y
			fichierFonctionTriangle(systeme, 5);break;
		case 6: // Touche U
			fichierFonctionTriangle(systeme, 6);break;
		case 7: // Touche I
			fichierFonctionSinus(systeme, 7);break;
		case 8: // Touche O
			fichierFonctionSinus(systeme, 8);break;
		case 9: // Touche P
			fichierFonctionCarre(systeme, 9);break;
		case 10: // Touche Q
			fichierFonctionSinus(systeme, 1);break;
		case 11: // Touche S
			fichierFonctionSinus(systeme, 2);break;
		case 12: // Touche D
			fichierFonctionSinus(systeme, 3);break;
		case 13: // Touche F
			fichierFonctionSinus(systeme, 4);break;
		case 14: // Touche G
			fichierFonctionSinus(systeme, 5);break;
		case 15: // Touche H
			fichierFonctionCarre(systeme, 1);break;
		case 16: // Touche J
			fichierFonctionCarre(systeme, 2);break;
		case 17: // Touche K
			fichierFonctionCarre(systeme, 3);break;
		case 18: // Touche L
			fichierFonctionCarre(systeme, 4);break;
		case 19: // Touche M
			fichierFonctionCarre(systeme, 5);break;
		case 20: // Touche W
			fichierFonctionSinus(systeme, 1);break;
		case 21: // Touche X
			fichierFonctionSinus(systeme, 2);break;
		case 22: // Touche C
			fichierFonctionSinus(systeme, 3);break;
		case 23: // Touche V
			fichierFonctionSinus(systeme, 4);break;
		case 24: // Touche B
			fichierFonctionSinus(systeme, 5);break;
		case 25: // Touche N
			fichierFonctionCarre(systeme, 1);break;
		default:
			;
		}
	return 0;
	}

int fichierFonctionNulle(systemeT * systeme)
	{
	float ancien, actuel;
	int i;
	for(i=0;i<(*systeme).nombre;i++)
		{
		ancien = 0.0;
		actuel = 0.0;
		penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
		}

	return 0;
	}

int fichierFonctionTriangle(systemeT * systeme, int numero)
	{
	float ancien, actuel;
	int i;
	fichierFonctionNulle(systeme);
	switch (numero)
		{
		case 1:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/2;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
				}break;
		case 2:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/4;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/2-1-i], ancien, actuel);
				}break;
		case 3:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/8;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/4-1-i], ancien, actuel);
				}break;
		case 4:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/16;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/8-1-i], ancien, actuel);
				}break;
		case 5:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/32;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/16-1-i], ancien, actuel);
				}break;
		case 6:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/64;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/64-1-i], ancien, actuel);
				}break;
		}

	return 0;
	}

int fichierFonctionCarre(systemeT * systeme, int numero)
	{
	float ancien, actuel;
	int i;
	fichierFonctionNulle(systeme);
	if(numero == 1)
		{
		printf("Réinitialisation du système, numero = 1\n");
		}
	else
		{
		printf("Réinitialisation du système, numero != 1\n");
		for(i=0;i<(*systeme).nombre/2;i++)
			{
			ancien = i*numero/(*systeme).nombre;
			actuel = ancien;
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
			}
		}

	return 0;
	}

int fichierFonctionSinus(systemeT * systeme, int numero)
	{
	float ancien, actuel;
	int i;
	fichierFonctionNulle(systeme);
	if(numero == 1)
		{
		printf("Réinitialisation du système, numero = 1\n");
		}
	else
		{
		printf("Réinitialisation du système, numero != 1\n");
		for(i=0;i<(*systeme).nombre/2;i++)
			{
			ancien = i*numero/(*systeme).nombre;
			actuel = ancien;
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
			}
		}

	return 0;
	}


///////////////////////////////////////////////////////////////////////////////////////////////

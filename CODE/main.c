#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "../1/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../1/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../1/ESLib.h" // Pour utiliser valeurAleatoire()



// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

#include "header.h"


// Fonction de trace de cercle
void cercle(float centreX, float centreY, float rayon);
/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);
void menuQuitter();
void menu();
void menu_perdre();
Joueur initialise_joueur(Joueur);

int main(int argc, char **argv)
{
	
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	
	return 0;
}



/* Fonction de trace de cercle */

void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 20; // Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2.*M_PI/Pas;
	int index;
	
	for (index = 0; index < Pas; ++index) // Pour chaque secteur
	{
		const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
			// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
	
}


/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	static DonneesImageRGB *image_fond = NULL; // L'image a afficher au centre de l'ecran
	
	static int condition_quitter;
	static int condition_perdre;
	static int Menu;
	static int termine_salle;
	
	static Joueur joueur;
	static Fantome fantome;
	
	static int vxJoueur;
	static int saut;
	static int gravite;
	
	static int condition_droite =0;
	static int condition_gauche =0;	
	static int condition_haut =0;

	
	static int compteur_temps =0;
	
	/*----A voir pour mettre dans une fonction---*/	
	block niveau[2];
 	int stop = 0;
 	
 	niveau[0] = initialise_block(niveau[0]);
	niveau[1] = initialise_block2(niveau[1]);
 	static int nbNiveau = 0;
 	/*------------------------------------------*/
 	
 	static parametre parametres;
 	
	switch (evenement)
	{
		case Initialisation:
			/* Le message "Initialisation" est envoye une seule fois, au debut du
			programme : il permet de fixer "image" a la valeur qu'il devra conserver
			jusqu'a la fin du programme : soit "image" reste a NULL si l'image n'a
			pas pu etre lue, soit "image" pointera sur une structure contenant
			les caracteristiques de l'image "imageNB.bmp" */

			// Configure le systeme pour generer un message Temporisation
			// toutes les 20 millisecondes
			image_fond = lisBMPRGB("donjon.bmp");
			
			saut = hauteurFenetre()*0.035;
			vxJoueur = largeurFenetre()*0.01;
			gravite = hauteurFenetre()*0.0055;
			
			termine_salle =0;
			condition_quitter = 0;
			condition_perdre = 0;
			
			Menu = 0;
			nbNiveau = 0;
			
			joueur = initialise_joueur(joueur);
			fantome = initialise_fantome(fantome);
				
			demandeTemporisation(20);
			break;
		
		case Temporisation:
			
			/*----------------------------------------------gere les collision et les deplacements---------------------------------*/
			fantome = mouvement_fantome(fantome);
			if(condition_perdre != 1) condition_perdre = perdu(fantome, joueur);
			if(condition_perdre != 1) condition_perdre = perdre_piege(joueur, niveau[nbNiveau], vxJoueur ,gravite);
			if(compteur_temps == 0) stop = bloque_direction_bas(niveau[nbNiveau], joueur, gravite);
			if(stop !=1 && condition_perdre !=1){
				joueur = MoveVertical(joueur, -gravite);
			}
			else{
				if(condition_haut==1){
					while(compteur_temps <4){
						stop = bloque_direction_haut(niveau[nbNiveau], joueur, saut);
						if(stop != 1){
							joueur = MoveVertical(joueur, saut);
						}
						compteur_temps++;
					}
					compteur_temps =0;
					condition_haut =0;	
				}			
			}
			
					
			if(condition_droite ==1 && condition_perdre !=1){
				stop = bloque_direction_droite(niveau[nbNiveau], joueur, vxJoueur);
				if(stop !=1){
					joueur = MoveLateral(joueur, vxJoueur);
					condition_droite =0;
				}
			}
			
			if(condition_gauche ==1 && condition_perdre !=1){
				stop = bloque_direction_gauche(niveau[nbNiveau], joueur, vxJoueur);
				if(stop !=1){
					joueur = MoveLateral(joueur, -vxJoueur);
					condition_gauche = 0;
				}
			}
			
			joueur = doodle(joueur); //peut être l'enlever, ca permet de passer d'un coter à lautre de la salle si on sort de la fenetre
			termine_salle = sortie_salle(joueur, niveau[nbNiveau]);
			/*-------------------------------------------------------------------------------------------------------------------*/
			
			rafraichisFenetre();		
			break;	
			
		case Affichage:
			// On part d'un fond d'ecran blanc
			effaceFenetre (255, 255, 255);
			/*
			if (image_fond != NULL) // Si l'image a pu etre lue
			{
				// On affiche l'image
				ecrisImage(largeurFenetre()*0, hauteurFenetre()*0, image_fond->largeurImage, image_fond->hauteurImage, image_fond->donneesRGB);
			}
			*/
			couleurCourante(255, 0, 0);
			if( (condition_quitter != 1) && Menu == 0){
				menu();
			}			
			else if( (condition_quitter != 1) && (Menu == 1) && (condition_perdre != 1)){
				//affiche la sortie
				couleurCourante(2, 0, 255);
				rectangle(niveau[nbNiveau].sortie_Xpt1, niveau[nbNiveau].sortie_Ypt1, niveau[nbNiveau].sortie_Xpt2, niveau[nbNiveau].sortie_Ypt2);
				
				//affiche le terrain 
				couleurCourante(255, 0, 0);
				for(int i=0; i<niveau[nbNiveau].sizeMap; i++){
					rectangle(niveau[nbNiveau].map[i].Xpt1, niveau[nbNiveau].map[i].Ypt1, niveau[nbNiveau].map[i].Xpt2, niveau[nbNiveau].map[i].Ypt2);
				}
				
				//afiche les pieges
				couleurCourante(128, 128, 128);
				for(int i=0; i<niveau[nbNiveau].nbPieges; i++){
					triangle(niveau[nbNiveau].pieges[i].xCoin1, niveau[nbNiveau].pieges[i].yCoin1, niveau[nbNiveau].pieges[i].xCoin2, niveau[nbNiveau].pieges[i].yCoin2, niveau[nbNiveau].pieges[i].xCoin3, niveau[nbNiveau].pieges[i].yCoin3);
				}
				
				//affiche le joueur
				couleurCourante(255, 0, 0);
				rectangle(joueur.xPt1, joueur.yPt1, joueur.xPt2, joueur.yPt2);
				
				couleurCourante(255, 2, 255);
				cercle(fantome.xFantome, fantome.yFantome, fantome.rayon);
				
				if(termine_salle == 1){
					nbNiveau++;
					joueur = initialise_joueur(joueur);
					fantome = initialise_fantome(fantome);
					fantome.vxFantome++;
					fantome.vyFantome--;
					termine_salle = 0;
				}
			}
			else if(condition_perdre == 1){
				menu_perdre();
			}
			else if( condition_quitter == 1 ){
				menuQuitter();
			}

			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 20 millisecondes (rapide)
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 100 millisecondes (lent)
					demandeTemporisation(100);
					break;

				case 'n':
					// Configure le systeme pour ne plus generer de message Temporisation
					demandeTemporisation(-1);
					break;
										
				case 'D':
				case 'd':
					condition_droite=1;
					break;
				
				case 'Q':
				case 'q':
					condition_gauche=1;
					break;
					
				case ' '://pour sauter
					condition_haut=1;
					break;
					
				case 'W':
				case 'w':
					if(condition_quitter ==0) condition_quitter =1;
					else condition_quitter =0;
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			switch(toucheClavier())
			{

			}
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				if(Menu ==0){
					if( (abscisseSouris() > largeurFenetre()*0.3 && abscisseSouris() < largeurFenetre()*0.7)){
						if(ordonneeSouris() > hauteurFenetre()*0.4 && ordonneeSouris() < hauteurFenetre()*0.5){
							Menu =1;
						}
						else if(ordonneeSouris() > hauteurFenetre()*0.25 && ordonneeSouris() < hauteurFenetre()*0.35){
							parametres = charger_sauvegarde(parametres);
							nbNiveau = parametres.nbNiveau_sauvegarde;
							fantome = parametres.fantome_sauvegarde;
							Menu =1;
						}
					}
				}
			
				if( (abscisseSouris() > largeurFenetre()*0.3 && abscisseSouris() < largeurFenetre()*0.7) && (condition_quitter == 1) ){
					if(ordonneeSouris() < hauteurFenetre()*0.625 && ordonneeSouris() > hauteurFenetre()*0.375){
						parametres = enregistre_parametre(parametres, fantome, nbNiveau);
						sauvegarde(parametres);
						libereDonneesImageRGB(&image_fond);
						termineBoucleEvenements();
					}
				}
				
				if(condition_perdre == 1){
					if( (abscisseSouris() > largeurFenetre()*0.3 && abscisseSouris() < largeurFenetre()*0.7)){
						if(ordonneeSouris() > hauteurFenetre()*0.4 && ordonneeSouris() < hauteurFenetre()*0.5){
							nbNiveau = 0;
							joueur = initialise_joueur(joueur);
							fantome = initialise_fantome(fantome);
							condition_perdre = 0; 
						}
						else if(ordonneeSouris() > hauteurFenetre()*0.25 && ordonneeSouris() < hauteurFenetre()*0.35){
							libereDonneesImageRGB(&image_fond);
							termineBoucleEvenements();
						}
					}
				}
							
			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
		
			// Donc le systeme nous en informe
			saut = hauteurFenetre()*0.035;
			vxJoueur = largeurFenetre()*0.01;
			gravite = hauteurFenetre()*0.0055;
			fantome = redimensionnement(fantome);
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}

void menuQuitter(){
	rectangle(largeurFenetre()*0.3, hauteurFenetre()*0.625, largeurFenetre()*0.7, hauteurFenetre()*0.375);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("QUITTER", 20, largeurFenetre()*0.45, hauteurFenetre()*0.48);
}

void menu(){
	epaisseurDeTrait(3);
	afficheChaine("TITRE DE JEU", 20, largeurFenetre()*0.45, hauteurFenetre()*0.55);
	rectangle(largeurFenetre()*0.35, hauteurFenetre()*0.4, largeurFenetre()*0.7, hauteurFenetre()*0.5);
	rectangle(largeurFenetre()*0.35, hauteurFenetre()*0.25, largeurFenetre()*0.7, hauteurFenetre()*0.35);
	couleurCourante(255,255,255);
	afficheChaine("JOUER", 20, largeurFenetre()*0.45, hauteurFenetre()*0.45);
	afficheChaine("CHARGER UNE SAUVEGARDE", 20, largeurFenetre()*0.45, hauteurFenetre()*0.3);		
}

void menu_perdre(){
	afficheChaine("VOUS AVEZ PERDUE", 20, largeurFenetre()*0.45, hauteurFenetre()*0.55);
	rectangle(largeurFenetre()*0.35, hauteurFenetre()*0.4, largeurFenetre()*0.7, hauteurFenetre()*0.5);
	rectangle(largeurFenetre()*0.35, hauteurFenetre()*0.25, largeurFenetre()*0.7, hauteurFenetre()*0.35);
	couleurCourante(255,255,255);
	afficheChaine("RECOMMENCER", 20, largeurFenetre()*0.45, hauteurFenetre()*0.45);
	afficheChaine("QUITTER", 20, largeurFenetre()*0.45, hauteurFenetre()*0.3);
}

Joueur initialise_joueur(Joueur joueur){
	joueur.xPt1 = largeurFenetre()*0;
	joueur.xPt2 = largeurFenetre()*0 + 40;			
	joueur.yPt1 = hauteurFenetre()*0.8;
	joueur.yPt2 = hauteurFenetre()*0.8 + 40;
	
	return joueur;
}



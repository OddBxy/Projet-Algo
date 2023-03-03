#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <time.h>
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


int finTempsJeu(int tpsJeu);
void afficheTps(int tpsJeu);


static int tpsJeu = 0;
static time_t time1, time2;
static DonneesImageRGB *imageFin = NULL;
static DonneesImageRGB *image_acceuil = NULL;
static DonneesImageRGB *image_jeu = NULL;

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
	//static DonneesImageRGB *image_fond = NULL;
	
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
	int nbNiveau = 2;
 	static int stop = 0;
 	
 	niveau[0] = initialise_block(niveau[0]);
	niveau[1] = initialise_block2(niveau[1]);
 	static int index_niveau = 0;
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
			//image_fond = lisBMPRGB("donjon.bmp");
			
			saut = hauteurFenetre()*0.035;
			vxJoueur = largeurFenetre()*0.01;
			gravite = hauteurFenetre()*0.0055;
			
			termine_salle =0;
			condition_quitter = 0;
			condition_perdre = 0;
			
			Menu = 0;
			index_niveau = 0;
			
			joueur = initialise_joueur(joueur);
			fantome = initialise_fantome(fantome);
				
				
			imageFin = lisBMPRGB("../IMAGES/ImageFin.bmp");
			image_acceuil = lisBMPRGB("../IMAGES/Image_acceuil.bmp");
			image_jeu = lisBMPRGB("../IMAGES/Image_jeu.bmp");
			
			demandeTemporisation(20);
			break;
		
		case Temporisation:
			
			/*----------------------------------------------gere les collision et les deplacements---------------------------------*/
			fantome = mouvement_fantome(fantome);
			if(condition_perdre != 1 && index_niveau != nbNiveau) condition_perdre = perdu(fantome, joueur);
			if(condition_perdre != 1 && index_niveau != nbNiveau) condition_perdre = perdre_piege(joueur, niveau[index_niveau], vxJoueur ,gravite);
			if(compteur_temps == 0 && index_niveau != nbNiveau) stop = bloque_direction_bas(niveau[index_niveau], joueur, gravite);
			if(stop !=1 && condition_perdre !=1){
				joueur = MoveVertical(joueur, -gravite);
			}
			else{
				if(condition_haut==1 && index_niveau != nbNiveau){
					while(compteur_temps <4){
						stop = bloque_direction_haut(niveau[index_niveau], joueur, saut);
						if(stop != 1){
							joueur = MoveVertical(joueur, saut);
						}
						compteur_temps++;
					}
					compteur_temps =0;
					condition_haut =0;	
				}			
			}
			
					
			if(condition_droite ==1 && condition_perdre !=1 && index_niveau != nbNiveau){
				stop = bloque_direction_droite(niveau[index_niveau], joueur, vxJoueur);
				if(stop !=1){
					joueur = MoveLateral(joueur, vxJoueur);
					condition_droite =0;
				}
			}
			
			if(condition_gauche ==1 && condition_perdre !=1 && index_niveau != nbNiveau){
				stop = bloque_direction_gauche(niveau[index_niveau], joueur, vxJoueur);
				if(stop !=1){
					joueur = MoveLateral(joueur, -vxJoueur);
					condition_gauche = 0;
				}
			}
			
			joueur = doodle(joueur); //peut être l'enlever, ca permet de passer d'un coter à lautre de la salle si on sort de la fenetre
			if(index_niveau != nbNiveau) termine_salle = sortie_salle(joueur, niveau[index_niveau]);
			/*-------------------------------------------------------------------------------------------------------------------*/
			
			rafraichisFenetre();		
			break;	
			
		case Affichage:
			// On part d'un fond d'ecran blanc
			effaceFenetre (255, 255, 255);
			/*
			if (image_terrain != NULL) // Si l'image a pu etre lue
			{
				// On affiche l'image
				ecrisImage(largeurFenetre()*0, hauteurFenetre()*0, image_terrain->largeurImage, image_terrain->hauteurImage, image_terrain->donneesRGB);
			}*/
			couleurCourante(255, 0, 0);
			if( (condition_quitter != 1) && Menu == 0){
				menu();
			}			
			else if( (condition_quitter != 1) && (Menu == 1) && (condition_perdre != 1) && (index_niveau < nbNiveau)){
			
				if(image_jeu != NULL){
					ecrisImage(0, 0, image_jeu->largeurImage, image_jeu->hauteurImage, image_jeu->donneesRGB);
				}
				//affiche la sortie
				couleurCourante(2, 0, 255);
				rectangle(niveau[index_niveau].sortie_Xpt1, niveau[index_niveau].sortie_Ypt1, niveau[index_niveau].sortie_Xpt2, niveau[index_niveau].sortie_Ypt2);
				
				//affiche le terrain 
				couleurCourante(255, 0, 0);
				for(int i=0; i<niveau[index_niveau].sizeMap; i++){
					rectangle(niveau[index_niveau].map[i].Xpt1, niveau[index_niveau].map[i].Ypt1, niveau[index_niveau].map[i].Xpt2, niveau[index_niveau].map[i].Ypt2);
					if(niveau[index_niveau].map[i].image_terrain != NULL) ecrisImage(niveau[index_niveau].map[i].Xpt1, niveau[index_niveau].map[i].Ypt1, niveau[index_niveau].map[i].image_terrain->largeurImage, niveau[index_niveau].map[i].image_terrain->hauteurImage, niveau[index_niveau].map[i].image_terrain->donneesRGB);
				}
				
				//afiche les pieges
				couleurCourante(128, 128, 128);
				for(int i=0; i<niveau[index_niveau].nbPieges; i++){
					triangle(niveau[index_niveau].pieges[i].xCoin1, niveau[index_niveau].pieges[i].yCoin1, niveau[index_niveau].pieges[i].xCoin2, niveau[index_niveau].pieges[i].yCoin2, niveau[index_niveau].pieges[i].xCoin3, niveau[index_niveau].pieges[i].yCoin3);
				}
				
				//affiche le joueur
				couleurCourante(255, 0, 0);
				//rectangle(joueur.xPt1, joueur.yPt1, joueur.xPt2, joueur.yPt2);
				if(stop == 1) ecrisImage(joueur.xPt1, joueur.yPt1, joueur.joueur_idle->largeurImage, joueur.joueur_idle->hauteurImage, joueur.joueur_idle->donneesRGB);
				else if(stop != 1) ecrisImage(joueur.xPt1, joueur.yPt1, joueur.joueur_fall->largeurImage, joueur.joueur_fall->hauteurImage, joueur.joueur_fall->donneesRGB);
				couleurCourante(255, 2, 255);
				cercle(fantome.xFantome, fantome.yFantome, fantome.rayon);
				
				if(termine_salle == 1){
					index_niveau++;
					termine_salle = 0;
					joueur = initialise_joueur(joueur);
					fantome = initialise_fantome(fantome);
					fantome.vxFantome++;
					fantome.vyFantome--;
				
				}
			}
			else if(condition_perdre == 1){
				menu_perdre();
			}
			else if( condition_quitter == 1 ){
				menuQuitter();
			}
			else if(index_niveau == nbNiveau){
				if(tpsJeu == 0){
					time(&time2);
					tpsJeu = finTempsJeu(tpsJeu);
				}
				afficheTps(tpsJeu);				
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

							time(&time1);
							Menu =1;
						}
						else if(ordonneeSouris() > hauteurFenetre()*0.25 && ordonneeSouris() < hauteurFenetre()*0.35){
							parametres = charger_sauvegarde(parametres);
							index_niveau = parametres.nbNiveau_sauvegarde;
							fantome = parametres.fantome_sauvegarde;

							time(&time1);
							Menu =1;
						}
					}
				}
			
				if( (abscisseSouris() > largeurFenetre()*0.3 && abscisseSouris() < largeurFenetre()*0.7) && (condition_quitter == 1) ){
					if(ordonneeSouris() < hauteurFenetre()*0.625 && ordonneeSouris() > hauteurFenetre()*0.375){
						parametres = enregistre_parametre(parametres, fantome, index_niveau);
						sauvegarde(parametres);
						//libereDonneesImageRGB(&image_terrain);
						termineBoucleEvenements();
					}
				}
				
				if(condition_perdre == 1){
					if( (abscisseSouris() > largeurFenetre()*0.3 && abscisseSouris() < largeurFenetre()*0.7)){
						if(ordonneeSouris() > hauteurFenetre()*0.4 && ordonneeSouris() < hauteurFenetre()*0.5){
							index_niveau = 0;
							joueur = initialise_joueur(joueur);
							fantome = initialise_fantome(fantome);
							condition_perdre = 0; 
						}
						else if(ordonneeSouris() > hauteurFenetre()*0.25 && ordonneeSouris() < hauteurFenetre()*0.35){
							//libereDonneesImageRGB(&image_terrain);
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
	if(image_acceuil != NULL){
		ecrisImage(0, 0, image_acceuil->largeurImage, image_acceuil->hauteurImage, image_acceuil->donneesRGB);	
	}
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
	joueur.joueur_idle = lisBMPRGB("../IMAGES/joueur_idle.bmp");
	joueur.joueur_fall = lisBMPRGB("../IMAGES/joueur_fall.bmp");
	joueur.xPt1 = largeurFenetre()*0;
	joueur.yPt1 = hauteurFenetre()*0.8;
	joueur.xPt2 = joueur.xPt1 + joueur.joueur_idle->largeurImage;			
	joueur.yPt2 = joueur.yPt1 + joueur.joueur_idle->hauteurImage;
	
	return joueur;
}



int finTempsJeu(int tpsJeu){ //Fonction à appeler à la fin du jeu 

	tpsJeu = difftime(time2, time1);
	return tpsJeu;
}

void afficheTps(int tpsJeu){

	//determination des minutes de jeu
	int min = tpsJeu/60;

	//determination des secondes de jeu
	int sec = 0;
	if(min != 0){
	sec = tpsJeu - (min*60);
	}
	else{
	sec = tpsJeu;
	}

	//affichage de l'image de fond
	if(imageFin != NULL){
		ecrisImage(0, 0, imageFin->largeurImage, imageFin->hauteurImage, imageFin->donneesRGB);
	}

	//conversion des minutes en chaine de caractères pour l'afficher
	char mins[sizeof(int)];
	sprintf(mins, "%d", min);

	//conversion des secondes en chaine de caractères pour l'afficher
	char secs[sizeof(int)];
	sprintf(secs, "%d", sec);

	//affichage des minutes
	couleurCourante(255, 255, 255);
	epaisseurDeTrait(8);
	afficheChaine(mins, 35, largeurFenetre()*0.365, hauteurFenetre()*0.2223);


	//affichage des secondes
	epaisseurDeTrait(8);
	afficheChaine(secs, 35, largeurFenetre()*0.495, hauteurFenetre()*0.2223);

}



#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()

#include "header.h"

void menuQuitter(){
	rectangle(largeurFenetre()*0.3, hauteurFenetre()*0.625, largeurFenetre()*0.7, hauteurFenetre()*0.375);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("QUITTER", 20, largeurFenetre()*0.45, hauteurFenetre()*0.48);
}

void menu(DonneesImageRGB *image_acceuil ){
	if(image_acceuil != NULL){
		ecrisImage(0, 0, image_acceuil->largeurImage, image_acceuil->hauteurImage, image_acceuil->donneesRGB);	
	}
	epaisseurDeTrait(3);
	afficheChaine("TITRE DE JEU", 20, largeurFenetre()*0.45, hauteurFenetre()*0.55);
	rectangle(largeurFenetre()*0.35, hauteurFenetre()*0.4, largeurFenetre()*0.7, hauteurFenetre()*0.5);
	rectangle(largeurFenetre()*0.35, hauteurFenetre()*0.25, largeurFenetre()*0.7, hauteurFenetre()*0.35);
	couleurCourante(255,255,255);
	afficheChaine("JOUER", 20, largeurFenetre()*0.45, hauteurFenetre()*0.45);
	afficheChaine("CHARGER UNE SAUVEGARDE", 15, largeurFenetre()*0.4, hauteurFenetre()*0.3);		
}

void menu_perdre(DonneesImageRGB *death_screen){
	ecrisImage(0, 0, death_screen->largeurImage, death_screen->hauteurImage, death_screen->donneesRGB);
	afficheChaine("VOUS AVEZ PERDU", 20, largeurFenetre()*0.45, hauteurFenetre()*0.55);
	rectangle(largeurFenetre()*0.35, hauteurFenetre()*0.4, largeurFenetre()*0.7, hauteurFenetre()*0.5);
	rectangle(largeurFenetre()*0.35, hauteurFenetre()*0.25, largeurFenetre()*0.7, hauteurFenetre()*0.35);
	couleurCourante(255,255,255);
	afficheChaine("RECOMMENCER", 20, largeurFenetre()*0.45, hauteurFenetre()*0.45);
	afficheChaine("QUITTER", 20, largeurFenetre()*0.45, hauteurFenetre()*0.3);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "../GFX/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../GFX/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../GFX/ESLib.h" // Pour utiliser valeurAleatoire()

typedef struct forme{
	DonneesImageRGB *image_terrain; 
	float Xpt1;
	float Xpt2;
	float Ypt1;
	float Ypt2;	
}forme;

typedef struct pique{
	float xCoin1;
	float yCoin1;
	float xCoin2;
	float yCoin2;
	float xCoin3;
	float yCoin3;
}pique;

typedef struct block{
	int sizeMap;
	int nbPieges;
	forme *map;
	pique *pieges;
	DonneesImageRGB *image_exit;
	float sortie_Xpt1, sortie_Xpt2;
	float sortie_Ypt1, sortie_Ypt2;
}block;


typedef struct Joueur{
	DonneesImageRGB *joueur_idle;
	DonneesImageRGB *joueur_fall;
	int xPt1, xPt2;
	int yPt1, yPt2;
	
}Joueur;

typedef struct Fantome{
	int xFantome;
	int yFantome;
	int vxFantome;
	int vyFantome;
	
	int rayon;
}Fantome;

typedef struct parametre{
	Fantome fantome_sauvegarde;
	int nbNiveau_sauvegarde;
}parametre;


void menuQuitter();
void menu(DonneesImageRGB *image_acceuil);
void menu_perdre(DonneesImageRGB *death_screen);

block initialise_block(block);
block initialise_block2(block);
forme initialise_forme(float, float, char *chemin_terrain);
pique initialise_pique(float, float, float, float);

int bloque_direction_haut(block, Joueur, int);
int bloque_direction_bas(block , Joueur, int);
int bloque_direction_droite(block , Joueur, int);
int bloque_direction_gauche(block , Joueur, int);
int perdre_piege(Joueur, block, float , float);

Joueur MoveVertical(Joueur , int);
Joueur MoveLateral(Joueur, int);
Joueur doodle(Joueur);
int sortie_salle(Joueur , block);

Fantome redimensionnement(Fantome);
Fantome initialise_fantome(Fantome);
Fantome mouvement_fantome(Fantome fantome);

int perdu(Fantome, Joueur);

void sauvegarde(parametre);
parametre charger_sauvegarde(parametre sauvegarde);
parametre enregistre_parametre(parametre, Fantome, int);


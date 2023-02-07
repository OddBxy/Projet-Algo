#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "../1/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../1/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../1/ESLib.h" // Pour utiliser valeurAleatoire()


typedef struct forme{
	float Xpt1;
	float Xpt2;
	float Ypt1;
	float Ypt2;
}forme;

typedef struct block{
	int sizeMap;
	forme *map;
	int stopYh, stopYb;
	int stopXg, stopXd;
}block;


typedef struct Joueur{
	int xPt1, xPt2;
	int yPt1, yPt2;
}Joueur;

block initialise_block(block);
forme initialise_forme(float, float, float, float);
int bloque_direction_haut(block, Joueur, int);
int bloque_direction_bas(block , Joueur, int);
int bloque_direction_droite(block , Joueur, int);
int bloque_direction_gauche(block , Joueur, int);

Joueur MoveVertical(Joueur , int);
Joueur MoveLateral(Joueur, int);
Joueur doodle(Joueur);


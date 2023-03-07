#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include "header.h"

block initialise_block(block NV){

	NV.image_exit = lisBMPRGB("../IMAGES/door.bmp");
	forme a = initialise_forme(0, 0, "../IMAGES/terrain6.bmp");
	forme d = initialise_forme(0.081, 0, "../IMAGES/terrain6.bmp");
	forme e = initialise_forme(0.162, 0, "../IMAGES/terrain6.bmp");
	forme f = initialise_forme(0.243, 0, "../IMAGES/terrain6.bmp");
	forme b = initialise_forme(0.324, 0, "../IMAGES/terrain6.bmp"); 	
	forme c = initialise_forme(0.405, 0, "../IMAGES/terrain6.bmp"); 	

	NV.sizeMap = 6;
	NV.map = (forme*) calloc(NV.sizeMap, sizeof(forme));
			
	NV.map[0] = a;
	NV.map[1] = b;
	NV.map[2] = c;
	NV.map[3] = d;
	NV.map[4] = e;
	NV.map[5] = f;
	
	pique piqueA = initialise_pique( 0.25, 0.105, 0.28, 0.105);
	pique piqueB = initialise_pique( 0.28, 0.105, 0.31, 0.105);
	
	NV.nbPieges = 2;
	NV.pieges = (pique*) calloc(NV.nbPieges, sizeof(pique));
	
	NV.pieges[0] = piqueA;
	NV.pieges[1] = piqueB;

	NV.sortie_Xpt1 = largeurFenetre() - NV.image_exit->largeurImage;
	NV.sortie_Ypt1 = NV.image_exit->largeurImage;
	
	NV.sortie_Xpt2 = NV.sortie_Xpt1 + NV.image_exit->largeurImage;
	NV.sortie_Ypt2 = NV.sortie_Ypt1 + NV.image_exit->hauteurImage;	
	

	return NV;
}
/*
block initialise_block2(block NV){

	NV.image_exit = lisBMPRGB("../IMAGES/door.bmp");
	forme a = initialise_forme(0, 0, "../IMAGES/terrain6.bmp");
	

	NV.sizeMap = 1;
	NV.map = (forme*) calloc(NV.sizeMap, sizeof(forme));
			
	NV.map[0] = a;

	NV.nbPieges = 0;
	NV.pieges = (pique*) calloc(NV.sizeMap, sizeof(pique));

	NV.sortie_Xpt1 = largeurFenetre() - NV.image_exit->largeurImage;
	NV.sortie_Ypt1 = NV.image_exit->largeurImage;
	
	NV.sortie_Xpt2 = NV.sortie_Xpt1 + NV.image_exit->largeurImage;
	NV.sortie_Ypt2 = NV.sortie_Ypt1 + NV.image_exit->hauteurImage;		
	

	return NV;
}*/

block initialise_block2(block NV){
	NV.image_exit = lisBMPRGB("../IMAGES/door.bmp");
	
	forme a1 = initialise_forme(0.82, 0.5,"../IMAGES/terrain6.bmp");
	forme a2 = initialise_forme(0.82, 0.39,"../IMAGES/terrain6.bmp");
	forme a3 = initialise_forme(0.82, 0.28,"../IMAGES/terrain6.bmp");
	forme a4 = initialise_forme(0.18, 0.6, "../IMAGES/terrain6.bmp");
	forme a5 = initialise_forme(0.26, 0.6, "../IMAGES/terrain6.bmp");
	forme a6 = initialise_forme(0.34, 0.6, "../IMAGES/terrain6.bmp");
	forme a7 = initialise_forme(0.42, 0.6, "../IMAGES/terrain6.bmp");
	forme a8 = initialise_forme(0.5, 0.6, "../IMAGES/terrain6.bmp");
	forme a9 = initialise_forme(0.58, 0.6, "../IMAGES/terrain6.bmp");
	forme a10 = initialise_forme(0.66, 0.6,"../IMAGES/terrain6.bmp");
	forme a11 = initialise_forme(0.74, 0.6, "../IMAGES/terrain6.bmp");
	forme a12 = initialise_forme(0.82, 0.6, "../IMAGES/terrain6.bmp");
	forme a13 = initialise_forme(0, 0.6, "../IMAGES/terrain6.bmp");
	forme a14 = initialise_forme(0.5, 0.6, "../IMAGES/terrain6.bmp");
	forme a15 = initialise_forme(0.58, 0.6, "../IMAGES/terrain6.bmp");
	forme a16 = initialise_forme(0, 0, "../IMAGES/terrain6.bmp");
	forme a17 = initialise_forme(0.08, 0, "../IMAGES/terrain6.bmp");
	forme a18 = initialise_forme(0.16, 0, "../IMAGES/terrain6.bmp");
	forme a19 = initialise_forme(0.32, 0, "../IMAGES/terrain6.bmp");
	forme a20 = initialise_forme(0.56, 0.11,"../IMAGES/terrain6.bmp");
	forme a21 = initialise_forme(0.64, 0.11, "../IMAGES/terrain6.bmp");
	forme a22 = initialise_forme(0.56, 0,"../IMAGES/terrain6.bmp");
	forme a23 = initialise_forme(0.64, 0, "../IMAGES/terrain6.bmp");
	forme a31 = initialise_forme(0.72, 0, "../IMAGES/terrain6.bmp");
	forme a32 = initialise_forme(0.8, 0, "../IMAGES/terrain6.bmp");
	forme a33 = initialise_forme(0.88, 0, "../IMAGES/terrain6.bmp");
	forme a34 = initialise_forme(0.96, 0, "../IMAGES/terrain6.bmp");
	forme a24 = initialise_forme(0.56, 0.22,"../IMAGES/terrain6.bmp");
	forme a25 = initialise_forme(0.82, 0.6, "../IMAGES/terrain6.bmp");
	forme a26 = initialise_forme(0, 0.6, "../IMAGES/terrain6.bmp");
	forme a27 = initialise_forme(0.5, 0.6, "../IMAGES/terrain6.bmp");
	forme a28 = initialise_forme(0.58, 0.6, "../IMAGES/terrain6.bmp");
	forme a29 = initialise_forme(0.05, 0.49, "../IMAGES/terrain6.bmp");
	forme a30 = initialise_forme(0.13, 0.49, "../IMAGES/terrain6.bmp");
	
	NV.sizeMap = 35;
	NV.map = (forme*) calloc(NV.sizeMap, sizeof(forme));
	
	NV.map[0] = a1;
	NV.map[1] = a2;
	NV.map[2] = a3;
	NV.map[3] = a4;
	NV.map[4] = a5;
	NV.map[5] = a6;
	NV.map[6] = a7;
	NV.map[7] = a8;
	NV.map[8] = a9;
	NV.map[9] = a10;
	NV.map[10] = a11;
	NV.map[11] = a12;
	NV.map[12] = a13;
	NV.map[13] = a14;
	NV.map[14] = a15;
	NV.map[15] = a16;
	NV.map[16] = a17;
	NV.map[17] = a18;
	NV.map[18] = a19;
	NV.map[19] = a20;
	NV.map[20] = a21;
	NV.map[21] = a22;
	NV.map[22] = a23;
	NV.map[23] = a24;
	NV.map[24] = a25;
	NV.map[25] = a26;
	NV.map[26] = a27;
	NV.map[27] = a28;
	NV.map[28] = a29;
	NV.map[29] = a30;
	NV.map[30] = a31;
	NV.map[31] = a32;
	NV.map[32] = a33;
	NV.map[33] = a34;
	
	pique piqueA = initialise_pique( 0.09, 0.6, 0.16, 0.6);
	NV.nbPieges = 1;
	NV.pieges = (pique*) calloc(NV.nbPieges, sizeof(pique));
	NV.pieges[0] = piqueA;
	
	
	NV.sortie_Xpt1 = largeurFenetre()*0;
	NV.sortie_Xpt2 = largeurFenetre()*0.1;
	NV.sortie_Ypt1 = hauteurFenetre()*0.1;
	NV.sortie_Ypt2 = hauteurFenetre()*0.25; 
	return NV;
	
}

forme initialise_forme(float FacteurXpt1, float FacteurYpt1,  char *chemin_image){
	forme a;
	a.image_terrain = lisBMPRGB(chemin_image);
	a.Xpt1 = largeurFenetre()*FacteurXpt1;
	a.Ypt1 = hauteurFenetre()*FacteurYpt1;
	a.Xpt2 = a.Xpt1 + a.image_terrain->largeurImage;
	a.Ypt2 = a.Ypt1 + a.image_terrain->hauteurImage;

	return a;
}

pique initialise_pique(float xFacteur1, float yFacteur1, float xFacteur2, float yFacteur2){
	//créer un pique sous forme de triangle iso, si le joueur le touche la partie est perdue
	
	float hauteur = xFacteur2 - xFacteur1;
	pique a;
	a.xCoin1 = largeurFenetre()*xFacteur1;
	a.yCoin1 = hauteurFenetre()*yFacteur1;
	a.xCoin2 = largeurFenetre()*xFacteur2;
	a.yCoin2 = hauteurFenetre()*yFacteur2;
	a.xCoin3 = (a.xCoin2 + a.xCoin1)*0.5;
	a.yCoin3 = a.yCoin1 + hauteurFenetre()*hauteur;

	return a;
}




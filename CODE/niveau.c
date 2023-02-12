#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include "header.h"

block initialise_block(block NV){

	
	forme a = initialise_forme(0, 0, 1, 0.15);
	forme b = initialise_forme(0.625, 0.15, 0.75, 0.30); 	
	forme c = initialise_forme(0.56, 0.23, 0.625, 0.250); 	

	NV.sizeMap = 3;
	NV.map = (forme*) calloc(NV.sizeMap, sizeof(forme));
			
	NV.map[0] = a;
	NV.map[1] = b;
	NV.map[2] = c;
	
	pique piqueA = initialise_pique( 0.73, 0.3, 0.75, 0.30);
	pique piqueB = initialise_pique(0.71, 0.3, 0.73, 0.30);
	
	NV.nbPieges = 2;
	NV.pieges = (pique*) calloc(NV.nbPieges, sizeof(pique));
	
	NV.pieges[0] = piqueA;
	NV.pieges[1] = piqueB;

	NV.sortie_Xpt1 = largeurFenetre()*0.875;
	NV.sortie_Xpt2 = largeurFenetre()*0.9735;
	
	NV.sortie_Ypt1 = hauteurFenetre()*0.15;
	NV.sortie_Ypt2 = hauteurFenetre()*0.15 + 100;	
	

	return NV;
}

block initialise_block2(block NV){

	
	forme a = initialise_forme(0, 0, 1, 0.15);
	

	NV.sizeMap = 1;
	NV.map = (forme*) calloc(NV.sizeMap, sizeof(forme));
			
	NV.map[0] = a;

	NV.nbPieges = 0;
	NV.pieges = (pique*) calloc(NV.sizeMap, sizeof(pique));

	NV.sortie_Xpt1 = largeurFenetre()*0.875;
	NV.sortie_Xpt2 = largeurFenetre()*0.9735;
	
	NV.sortie_Ypt1 = hauteurFenetre()*0.15;
	NV.sortie_Ypt2 = hauteurFenetre()*0.15 + 100;		
	

	return NV;
}

forme initialise_forme(float FacteurXpt1, float FacteurYpt1, float FacteurXpt2, float FacteurYpt2){
	forme a;
	a.Xpt1 = largeurFenetre()*FacteurXpt1;
	a.Xpt2 = largeurFenetre()*FacteurXpt2;
	a.Ypt2 = hauteurFenetre()*FacteurYpt2;
	a.Ypt1 = hauteurFenetre()*FacteurYpt1;

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




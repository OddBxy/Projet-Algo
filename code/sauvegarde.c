#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "header.h"

void sauvegarde(parametre sauvegarde){

	parametre *pointer = &sauvegarde;
	FILE* fichier = NULL;
	fichier = fopen("../sauvegardes/sauvegarde.txt", "wb");
	if(fichier != NULL){
		fwrite(pointer, sizeof(parametre), 1, fichier);
		fclose(fichier);
	}
	else perror("error");
	printf("sauvegarde effectuée\n");
}

parametre charger_sauvegarde(parametre sauvegarde){
	parametre *pointer = &sauvegarde;
	FILE* fichier = NULL;	
	fichier = fopen("../sauvegardes/sauvegarde.txt", "rb");
	if(fichier == NULL) perror("error");
	fread(pointer, sizeof(parametre), 1, fichier);
	
	printf("%d\n", pointer->fantome_sauvegarde.vxFantome);
	return sauvegarde;
}

parametre enregistre_parametre(parametre parametres, Fantome fantome, int nbNiveau){
	parametres.fantome_sauvegarde = fantome;
	parametres.nbNiveau_sauvegarde = nbNiveau; 

	return parametres;
}

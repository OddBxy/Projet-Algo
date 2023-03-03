#include "header.h"

Fantome redimensionnement(Fantome fantome){
	if (fantome.xFantome >= largeurFenetre())
		fantome.xFantome = largeurFenetre()-1;
	if (fantome.yFantome >= hauteurFenetre())
		fantome.yFantome = hauteurFenetre()-1;
	return fantome;
}

Fantome initialise_fantome(Fantome fantome){
	fantome.xFantome = largeurFenetre()*valeurAleatoire();
	fantome.yFantome = hauteurFenetre()*valeurAleatoire();
	
	fantome.vxFantome = 2;
	fantome.vyFantome = -2;
	
	fantome.rayon = 10;	
	return fantome;
}

Fantome mouvement_fantome(Fantome fantome){
	fantome.xFantome += fantome.vxFantome;
	fantome.yFantome += fantome.vyFantome;

	if (fantome.xFantome < 0 || fantome.xFantome >= largeurFenetre())
		fantome.vxFantome = - fantome.vxFantome;
	if (fantome.yFantome < 0 || fantome.yFantome >= hauteurFenetre())
		fantome.vyFantome = - fantome.vyFantome;
		
	return fantome;
}

int perdu(Fantome fantome, Joueur joueur){	
	if(fantome.xFantome <= joueur.xPt2 && fantome.xFantome >= joueur.xPt1){
		if(fantome.yFantome <= joueur.yPt2 && fantome.yFantome >= joueur.yPt1 ) return 1;
	}
	return 0;
}

exe: main.o sauvegarde.o fantome.o niveau.o deplacement.o menu.o ../GFX/libisentlib.a 
	gcc -Wall main.o sauvegarde.o fantome.o niveau.o deplacement.o menu.o -o exe ../GFX/libisentlib.a -lm -lglut -lGL -lX11
	
main.o: main.c header.h ../GFX/GfxLib.h ../GFX/BmpLib.h ../GFX/ESLib.h 
	gcc -Wall -c main.c -o main.o
	
sauvegarde.o: sauvegarde.c header.h ../GFX/GfxLib.h ../GFX/BmpLib.h ../GFX/ESLib.h
	gcc -Wall -c sauvegarde.c -o sauvegarde.o  
	
fantome.o: fantome.c header.h ../GFX/GfxLib.h ../GFX/BmpLib.h ../GFX/ESLib.h
	gcc -Wall -c fantome.c -o fantome.o 
		
niveau.o: niveau.c header.h ../GFX/GfxLib.h ../GFX/BmpLib.h ../GFX/ESLib.h 
	gcc -Wall -c niveau.c -o niveau.o

deplacement.o: deplacement.c header.h	../GFX/GfxLib.h ../GFX/BmpLib.h ../GFX/ESLib.h
	gcc -Wall -c deplacement.c -o deplacement.o
	
menu.o: menu.c header.h ../GFX/GfxLib.h ../GFX/BmpLib.h ../GFX/ESLib.h
	gcc -Wall -c menu.c -o menu.o

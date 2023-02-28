exe: main.o sauvegarde.o fantome.o niveau.o deplacement.o ../1/libisentlib.a 
	gcc -Wall main.o sauvegarde.o fantome.o niveau.o deplacement.o -o exe ../1/libisentlib.a -lm -lglut -lGL -lX11
	
main.o: main.c header.h ../1/GfxLib.h ../1/BmpLib.h ../1/ESLib.h 
	gcc -Wall -c main.c -o main.o
	
sauvegarde.o: sauvegarde.c header.h ../1/GfxLib.h ../1/BmpLib.h ../1/ESLib.h
	gcc -Wall -c sauvegarde.c -o sauvegarde.o  
	
fantome.o: fantome.c header.h ../1/GfxLib.h ../1/BmpLib.h ../1/ESLib.h
	gcc -Wall -c fantome.c -o fantome.o 
		
niveau.o: niveau.c header.h ../1/GfxLib.h ../1/BmpLib.h ../1/ESLib.h 
	gcc -Wall -c niveau.c -o niveau.o

deplacement.o: deplacement.c header.h	../1/GfxLib.h ../1/BmpLib.h ../1/ESLib.h
	gcc -Wall -c deplacement.c -o deplacement.o

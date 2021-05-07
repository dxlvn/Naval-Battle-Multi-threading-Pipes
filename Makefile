CFLAGS = -g -c -Wall -I./lib/include -L./lib

run: launch
	./launch testfile

#Edition de lien du programme principal
launch: main.o lire_fichier.o afficher.o gestion_actions.o serveur.o
	gcc -o $@ $^ -g -Wall -I./lib/include -L./lib -lnm

#Compilation du programme principal 
main.o: main.c lire_fichier.h afficher.h gestion_actions.h serveur.h

	gcc ${CFLAGS} $*.c

#Compilations des .o
lire_fichier.o: lire_fichier.c lire_fichier.h

	gcc ${CFLAGS} $*.c 

afficher.o: afficher.c afficher.h

	gcc ${CFLAGS} $*.c

gestion_actions.o: gestion_actions.c gestion_actions.h

	gcc ${CFLAGS} $*.c

serveur.o: serveur.c serveur.h

	gcc ${CFLAGS} $*.c


clean:
	rm -f *.o
	rm -f launch


# compilateur
CC = gcc

# options de compilation
CFLAGS = -Wall -ansi -pedantic -Wextra -g -O2

# options de l'edition des liens
LDFLAGS = -g

# nom de l'executable a  generer
EXEC = agenda

# liste des fichiers objets
OBJ = agenda.o afficher.o bilatere.o insertion.o recherche.o suppression.o ecriture.o motif.o

all : $(EXEC)

# regle de production finale
agenda : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# regle de production pour chaque fichier
agenda.o : agenda.c agenda.h
	$(CC) -c $< $(CFLAGS)

afficher.o : afficher.c agenda.h
	$(CC) -c $< $(CFLAGS)

bilatere.o : bilatere.c agenda.h
	$(CC) -c $< $(CFLAGS)

ecriture.o : ecriture.c agenda.h
	$(CC) -c $< $(CFLAGS)

insertion.o : insertion.c agenda.h
	$(CC) -c $< $(CFLAGS)

recherche.o : recherche.c agenda.h
	$(CC) -c $< $(CFLAGS)

suppression.o : suppression.c agenda.h
	$(CC) -c $< $(CFLAGS)

motif.o : motif.c agenda.h
	$(CC) -c $< $(CFLAGS)	

# regle de suppression des fichiers
clean :
	rm *.o $(EXEC)


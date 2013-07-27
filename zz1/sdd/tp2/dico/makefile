# compilateur
CC = gcc

# options de compilation
CFLAGS = -Wall -ansi -pedantic -Wextra -g

# options de l'edition des liens
LDFLAGS = -g

# nom de l'executable a  generer
EXEC = dico

# liste des fichiers objets
OBJ = main.o lifo.o arbre.o chaine.o

all : $(EXEC)

# regle de production finale
dico : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# regle de production pour chaque fichier
main.o : main.c lifo.h arbre.h chaine.h
	$(CC) -c $< $(CFLAGS)

lifo.o : lifo.c lifo.h arbre.h
	$(CC) -c $< $(CFLAGS)

arbre.o : arbre.c arbre.h lifo.h chaine.h
	$(CC) -c $< $(CFLAGS)

chaine.o : chaine.c chaine.h
	$(CC) -c $< $(CFLAGS)

# regle de suppression des fichiers
clean :
	rm *.o $(EXEC)

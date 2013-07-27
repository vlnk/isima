# compilateur
CC = gcc

# options de compilation
CFLAGS = -Wall -ansi -pedantic -Wextra -g -O2

# options de l'édition des liens
#LDFLAGS = -L/opt/X11/lib -lX11

# nom de l'executable à générer
EXEC = abinaire

# liste des fichiers objets
OBJ = abinaire.o abinaire_txt.o

all : $(EXEC)

# règle de production finale
abinaire : $(OBJ)
	$(CC) $(OBJ) -o $@

# règle de production pour chaque fichier
abinaire_txt.o : abinaire_txt.c abinaire_txt.h
	$(CC) -c $< $(CFLAGS)

abinaire.o : abinaire.c abinaire_txt.h
	$(CC) -c $< $(CFLAGS)

# règle de suppression des fichiers
clean :
	rm $(OBJ)


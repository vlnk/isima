# compilateur
CC = gcc

# options de compilation
CFLAGS = -Wall -ansi -pedantic -Wextra -g -O2

# options de l'édition des liens
LDFLAGS = -L/opt/X11/lib -lX11

# nom de l'executable à générer
EXEC = calculatrice

# liste des fichiers objets
OBJ = calc.o calc_txt.o fonctions.o

all : $(EXEC)

# règle de production finale
calculatrice : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# règle de production pour chaque fichier
fonctions.o : fonctions.c
	$(CC) -c $< $(CFLAGS)

calc_txt.o : calc_txt.c fonctions.h
	$(CC) -c $< $(CFLAGS)

calc.o : calc.c calc_txt.h
	$(CC) -c $< $(CFLAGS)

# règle de suppression des fichiers
clean :
	rm $(OBJ)


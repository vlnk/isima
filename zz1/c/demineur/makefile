# compilateur
CC = gcc

# options de compilation
CFLAGS = -Wall -ansi -pedantic -Wextra -g -O2

# options del'édition des liens
LDFLAGS = -L/opt/X11/lib -lX11

# nom de l'executable à générer
EXEC = demineur

# liste des fichiers objets
OBJ = demineur.o demineur_txt.o

all : $(EXEC)

# règle de production finale
demineur : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# règle de production pour chaque fichier
demineur_txt.o : demineur_txt.c
	$(CC) -c $< $(CFLAGS)

demineur.o : demineur.c demineur.h demineur_txt.h
	$(CC) -c $< $(CFLAGS)

# règle de suppression des fichiers
clean :
	rm $(OBJ)


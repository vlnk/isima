# compilateur
CC = gcc

# options de compilation
CFLAGS = -Wall -ansi -pedantic -Wextra -g -O2

# options del'édition des liens
LDFLAGS = -L/opt/X11/lib -lX11

# nom de l'executable à générer
EXEC = floodit

# liste des fichiers objets
OBJ = floodit.o floodit_txt.o

all : $(EXEC)

# règle de production finale
floodit : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# règle de production pour chaque fichier
floodit_txt.o : floodit_txt.c
	$(CC) -c $< $(CFLAGS)

floodit.o : floodit.c floodit.h floodit_txt.h
	$(CC) -c $< $(CFLAGS)

# règle de suppression des fichiers
clean :
	rm $(OBJ)


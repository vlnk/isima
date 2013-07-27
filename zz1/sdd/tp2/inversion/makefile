# compilateur
CC = gcc

# options de compilation
CFLAGS = -Wall -ansi -pedantic -Wextra -g

# options de l'edition des liens
LDFLAGS = -g

# nom de l'executable a  generer
EXEC = inversion

# liste des fichiers objets
OBJ = main.o lifo.o fifo.o

all : $(EXEC)

# regle de production finale
inversion : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# regle de production pour chaque fichier
main.o : main.c lifo.h fifo.h
	$(CC) -c $< $(CFLAGS)

lifo.o : lifo.c lifo.h fifo.h
	$(CC) -c $< $(CFLAGS)

fifo.o : fifo.c fifo.h lifo.h
	$(CC) -c $< $(CFLAGS)

# regle de suppression des fichiers
clean :
	rm *.o $(EXEC)

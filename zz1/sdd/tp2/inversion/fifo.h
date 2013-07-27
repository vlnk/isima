/* Malrin Vincent
 * Laurent Valentin
 * 4/06/2013
 * FIFO : fifo.h
 */

/*GARDIEN*/
#ifndef FIFO_H
#define FIFO_H

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>

typedef char type_t;

typedef struct fifo
{
    int t_max;
    int in;
    int out;
    type_t * tab;
} fifo_t;

/* FONCTION : enfiler
 * Enfile un element dans la file (fifo_t).
 *
 * entree : le pointeur de la file (fifo_t)
 *          la valeur a inserer (type_t)
 */

int enfiler(fifo_t * f, type_t val);

/* FONCTION : defiler
 * Defile un element dans la file (fifo_t).
 *
 * entree : le pointeur de la file (fifo_t)
 *          la valeur a inserer (type_t)
 */

type_t defiler(fifo_t * f);

/* FONCTION : init_fifo
 * Initialise la file (fifo_t).
 *
 * entree : le pointeur de la file (fifo_t)
 *          la taille maximale (int)
 */

int init_fifo(fifo_t * f, int t_max);

/* FONCTION : est_vide
 * Vérifie si la fifo est vide (fifo_t).
 *
 * entree : le pointeur de la fifo (fifo_t)
 * sortie : le code d'erreur (int)
 */

int fifo_vide(fifo_t * f);

/* FONCTION : est_pleine
 * Vérifie si la fifo est pleine (fifo_t).
 *
 * entree : le pointeur de la fifo (fifo_t)
 * sortie : le code d'erreur (int)
 */

int fifo_pleine(fifo_t* f);

/* FONCTION : free_fifo
 * Libère la fifo (fifo_t).
 *
 * entree : le pointeur de la fifo (fifo_t)
 * sortie : le code d'erreur (int)
 */

void free_fifo(fifo_t* f);

/* FONCTION : afficher_fifo
 * Affiche la fifo (fifo_t).
 *
 * entree : le pointeur de la fifo (fifo_t)
 */

void afficher_fifo(fifo_t * f);

#endif


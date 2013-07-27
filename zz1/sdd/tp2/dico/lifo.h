/* lifo.h
*/

/*GARDIEN*/
#ifndef LIFO_H
#define LIFO_H

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"

typedef abr_t ** type_t;

typedef struct lifo
{
    int t_max;
    int taille;
    type_t * tab;
} lifo_t;

/* FONCTION : empiler
 * Empile un element dans la lifo (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 *          la valeur a inserer (type_t *)
 * sortie : le code d'erreur (int)
 */
int empiler(lifo_t * p, type_t val);

/* FONCTION : depiler
 * Depile un element dans la lifo (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 *          la valeur a inserer (type_t *)
 * sortie : le code d'erreur (int)
 */
type_t depiler(lifo_t * p);

/* FONCTION : init_lifo
 * Initialise la lifo (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 *          la taille maximale (int)
 * sortie : le code d'erreur (int)
*/
int init_lifo(lifo_t * p, int t_max);

/* FONCTION : est_vide
 * Vérifie si la lifo est vide (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 * sortie : le code d'erreur (int)
*/
int lifo_vide(lifo_t* p);

/* FONCTION : est_pleine
 * Vérifie si la lifo est pleine (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 * sortie : le code d'erreur (int)
*/
int lifo_pleine(lifo_t* p);

/* FONCTION : free_lifo
 * Libère la lifo (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 * sortie : le code d'erreur (int)
*/
void free_lifo(lifo_t* p);

/* FONCTION : afficher_lifo
 * Affiche la pile.
 *
 * entree : le pointeur de la lifo (lifo_t)
 */

void afficher_lifo(lifo_t * p);

/*FONCTION : inversion_pile
 * Porte bien son nom.
 *
 * entree : le pointeur de la pile (lifo_t).
 */

void inversion_pile(lifo_t * p);
#endif

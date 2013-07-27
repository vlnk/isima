/* Malrin Vincent
 * Laurent Valentin
 * 4/06/2013
 * ARBRE : arbre.h
 */

/*GARDIEN*/
#ifndef ARBRE_H
#define ARBRE_H

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"
#include "string.h"

typedef struct abr
{
    char            val;
    struct abr *    fils;
    struct abr *    frere;
} abr_t;

/* FONCTION : construction
 * Construit un noeud à partir de sa valeur (noeud_t).
 *
 * entree : la valeur (char)
 * sortie : le code erreur (int)
 */

int construction(char val, abr_t ** n);

/* FONCTION : lecture_abr
 * Lit la chaine de caractere (ecriture parenthesee) et construit l'arbre.
 *
 * entree : chaine de caractere (char *)
 *          le pointeur sur l'arbre (noeud_t *)
 * sortie : erreur (int).
 */

int lecture_abr(char * ch, abr_t ** r);

/* FONCTION : liberation_abr
 * Libere les ressources.
 *
 * entree : la racine (abr_t ** r)
 * sortie : erreur (int)
 */

int liberation_abr(abr_t ** r);

/* FONCTION : affichage_abr
 * Affiche les mots contenus dans l'arbre.
 *
 * entree : la racine (abr_t ** r)
 * sortie : erreur (int)
 */

int affichage_abr(abr_t ** r);

/* FONCTION : insertion_abr
 * Insère une chaine de caractères dans l'arbre trié.
 *
 * entrée : la racine (abr_t ** r)
 *          la chaine a inserer (char * ch)
 * sortie : erreur (int)
 */

int insertion_abr(abr_t ** r, char * ch);

#endif

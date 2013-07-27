/* Malrin Vincent
 * Laurent Valentin
 * 4/06/2013
 * CHAINE : chaine.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"
#include "string.h"

/* FONCTION : verif_chaine
 * Verifie si la chaine est une notation parenthesee.
 *
 * entree : la chaine (char *)
 * sortie : le code erreur (int)
 */

int verif_chaine(char * ch);

/* FONCTION : verif_argument
 * Verifie si la chaine est un mot.
 *
 * entree : la chaine (char *)
 * sortie : le code erreur (int)
 */

int verif_argument(char * ch);

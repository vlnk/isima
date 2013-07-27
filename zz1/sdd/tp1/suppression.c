/* Malrin Vincent
 * Laurent Valentin
 * 25/03/2013
 * SUPPRESSION : suppression.c
 */

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"


/* FONCTION : SuppressionAct
 * Suppression de la semaine dans la liste chainée.
 *
 * entree : l'adresse de la structure à supprimer (action_t ** prec)
 * varloc : le pointeur temporaire (action_t * tmp)
 */

void SuppressionAct(action_t ** prec)
{
    /*variables locales*/
    action_t *          tmp = *prec;

    /*le pointeur à supprimer est NULL*/
    if (*prec == NULL)
    {
        printf("Erreur\n");
    }
    else
    {
        *prec = ((**prec).suiv);
        free(tmp);
    }
}

/* FONCTION : SuppressionSem
 * Suppression de la semaine dans la liste chainée.
 *
 * entree : l'adresse de la structure à supprimer (semaine_t ** prec)
 * varloc : le pointeur temporaire (semaine_t * tmp)
 */

void SuppressionSem(semaine_t ** prec)
{
    /*variables locales*/
    semaine_t *         tmp = *prec;

    /*le pointeur à supprimer est NULL*/
    if (*prec == NULL)
    {
        printf("Erreur\n");
    }
    else
    {
        *prec = (**prec).suiv;
        free(tmp);
    }
}


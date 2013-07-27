/* Malrin Vincent
 * Laurent Valentin
 * 25/03/2013
 * INSERTION : insertion.c
 */

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

/* FONCTION : InsererSem
 * Insertion d'une nouvelle semaine dans la liste chainee.
 *
 * entree : le pointeur de recherche (semaine_t ** prec)
 *          les informations à inserer (char * chaine_sem)
 * varloc : le nouveau pointeur à inserer (semaine_t * new)
 * sortie : le nouveau pointeur (semaine_t * new)
 */

semaine_t * InsererSem(semaine_t ** prec, char * chaine_sem)
{
    /*variales locales*/
    semaine_t *         new = (semaine_t *) malloc (sizeof(semaine_t));

    if(new)
    {
        /*copie des informations*/
        strcpy((*new).chaine_sem,chaine_sem);
        (*new).action_s = NULL;
        (*new).suiv = NULL;

        /*insertion du pointeur new*/
        (*new).suiv = *prec;
        *prec = new;
    }
    return new;
}

/* FONCTION : InsererAct
 * Insertion d'une nouvelle action dans la liste chainee.
 *
 * entree : le pointeur de recherche (action_t ** prec)
 *          les informations à inserer (char * chaine_act)
 * varloc : le nouveau pointeur à inserer (action_t * new)
 * sortie : le nouveau pointeur (action_t * new)
 */

action_t * InsererAct(action_t ** prec, char * chaine_act)
{
    /*variales locales*/
    action_t *          new = (action_t *) malloc (sizeof(action_t));

    if(new)
    {
        /*copie des informations*/
        strcpy((*new).chaine_act,chaine_act);

        /*insertion du pointeur new*/
        (*new).suiv = *prec;
        *prec = new;
    }
    return new;
}

/* FONCTION : Liberation
 * Libere toute les données allouees.
 *
 * entree : le pointeur de debut de la liste chainee (semaine_t * p_sem)
 * varloc : les pointeurs courants (action_t * cour_act et semaine_t * cour_sem)
 *          les pointeurs temporaires (action_t * tmp_act et semaine_t * tmp_sem)
 * sortie : rien
 */

void Liberation(semaine_t * p_sem)
{
    /*variables locales*/
    semaine_t *         cour_sem = p_sem;
    action_t *          cour_act;
    action_t *          tmp_act;
    semaine_t *         tmp_sem;

    /*parcours*/
    while (cour_sem)
    {

        /*on initialise le pointeur d'action*/
        cour_act = (*cour_sem).action_s;

        while (cour_act)
        {
            tmp_act = cour_act;

            /*on avance les pointeurs de action_t*/
            cour_act = (*cour_act).suiv;

            /*libération de la structure action_t*/
            free(tmp_act);
        }

        tmp_sem = cour_sem;

        /*on avance le pointeur de semaine_t*/
        cour_sem = (*cour_sem).suiv;

        /*libération de la structure semaine_t*/
        free(tmp_sem);

    }

    p_sem = NULL;
}

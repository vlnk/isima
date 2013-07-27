/* Malrin Vincent
 * Laurent Valentin
 * 25/03/2013
 * BILATERE : bilatere.c
 */

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

/* FONCTION : Transformation
 * Transforme la liste des semaines en liste bilatère.
 *
 * entrée : le pointeur de debut de la liste chainée (semaine_t * p_sem)
 *          le pointeur de debut de la liste bilatère (semaine_t * p_bil)
 * varloc : le pointeurs precedents (semaine_t ** prec, bilatere_t ** prec_bil)
 *          le pointeur courant de la liste bilatère (bilatere_t * nouv)
 * sortie : le pointeur de debut de la liste bilatère (semaine_t * p_bil)
 */

bilatere_t * TransfoBilatere (semaine_t ** p_sem, bilatere_t * p_bil)
{
    /*variables locales*/
    semaine_t **        prec = p_sem;
    bilatere_t **       prec_bil = &p_bil;
    bilatere_t *        nouv = NULL;

    /*boucle*/
    while (*prec)
    {
        nouv = (bilatere_t *) calloc (1,sizeof(bilatere_t)); /*création de la cellule bilatère*/

        strcpy((*nouv).chaine_sem,(**prec).chaine_sem); /*copie des données*/
        (*nouv).action_s = (**prec).action_s;

        prec_bil = InsertionBil(prec_bil,nouv); /*insertion*/

        prec = &(**prec).suiv; /*avance les prec*/
    }
    return p_bil;
}

/* FONCTION : InsertionBil
 * Insère une celulle .
 *
 * entrée : l'adresse du pointeur où il faut inserer (bilatere_t ** b)
 *          le pointeur de la cellule à inserer (bilatere_t * elt)
 * sortie : l'adresse de l'élement inséré (semaine_t ** adr_bil)
 */

bilatere_t ** InsertionBil(bilatere_t ** b, bilatere_t * elt)
{
    /*insertion*/
    elt->suiv = (**b).suiv;
    elt->prec = *b;
    (*b)->suiv->prec = elt;
    (*b)->suiv = elt;

    return &(**b).suiv;
}

/* FONCTION : LiberationBil
 * Libere toute les données allouées dans la structure bilatere.
 *
 * entree : le pointeur de debut de la liste bilatere (bilatere_t * p_bil)
 * varloc : les pointeurs courants (action_t * cour_act et bilatere_t * cour_bil)
 *          les pointeurs temporaires (action_t * tmp_act et bilatere_t * tmp_bil)
 * sortie : rien
 */

void LiberationBil(bilatere_t * p_bil)
{
    /*variables locales*/
    bilatere_t *        cour_bil = (*p_bil).suiv;
    bilatere_t *        tmp_bil = NULL;
    int                 verif = 0;

    /*parcours*/
    while ((cour_bil != NULL) && ((*cour_bil).action_s != NULL))
    {

        /* ATTENTION : les pointeurs (action_t *) ne sont pas libérés !
         * Ils seront libérés dans la fonction Liberation.
         */

        tmp_bil = cour_bil;

        /*on avance le pointeur de semaine_t*/
        cour_bil = (*cour_bil).suiv;

        /*libération de la structure semaine_t*/
        (*tmp_bil).action_s = NULL;
        (*tmp_bil).prec = NULL;
        (*tmp_bil).suiv = NULL;
        free(tmp_bil);

    }
    (*p_bil).suiv = NULL;
    (*p_bil).prec = NULL;
}

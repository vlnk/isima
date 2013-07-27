/* Malrin Vincent
 * Laurent Valentin
 * 25/03/2013
 * RECHERCHE : recherche.c
 */

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

/* FONCTION : RechercheSem
 * Recherche de la semaine dans la liste chainee.
 *
 * entree : le pointeur de debut de la liste chainee (semaine_t ** p_sem)
 *          les informations de à rechercher (char * chaine_sem)
 * varloc : le pointeur precedent (semaine_t ** prec)
 *          le pointeur courant (semaine_t * cour)
 * sortie : le pointeur correspondant à la recherche (semaine_t ** prec)
 */

semaine_t ** RechercheSem(semaine_t ** p_sem, char * chaine_sem)
{
    /*variables locales*/
    char                annee[5];
    char                cour_annee[5];
    char                semaine[3];
    char                cour_semaine[3];
    semaine_t **        prec = p_sem;
    semaine_t *         cour = *p_sem;

    if (cour != NULL) /*si la liste des semaines est nulle*/
    {
        /*initialisation des chaines*/
        sscanf(chaine_sem,"%4c%2c",annee,semaine);
        sscanf(cour->chaine_sem,"%4c%2c",cour_annee,cour_semaine);
        annee[4] = '\0';
        cour_annee[4] = '\0';
        semaine[2] = '\0';
        cour_semaine[2] = '\0';
    }

    /*parcours*/
    while ((cour != NULL) && ((strcmp(cour_annee,annee) < 0) || ((strcmp(cour_annee,annee) == 0) && (strcmp(cour_semaine,semaine) < 0))))
    {
        /*on avance les pointeurs*/
        prec = &(*cour).suiv;
        cour = (*cour).suiv;

        /*si le pointeur suivant est vide, la copie est impossible*/
        if (cour != NULL)
        {
            sscanf(cour->chaine_sem,"%4c%2c",cour_annee,cour_semaine);
        }
    }
    if ((cour != NULL) && ((strcmp(cour_annee,annee) > 0) || (strcmp(cour_semaine,semaine) > 0)))
    {
        *prec = NULL; /*la date est anterieure aux dates de listes*/
    }

    return prec;
}

/* FONCTION : RechercheAct
 * Recherche de l'action dans la liste chainee.
 *
 * entree : le pointeur de debut de la liste chainée (action_t ** p_act)
 *          les informations de à rechercher (char * chaine_act)
 * varloc : le pointeur precedent (action_t ** prec)
 *          le pointeur courant (action_t * cour)
 * sortie : le pointeur correspondant à la recherche (action_t ** prec)
*/

action_t ** RechercheAct(action_t ** p_act, char * chaine_act)
{
    /*variables locales*/
    char                jour[2];
    char                cour_jour[2];
    char                heure[3];
    char                cour_heure[3];
    action_t **         prec = p_act;
    action_t *          cour = *p_act;

    if (cour != NULL) /*si la liste des actions est nulle*/
    {
        /*initialisation des chaines*/
        sscanf(chaine_act,"%1c%2c",jour,heure);
        sscanf(cour->chaine_act,"%1c%2c",cour_jour,cour_heure);
        jour[1] = '\0';
        cour_jour[1] = '\0';
        heure[2] = '\0';
        cour_heure[2] = '\0';
    }

    /*parcours*/
    while ((cour != NULL) && ((strcmp(cour_jour,jour) < 0) || ((strcmp(cour_jour,jour) == 0) && (strcmp(cour_heure,heure) < 0))))
    {
        /*on avance les pointeurs*/
        prec = &(*cour).suiv;
        cour = (*cour).suiv;

        /*si le pointeur suivant est vide, la copie est impossible*/
        if (cour != NULL)
        {
            sscanf(cour->chaine_act,"%1c%2c",cour_jour,cour_heure);
        }
    }

    if ((cour != NULL) && ((strcmp(cour_jour,jour) > 0) || (strcmp(cour_heure,heure) > 0)))
    {
        *prec = NULL; /*la date est anterieure aux dates de listes*/
    }
    return prec;
}

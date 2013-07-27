/* Malrin Vincent
 * Laurent Valentin
 * 25/03/2013
 * RECHERCHE DE MOTIF : motif.c
 */

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

/* FONCTION : RechercheMotif
 * Crée une liste contigue des jours ou une action contenant un motif donné est présente.
 *
 * entrée : pointeur sur la liste chainée des semaines (semaine_t * p_sem).
 *          pointeur sur la liste contigue des jours (motif_t * p_motif).
 *          chaine du motif à rechercher (char * motif_rech).
 * varloc : les pointeurs courants (semaine_t * cour_sem, action_t * cour_act).
 *          compteur de la liste contigue (int compteur).
 *          chaine de copie (char chaine_motif[10], char libelle[11], char dechet[TMAX]).
 * sortie : l'adresse de la dernière cellule de recherche.
 */

int RechercheMotif(semaine_t * p_sem, motif_t * p_motif, char * motif_rech)
{
    /*variables locales*/
    semaine_t *         cour_sem = p_sem;
    action_t *          cour_act = (*cour_sem).action_s; /*on initialise le pointeur d'action*/
    int                 compteur = 0;

    char                dechet[TMAX];
    char                libelle[11];

    /*compteur*/
    while (cour_sem)
    {
        /*initialisation des chaines*/
        libelle[11] = '\0';

        /*on initialise le pointeur d'action*/
        cour_act = (*cour_sem).action_s;

        while (cour_act)
        {
            sscanf(cour_act->chaine_act,"%3c%10c",dechet,libelle);
            if (strstr(libelle,motif_rech) != NULL)
            {
                /*copie de la date du motif*/
                strcpy(p_motif[compteur].motif,cour_sem->chaine_sem);
                strncat(p_motif[compteur].motif,cour_act->chaine_act,3);
                p_motif[compteur].motif[10] = '\0';
                compteur++;
            }

            /*on avance les pointeurs de action_t*/
            cour_act = (*cour_act).suiv;
        }

        /*on avance le pointeur de semaine_t*/
        cour_sem = (*cour_sem).suiv;
    }
    return compteur;
}

/* FONCTION : AffichageMotif
 * Crée une liste contigue
 *
 * entrée : pointeur sur la liste chainée des semaines (semaine_t * p_sem).
 *          pointeur sur la liste contigue des jours (motif_t * p_motif).
 *          le nombre de cellules complètes (int compteur).
 * varloc : les pointeurs courants (semaine_t * cour_sem, action_t * cour_act).
 *          compteur de la liste contigue (int compteur).
 *          chaine de copie (char chaine_motif[10], char libelle[11], char dechet[TMAX]).
 * sortie : l'adresse de la dernière cellule de recherche.
 */

void AffichageMotif(motif_t * p_motif, int compteur)
{
    /*variables locales*/
    int                 compteur_aff = 0;

    if (compteur == 0) /*cas d'une liste vide*/
    {
        printf("Aucune date correspondante\n");
    }
    else
    {
        /*parcours*/
        while (compteur_aff < compteur)
        {
            printf("%s\n",p_motif[compteur_aff].motif);
            compteur_aff++;
        }
    }
}



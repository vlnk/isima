/* Malrin Vincent
 * Laurent Valentin
 * 25/03/2013
 * ECRITURE : ecriture.c
 */

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

/* FONCTION : Ecriture
 * Ecriture de la liste dans un fichier texte.
 *
 * entree : le pointeur de debut de liste (semaine_t * p_sem)
 *          le nom du fichier à ouvrir (char * nom)
 * varloc : le nouveau pointeur à inserer (semaine_t * new)
 * sortie : code erreur fourni en parametre de sortie (int code)
 */

int Ecriture(semaine_t * p_sem, char * nom)
{
    /*variables locales*/
    FILE *              f_ecriture = fopen(nom, "w");
    semaine_t *         cour_sem = p_sem;
    action_t *          cour_act;
    char                chaine_sem[7];
    char                chaine_act[3 + TLIBELLE + 1];
    int                 code = 0;

    /*parcours*/
    if (!f_ecriture)
    {
        printf("Ecriture impossible !");
        code = 1;
    }
    else
    {
        while (cour_sem)
        {
            /*initialisation des chaines*/
            chaine_sem[6] = '\0';
            chaine_act[TACT] = '\0';

            /*on initialise le pointeur d'action*/
            cour_act = (*cour_sem).action_s;

            /*mise à jour des informations à afficher*/
            /*annee,semaine*/
            strcpy(chaine_sem,cour_sem->chaine_sem);

            while (cour_act)
            {
                 /*jour,heure,libelle*/
                strcpy(chaine_act,cour_act->chaine_act);

                /*affichage des informations*/
                fputs(chaine_sem,f_ecriture);
                fputs(chaine_act,f_ecriture);
                fputc('\n',f_ecriture);

                /*on avance les pointeurs de action_t*/
                cour_act = (*cour_act).suiv;
            }

            /*on avance le pointeur de semaine_t*/
            cour_sem = (*cour_sem).suiv;
        }

        /*fermeture du fichier d'ecriture*/
        fclose(f_ecriture);
    }

    return code;
}

/* FONCTION : Lecture
 * Lecture dans un fichier texte et creation de la liste.
 *
 * entree : le pointeur de la structure (semaine_t ** p_sem)
 *          le nom du fichier à ouvrir (char * nom_f)
 * varloc : pointeurs de parcours, les informations à copier
 * sortie : code erreur fourni en parametre de sortie (int erreur)
 */

int Lecture(semaine_t ** p_sem, char * nom_f)
{
    /*variable locales*/
    FILE *              f_lecture = fopen(nom_f, "r");
    int                 taille = TMAX + 10;
    char *              ligne = (char *) calloc(1,sizeof(char)*taille);

    semaine_t *         new_sem = NULL; /*pointeurs de parcours des listes*/
    semaine_t **        prec_sem = NULL;
    action_t *          new_act = NULL;
    action_t **         prec_act = NULL;

    int                 erreur = 0;

    char                chaine_sem[7]; /*copies des informations*/
    char                chaine_act[TACT + 1];
    char                dechet[100];

    if (f_lecture && ligne)
    {
        /*initialisation*/
        prec_sem = p_sem;

        /*creation de la structure*/
        while ((fgets(ligne,taille,f_lecture) != NULL))
        {
            sscanf(ligne,"%6c%13c%100c",chaine_sem,chaine_act,dechet);

            /*initialisation des chaines*/
            chaine_sem[6] = '\0';
            chaine_act[strlen(chaine_act)] = '\0';

            if ((*p_sem == NULL) || (strcmp(new_sem->chaine_sem,chaine_sem) != 0))
            {
                /*insertion de semaine_t*/
                new_sem = InsererSem(prec_sem,chaine_sem);
                prec_sem = &((*new_sem).suiv);
                prec_act = &((*new_sem).action_s);

                /*insertion de action_t*/
                new_act = InsererAct(prec_act,chaine_act);
                prec_act = &((*new_act).suiv);
            }
            else
            {
                /*insertion de action_t*/
                new_act = InsererAct(prec_act,chaine_act);
                prec_act = &((*new_act).suiv);

            }
        }

        fclose(f_lecture);
        free(ligne);
    }
    else
    {
        printf("Ouverture du fichier de lecture impossible !\n");
        erreur = 1;
    }

    return erreur;
}


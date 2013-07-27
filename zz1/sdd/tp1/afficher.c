/* Malrin Vincent
 * Laurent Valentin
 * 25/03/2013
 * AFFICHAGE : afficher.c
 */

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

/* FONCTION : Affichage
 * Affiche les informations des listes chainées (semaine_t).
 *
 * entree : le pointeur de debut de la liste chainée (semaine_t * p_sem)
 * varloc : les pointeurs courants (action_t * cour_act et semaine_t * cour_sem)
 *          les informations à afficher (char)
 * sortie : rien
 */

void Affichage(semaine_t * p_sem)
{
    /*variables locales*/
    semaine_t *         cour_sem = p_sem;
    action_t *          cour_act;
    char                annee[5];
    char                semaine[3];
    char                jour[2];
    char                heure[3];
    char                libelle[11];

    /*parcours*/
    while (cour_sem)
    {
        /*initialisation des chaines*/
        jour[1] = '\0';
        annee[4] = '\0';
        semaine[2] = '\0';
        heure[2] = '\0';
        libelle[10] = '\0';


        /*on initialise le pointeur d'action*/
        cour_act = (*cour_sem).action_s;

        /*mise à jour des informations à afficher*/
        /*chaine_sem,semaine*/
        sscanf(cour_sem->chaine_sem,"%4c%2c",annee,semaine);

        while (cour_act)
        {
            /*jour,heure,libelle*/
            sscanf(cour_act->chaine_act,"%1c%2c%10c",jour,heure,libelle);

            /*affichage des informations*/
            printf("ANNEE : %s\n",annee);
            printf("SEMAINE : %s\n",semaine);
            printf("JOUR : %s\n",jour);
            printf("HEURE : %s\n",heure);
            printf("LIBELLE : %s\n",libelle);
            printf("\n");

            /*on avance les pointeurs de action_t*/
            cour_act = (*cour_act).suiv;
        }

        /*on avance le pointeur de semaine_t*/
        cour_sem = (*cour_sem).suiv;
    }

    printf("--------------------------------------------\n");
}


/* FONCTION : Menu
 * Affichage du menu.
 * entree : code de saisie (int saisie)
 *          le ponteur vers le choix (int * choix)
 * sortie : rien
 */

void Menu(int saisie, int * choix)
{
    /*saisie controle activation du scanf*/
    printf("\n<choix menu> :\n");
    printf("0) Quitter\n");
    printf("1) Affichage\n");
    printf("2) Recherche par date\n");
    printf("3) Suppression\n");
    printf("4) Ecriture\n");
    printf("5) Transformation en liste bilatere\n");
    printf("6) Recherche de motifs\n");

    printf("\n<argument> :\n<menu 1,2> -> date\n<menu 5> -> fichier d'ecriture\n<menu 6> -> motif\n");

    if (saisie == 1)
    {
        printf("Veuillez choisir votre choix ? ");
        fflush(stdout);
        scanf("%d%*c",choix);
        printf("\n");
    }
}

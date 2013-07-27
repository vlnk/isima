/* TITRE : TP7
 * FICHIER : tp71.c
 *
 * Question 1) de la PREMIERE PARTIE -> Saisie et affichage.
 *
 * AUTEUR : Valentin Laurent
 * DATE : 9/12/12
 */

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DEFINE */
#define TMAX 100

typedef struct cellule
{
    char            * ligne;
    struct cellule  * suiv;
} cellule_t;

void saisie(cellule_t ** ftete);
void affiche(cellule_t * ptete);
void liberation(cellule_t ** ptete);
void ajout(cellule_t ** ftete);

/* PROGRAMME PRINCIPALE
 *
 * Lit la saisie utilisateur en copiant le texte ligne par ligne dans une liste chainée, puis affiche le texte.
 *
 * ENTRÉE : Rien.
 * SORTIE : Rien.
 */

int main(int argc, char ** argv)
{
    /*VARIABLES LOCALES*/
    cellule_t *         ptete;
    cellule_t *         ftete;

    /*Allocation de la liste*/
    ptete = (cellule_t *) malloc(sizeof(cellule_t));
    (*ptete).suiv = NULL;

    if (ptete == NULL)
    {
        printf("Allocation impossible");
    }
    else
    {
        /*initialisation du pointeur de fin de liste*/
        ftete = ptete;

        while(!feof(stdin))
        {
            saisie(&ftete);
            ajout(&ftete);
        }

        affiche(ptete);
    }
    liberation(&ptete);

    return 0;
}

/* SOUS PROGRAMMES */

/* FONCTION : (void) saisie
 *
 * Lecture de la saisie utilisateur (arrêt : ctrl+D) et copie des lignes dans une cellule de la liste chainée.
 *
 * ENTRÉE : (cellule_t **) ftete : un pointeur de pointeur sur la dernière cellule (vide) de la liste chainée.
 * SORTIE : Rien.
 */

void saisie(cellule_t ** ftete)
{
    /*VARIABLES LOCALES*/
    char            temp[TMAX];

    fgets(temp,TMAX,stdin);

    (**ftete).ligne = (char *) malloc(sizeof(char)*TMAX + 1);
    strcpy((**ftete).ligne,temp);
}

/* FONCTION : (void) ajout
 *
 * Ajout d'une cellule (struct) initialisée (à NULL) en fin de la liste chainée.
 *
 * ENTRÉE : (cellule_t **) ftete : un pointeur de pointeur sur la dernière cellule de la liste chainée.
 * SORTIE : Rien.
 */


void ajout(cellule_t ** ftete)
{
    (**ftete).suiv = (cellule_t *) malloc(sizeof(cellule_t));
    *ftete = (**ftete).suiv;
    (**ftete).ligne = NULL;
    (**ftete).suiv = NULL;
}

/* FONCTION : (void) affiche
 *
 * Affichage des cellules de la liste chainée.
 *
 * ENTRÉE : (cellule_t *) ftete : un pointeur sur la dernière cellule (vide) de la liste chainée.
 * SORTIE : Rien.
 */


void affiche(cellule_t * ptete)
{
    /*VARIABLES LOCALES*/
    cellule_t *        cour = ptete;

    printf("\n\n --AFFICHAGE-- \n");
    while((*cour).suiv != NULL)
    {
        printf("%s",(*cour).ligne);
        (cour) = (*cour).suiv;
    }
    printf("\n");
}

/* FONCTION : (void) liberation
 *
 * Libération de la mémoire allouée pour la création de la liste chainée.
 *
 * ENTRÉE : (cellule_t **) ftete : un pointeur de pointeur sur la première cellule de la liste chainée.
 * SORTIE : Rien.
 */

void liberation(cellule_t ** ptete)
{
    /*variales locales*/
    cellule_t * cour;
    cour = *ptete;

    /*parcours de la liste chainée*/
    while ((cour) != NULL)
    {
        *ptete = (*cour).suiv;

        /*libération de l'élément visité*/
        free(cour);
        cour = *ptete;
    }

    free(*ptete);
}

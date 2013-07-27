/* TITRE : TP7
 * FICHIER : tp72.c
 *
 * Question 2) de la PREMIERE PARTIE -> Lecture et affichage.
 *
 * AUTEUR : Valentin Laurent
 * DATE : 9/12/12
 */

/* INCLUDE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DEFINE */
#define TMAX 1000

/* STRUCTURE */
typedef struct cellule
{
    char            * ligne;
    struct cellule  * suiv;
} cellule_t;

/* PROTOTYPES */
void lecture(cellule_t ** ftete, cellule_t * ptete);
void affiche(cellule_t * ptete);
void liberation(cellule_t ** ptete);
void ajout(cellule_t ** ftete);

/* PROGRAMME PRINCIPALE
 *
 * Lit un fichier texte en copiant le texte ligne par ligne dans une liste chainée, puis affiche le texte.
 *
 * ENTRÉE : Rien.
 * SORTIE : Rien.
 */

int main(int argc, char ** argv)
{
    /* VARIABLES LOCALES */
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

        /*lecture du fichier texte et modification de la liste chainée*/
        lecture(&ftete, ptete);

        /*affichage du texte à partir de la liste chainée*/
        affiche(ptete);
    }
    liberation(&ptete);

    return 0;
}

/* SOUS PROGRAMMES */

/* FONCTION : (void) lecture
 *
 * Lecture du fichier et copie des lignes dans une cellule de la liste chainée.
 *
 * ENTRÉE : (cellule_t **) ftete : un pointeur de pointeur sur la dernière cellule (vide) de la liste chainée.
 * SORTIE : Rien.
 */

void lecture(cellule_t ** ftete, cellule_t * ptete)
{
    /*VARIABLES LOCALES*/
    char            temp[TMAX];
    FILE *          fic_lecture;

    /*saisie du nom du fichier (chemin complet)*/
    printf("Veuillez saisir le nom du fichier : ");
    fflush(stdout);
    scanf("%s%*c",temp);

    /*En tête du fichier*/
    (*ptete).ligne = (char *) malloc(sizeof(char)*strlen(temp) + 1);
    strcpy((*ptete).ligne,temp);

    /*ouverture du fichier*/
    fic_lecture = fopen(temp,"r+");

    /*ouverture incorrecte*/
    if(fic_lecture == NULL)
    {
        printf("Problème d'ouverture");
    }
    /*ouverture réussie*/
    else
    {
        /*lecture du fichier texte*/
        while(!feof(fic_lecture))
        {
            fgets(temp,TMAX,fic_lecture);

            /*création de la cellule*/
            ajout(ftete);

            /*copie du texte dans la liste chainée*/
            (**ftete).ligne = (char *) malloc(sizeof(char)*strlen(temp) + 1);
            strcpy((**ftete).ligne,temp);
        }
    }
    fclose(fic_lecture);
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
    cellule_t *        cour = (*ptete).suiv;

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

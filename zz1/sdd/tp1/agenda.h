/* Malrin Vincent
 * Laurent Valentin
 * 25/03/2013
 * EN TETE : agenda.h
 */

/*GARDIEN*/
#ifndef AGENDA_H
#define AGENDA_H

/*DEFINE*/
#define TLIBELLE 10
#define TACT (TLIBELLE + 3)
#define TMAX 100

/* INCLUDE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*STRUCTURES*/
typedef struct struct2
{
    char                chaine_act[3 + TLIBELLE + 1];
    struct struct2 *    suiv;
} action_t;

typedef struct struct1
{
    char                chaine_sem[7];
    action_t *          action_s;
    struct struct1 *    suiv;
} semaine_t;

typedef struct struct3
{
    char                motif[13];
} motif_t;

typedef struct struct4
{
    char                chaine_sem[7];
    action_t *          action_s;
    struct struct4 *    prec;
    struct struct4 *    suiv;
} bilatere_t;

/*----------------------------------------------------*/
/*             INSERTION (insertion.c)                */
/*----------------------------------------------------*/


/* FONCTION : InsererSem
 * Insertion d'une nouvelle semaine dans la liste chainee.
 *
 * entree : le pointeur de recherche (semaine_t ** prec)
 *          les informations à inserer (char * chaine_sem)
 * varloc : le nouveau pointeur à inserer (semaine_t * new)
 * sortie : le nouveau pointeur (semaine_t * new)
 */

semaine_t * InsererSem(semaine_t ** prec, char * chaine_sem);

/* FONCTION : InsererAct
 * Insertion d'une nouvelle action dans la liste chainee.
 *
 * entree : le pointeur de recherche (action_t ** prec)
 *          les informations à inserer (char * chaine_act)
 * varloc : le nouveau pointeur à inserer (action_t * new)
 * sortie : le nouveau pointeur (action_t * new)
 */

action_t * InsererAct(action_t ** prec, char * chaine_act);

/* FONCTION : Liberation
 * Libere toute les données allouees.
 *
 * entree : le pointeur de debut de la liste chainee (semaine_t * p_sem)
 * varloc : les pointeurs courants (action_t * cour_act et semaine_t * cour_sem)
 *          les pointeurs temporaires (action_t * tmp_act et semaine_t * tmp_sem)
 * sortie : rien
 */

void Liberation(semaine_t * p_sem);

/*----------------------------------------------------*/
/*             RECHERCHE (recherche.c)                */
/*----------------------------------------------------*/

/* FONCTION : RechercheSem
 * Recherche de la semaine dans la liste chainee.
 *
 * entree : le pointeur de debut de la liste chainee (semaine_t ** p_sem)
 *          les informations de à rechercher (char * chaine_sem)
 * varloc : le pointeur precedent (semaine_t ** prec)
 *          le pointeur courant (semaine_t * cour)
 * sortie : le pointeur correspondant à la recherche (semaine_t ** prec)
 */

semaine_t ** RechercheSem(semaine_t ** p_sem, char * chaine_sem);

/* FONCTION : RechercheAct
 * Recherche de l'action dans la liste chainee.
 *
 * entree : le pointeur de debut de la liste chainée (action_t ** p_act)
 *          les informations de à rechercher (char * chaine_act)
 * varloc : le pointeur precedent (action_t ** prec)
 *          le pointeur courant (action_t * cour)
 * sortie : le pointeur correspondant à la recherche (action_t ** prec)
 */

action_t ** RechercheAct(action_t ** p_act, char * chaine_act);

/*----------------------------------------------------*/
/*            SUPPRESSION (suppression.c)             */
/*----------------------------------------------------*/

/* FONCTION : SuppressionAct
 * Suppression de l'action dans la liste chainée.
 *
 * entree : le pointeur de debut de la liste chainee (action_t ** p_act)
 *          les informations à rechercher (char * jour)
 * varloc : le pointeur precedent (action_t ** prec)
 *          le pointeur courant (action_t * cour)
 */

void SuppressionAct(action_t ** prec);

/* FONCTION : SuppressionSem
 * Suppression de la semaine dans la liste chainee.
 *
 * entree : le pointeur de debut de la liste chaiee (semaine_t ** p_sem)
 *          les informations à rechercher (char * jour)
 * varloc : le pointeur precedent (semaine_t ** prec)
 *          le pointeur courant (semaine_t * cour)
 */

void SuppressionSem(semaine_t ** p_sem);

/*----------------------------------------------------*/
/*                AFFICHER (afficher.c)               */
/*----------------------------------------------------*/

/* FONCTION : Affichage
 * Affiche les informations des listes chainees (semaine_t).
 *
 * entree : le pointeur de debut de la liste chainee (semaine_t * p_sem)
 * varloc : le pointeur courant (action_t * cour)
 * sortie : rien
 */

void Affichage(semaine_t * p_sem);

/* FONCTION : Menu
 * Affichage du menu.
 * entree : code de saisie (int saisie)
 *          le ponteur vers le choix (int * choix)
 * sortie : rien
 */

void Menu(int saisie, int * choix);

/*----------------------------------------------------*/
/*                BILATERE (bilatere.c)               */
/*----------------------------------------------------*/

/* FONCTION : Transformation
 * Transforme la liste des semaines en liste bilatere.
 *
 * entree : le pointeur de debut de la liste chainee (semaine_t ** p_sem)
 *          le pointeur de debut de la liste bilatere (semaine_t * p_bil)
 * varloc : le pointeurs precedents (semaine_t ** prec, bilatere_t ** prec_bil)
 *          le pointeur courant de la liste bilatere (bilatere_t * nouv)
 * sortie : le pointeur de debut de la liste bilatere (semaine_t * p_bil)
 */

bilatere_t * TransfoBilatere (semaine_t ** p_sem, bilatere_t * p_bil);

/* FONCTION : InsertionBil
 * Insère une celulle.
 *
 * entree : l'adresse du pointeur où il faut inserer (bilatere_t ** b)
 *          le pointeur de la cellule à inserer (bilatere_t * elt)
 * sortie : l'adresse de l'élement inséré (semaine_t ** adr_bil)
 */

bilatere_t ** InsertionBil(bilatere_t ** b, bilatere_t * elt);

/* FONCTION : LiberationBil
 * Libere toute les données allouées dans la structure bilatere.
 *
 * entree : le pointeur de debut de la liste bilatere (bilatere_t * p_bil)
 * varloc : les pointeurs courants (action_t * cour_act et bilatere_t * cour_bil)
 *          les pointeurs temporaires (action_t * tmp_act et bilatere_t * tmp_bil)
 * sortie : rien
 */

void LiberationBil(bilatere_t * p_bil);

/*----------------------------------------------------*/
/*                ECRITURE (ecriture.c)               */
/*----------------------------------------------------*/

/* FONCTION : Ecriture
 * Ecriture de la liste dans un fichier texte.
 *
 * entree : le pointeur de debut de liste (semaine_t * p_sem)
 *          le nom du fichier à ouvrir (char * nom)
 * varloc : le nouveau pointeur à inserer (semaine_t * new)
 * sortie : code erreur fourni en parametre de sortie (int code)
 */

int Ecriture(semaine_t * p_sem, char * nom);

/* FONCTION : Lecture
 * Lecture dans un fichier texte et creation de la liste.
 *
 * entree : le pointeur de la structure (semaine_t ** p_sem)
 *          le nom du fichier à ouvrir (char * nom_f)
 * varloc : pointeurs de parcours, les informations à copier
 * sortie : code erreur fourni en parametre de sortie (int erreur)
 */

int Lecture(semaine_t ** p_sem, char * nom_f);

/*----------------------------------------------------*/
/*  RECHERCHE DE MOTIF (recherche_motif.c)            */
/*----------------------------------------------------*/

/* FONCTION : RechercheMotif
 * Crée une liste contigue des jours ou une action contenant un motif donné est présente.
 *
 * entree : pointeur sur la liste chainee des semaines (semaine_t * p_sem).
 *          pointeur sur la liste contigue des jours (motif_t * p_motif).
 *          chaine du motif à rechercher (char * motif_rech).
 * varloc : les pointeurs courants (semaine_t * cour_sem, action_t * cour_act).
 *          compteur de la liste contigue (int compteur).
 *          chaine de copie (char chaine_motif[10], char libelle[11], char dechet[TMAX]).
 * sortie : l'adresse de la dernière cellule de recherche.
 */

int RechercheMotif(semaine_t * p_sem, motif_t * p_motif, char * motif_rech);

/* FONCTION : AffichageMotif
 * Crée une liste contigue
 *
 * entree : pointeur sur la liste chainee des semaines (semaine_t * p_sem).
 *          pointeur sur la liste contigue des jours (motif_t * p_motif).
 *          le nombre de cellules completes (int compteur).
 * varloc : les pointeurs courants (semaine_t * cour_sem, action_t * cour_act).
 *          compteur de la liste contigue (int compteur).
 *          chaine de copie (char chaine_motif[10], char libelle[11], char dechet[TMAX]).
 * sortie : l'adresse de la dernière cellule de recherche.
 */

void AffichageMotif(motif_t * p_motif, int compteur);

#endif

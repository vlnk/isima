/* TITRE : ABINAIRE_TXT (EN TETE)
 * FICHIER : abinaire_txt.h
 *
 * AUTEUR : Valentin Laurent
 * DATE : 24/01/13
 *
 * COMPILATION : gcc tp10.c -o tp10 -Wall -Wextra -g -ansi -pedantic -lm
 */

/*GARDIEN*/
#ifndef abinaire_txt_H
#define abinaire_txt_H

/* INCLUDE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* DEFINE */
#define M 32
#define TRUE 1
#define FALSE 0

/* STRUCTURE */
typedef struct noeud
{
    char *          nom;
    char *          prenom;
    char *          login;
    char *          mdp;
    struct noeud *  g;
    struct noeud *  d;
} noeud_t;

/* PROTOTYPES */
void inserer (noeud_t ** pracine, noeud_t * saisie);
void affichage (noeud_t * r, int prof);
void affiche_menu ();
noeud_t * saisie ();
void liberation (noeud_t ** pracine);
noeud_t ** recherche (noeud_t ** pracine, noeud_t * saisie_t);
void suppression (noeud_t ** pracine, noeud_t * saisie_t);
void supprAux (noeud_t ** pracine, noeud_t * r);
void miseAJour (noeud_t ** pracine, noeud_t * saisie_t);
void recherchePrenom (noeud_t * r, char * prenom_t);
void rechercheNom (noeud_t * r,char * nom_t);
void ecriture (noeud_t * r, char * nom_fic);
void efface (char * nom_fic);
void lecture (noeud_t ** pracine, char * nom_fic);

#endif

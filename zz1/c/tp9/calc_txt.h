/* calc_txt.h
 *
 * Evaluation et calcul d'une expression saisie pas l'utilisateur.
 *
 * Version 0.2
 * Auteur : Valentin
 * Date : 20/01/13
 *
 * Compilation : gcc calc_txt.c -o calculatrice -Wall -Wextra -g -ansi -pedantic -lm
 */

/*gardien*/
#ifndef calc_txt_H
#define calc_txt_H

/*INCLUDE*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

/*DEFINE*/
#define TMAX 100
#define TRUE 1
#define FALSE 0


/*STRUCTURES*/
typedef struct str1
{
    char *      exp1;
    char        op;
    char *      exp2;
} operation;

typedef struct str2
{
    char *      fct;
    char *      param;
} fonction;

typedef struct str3
{
    double      sup;
    double      inf;
    double      delta;
} intervalle;

/* fonction : IDENTIFICATIONFONCTION
 *
 * renvoie l'indice du tableau de fonction correspondant à l'expression lue, -1 sinon
 *
 * en entrée : l'expression à interpréter (char*)
 *             le tableau de fonction (const char**)
 * en sortie : l'indice du tableau (int)
 */

int identificationFonction(char* expression,const char** tab_fct);

/* fonction : IDENTIFICATIONOPERATION
 *
 * renvoie l'indice du tableau de fonction correspondant à l'expression lue, -1 sinon
 *
 * en entrée : l'expression à interpréter (char*)
 *             le tableau de fonction (const char**)
 * en sortie : l'indice du tableau (int)
 */

int identificationOperation(char expression,const char* tab_op);

/* fonction : EVAL
 *
 * renvoie le résultat du calcul de l'expression évaluée.
 *
 * en entrée : la valeur saisie (double)
 *             le pointeur sur l'entier d'activation de l'évaluation d'intervalles.
 * en sortie : la valeur de l'expression évaluée (double)
 */

double eval(char* expr, int* verif_intervalle);

/* fonction : EVALINTERVALLE
 *
 * renvoie le résultat du calcul de l'expression évaluée.
 *
 * en entrée : la valeur saisie (double)
 *             le pointeur sur l'entier d'activation de l'évaluation d'intervalles.
 * en sortie : la valeur de l'expression évaluée (double)
 */

double evalIntervalle(char* expr,double cour,int* verif_intervalle);

/* fonction : EVALFONCTION
 *
 * renvoie la valeur de la fonction évaluée avec une valeur saisie "fonction(valeur)"
 *
 * en entrée : la valeur saisie (double)
 *             l'indice du tableau correspondant à la fonction (int)
 * en sortie : la valeur de l'expression évaluée (double)
 */

double evalFonction(double valeur, int i);

/* fonction : EVALOPERATION
 *
 * lit une chaine de caractère et renvoie un tableau contenant la fonction et la valeur associée
 *
 * en entrée : la chaine saisie (char*)
 *             le tableau de chaine (char**)
 * en sortie : le tableau contenant les deux chaines (char**)
 */

double evalOperation(double val1, double val2, int i);

/* fonction : LECTUREOPERATION
 *
 * lit une chaine de caractère et stocke dans une structure l'opperateur et ses valeurs associées
 *
 * en entrée : la chaine saisie (char*)
 * en sortie : l'opérateur et ses valeurs associées dans une structure operation.
 *             ex : "4 + 3" -> ("4", '+', "3")
 */

operation lectureOperation(char* chaine);

/* fonction : LECTUREFONCTION
 *
 * Récupère le nom d'une fonction et son paramètre à partir d'une chaine de caractère.
 *
 * en entrée : la chaine saisie (char*)
 *             le pointeur sur l'entier d'activation de l'évaluation d'intervalles.
 * en sortie : le nom et le paramètre de la fonction sous la structure fonction.
 *             ex : "cos(x)" -> ("cos","x")
 */

fonction lectureFonction(char* chaine,int* verif_intervalle);

/* fonction : LECTUREINTERVALLE
 *
 * Récupère les bornes d'un intervalle et son pas delta à partir d'une chaine de caractère.
 *
 * en entrée : la chaine saisie (char*)
 * en sortie : les bornes et le pas de l'intervalle sous la structure intervalle.
 *             ex : "expression,a,b,delta" -> ("a","b","delta")
 */

intervalle lectureIntervalle(char * chaine);

/* fonction : VERIFFONCTION
 *
 * Vérifie si l'expression est une fonction.
 *
 * en entrée : la chaine saisie (char*)
 * en sortie : VRAI(int) si c'est une fonction, FAUX(int) sinon.
 */

int verifFonction(char * chaine);

/* fonction : VERIFNUM
 *
 * Vérifie si l'expression est une valeur numérique.
 *
 * en entrée : la chaine saisie (char*)
 * en sortie : VRAI(int) si c'est une valeur numérique, FAUX(int) sinon.
 */

int verifNum(char* chaine);

/* fonction : VERIFINTERVALLE
 *
 * Vérifie si l'expression est une valeur numérique.
 *
 * en entrée : la chaine saisie (char*)
 *             le pointeur sur l'entier d'activation de l'évaluation d'intervalles.
 * en sortie : VRAI(int) si il y a un intervalle de déclaré, FAUX(int) sinon.
 */

int verifIntervalle(char * chaine, int * verif_intervalle);

#endif

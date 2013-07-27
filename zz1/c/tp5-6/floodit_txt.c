/* floodit_xlib.c
 *
 * Affichage graphique du programme floodit.
 *
 * Compilation MacOSX : gcc floodit_xlib.c -o floodit -L/opt/X11/lib -lX11 -pedantic -Wall -Wextra -ansi
 *
 */

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*DEFINES*/
#define COULEUR 7


/* fonction : INITIALISER
 *
 * initialise mat avec des couleurs aux hasard.
 *
 * en entrée : la matrice
 * en sortie : rien
 */

void initialiser(int ** mat,int germe,int taille_t)
{
    /*variables locales*/
    int i=0,j=0;

    /*initialisation du germe*/
    srand(germe);

    for(i=0;i<taille_t;i++)
    {
        for(j=0;j<taille_t;j++)
        {
            /*initialisation de la grille*/
            mat[i][j] = (rand()%COULEUR)*100;
        }
    }
}

/* fonction : FIN
 *
 * renvoie 1 si la grille est remplie, 0 sinon
 *
 * en entrée : la matrice
 * en sortie : rien
 */

int fin(int ** mat, int taille_t)
{
    /*variables locales*/
    int i=0,j=0;
    int valeur_origine = mat[0][0]/100;
    int verif = 0;

    for(i=0;i<taille_t;i++)
    {
        for(j=0;j<taille_t;j++)
        {
            /*verifie la matrice*/
            if (mat[i][j]/100 != valeur_origine)
            {
                verif = 1;
                break;
            }
        }
    }
    return verif;
}

/* fonction : REMPLIR
 * Remplie la grille selon les règles de Flood It
 *
 * en entrée : la matrice
               l'ancienne couleur (int)
               les coordonées i et j de la matrice (int)*(int)
               la valeur de l'itération courante (int)

 * en sortie : rien
 */

void remplir(int ** mat, int old_color, int new_color, int i, int j, int iteration, int taille_t)
{
    /*variables locales*/
    int cour = mat[i][j];
    int iter_cour = mat[i][j]%100;

    /*vérification de la couleur de la case*/
    if (cour/100 == old_color)
    {
        mat[i][j] = new_color*100 + iter_cour;

        /*vérification de l'itération de la case*/
        if (cour%100 == 0)
        {
                mat[i][j] = mat[i][j] + iteration;
        }

        /*vérification des cases [i+1;j]*/
        if ((i < (taille_t - 1)) && (mat[i+1][j]/100 == old_color))
        {
            remplir(mat, old_color, new_color, i+1, j, iteration,taille_t);
		}

        /*vérification des cases [i-1;j]*/
        if ((i > 0) && (mat[i-1][j]/100 == old_color))
		{
            remplir(mat, old_color, new_color, i-1, j, iteration,taille_t);
		}

        /*vérification des cases [i;j+1]*/
        if ((j < (taille_t - 1)) && (mat[i][j+1]/100 == old_color))
		{
			remplir(mat, old_color, new_color, i, j+1, iteration,taille_t);
		}
        /*vérification des cases [i;j-1]*/
        if ((j > 0) && (mat[i][j-1]/100 == old_color))
		{
			remplir(mat, old_color, new_color, i, j-1, iteration,taille_t);
		}
    }
}


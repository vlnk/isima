/* demineur_txt.c
 *
 * Fonctions de bases du démineur (crée à partir de la version texte pour la version xlib).
 *
 */

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Fonction : INITIALISERJOUEUR
 *
 * Initialise la matrice mat_t avec des -1
 *
 * En entrée : la matrice.
 *
 * En sortie : rien.
 */

void initialiserJoueur(int ** mat_t, int taille_t)
{
    /*variables locales*/
    int i=0,j=0;

    for(i=0;i<taille_t;i++)
    {
        for(j=0;j<taille_t;j++)
        {
            /*initialisation de la grille*/
            mat_t[i][j] = -1;
        }
    }
}

/* Fonction : INITIALISERJEU
 *
 * Initialise la matrice mat avec des 0
 *
 * En entrée : la matrice.
 *
 * En sortie : rien.
 */

void initialiserJeu(int ** mat, int taille_t)
{
    /*variables locales*/
    int i=0,j=0;

    for(i=0;i<taille_t;i++)
    {
        for(j=0;j<taille_t;j++)
        {
            /*initialisation de la grille*/
            mat[i][j] = 0;
        }
    }
}

/* Fonction : PLACERBOMBE
 *
 * Initialise la matrice mat en plaçant des bombes au hasard.
 *
 * En entrée : la matrice.
 *
 * En sortie : rien.
 */

void placerBombe(int ** mat,int nb_bombe, int taille_t, int germe)
{
    /*variables locales*/
    int i=0,j=0,k=0;

    /*initialisation du germe*/
    srand(germe);

    for(k=0;k<nb_bombe;k++)
    {
        /*initialisation de la grille*/
        i = rand()%taille_t;
        j = rand()%taille_t;
        mat[i][j] = 100;
    }
}

/* fonction : FIN
 *
 * renvoie 1 si la grille est remplie, 0 sinon
 *
 * en entrée : la matrice
 * en sortie : rien
 */

int fin(int ** mat,int ** mat_t,int taille_t)
{
    /*variables locales*/
    int i=0,j=0;
    int verif = 1;

    for(i=0;i<taille_t;i++)
    {
        for(j=0;j<taille_t;j++)
        {
            /*verifie la matrice*/
            if (mat[i][j]/100 != mat_t[i][j]/100)
            {
                verif = 0;
                break;
            }
        }
    }
    return verif;
}



/* Fonction : REMPLIRJEU
 *
 * Remplie la grille de Jeu selon les règles du Démineur.
 *
 * En entrée : la matrice.
 *             les coordonées i et j de la matrice (int)*(int).
 *
 * En sortie : rien.
 */

void remplirJeu(int ** mat, int i, int j, int taille_t)
{
    /*variables locales*/

    /*VERTICAL*/
    /*vérification des cases [i+1;j]*/
    if ((i < (taille_t - 1)) && (mat[i+1][j]/100 == 1))
    {
        mat[i][j] = mat[i][j] + 1;
	}

    /*vérification des cases [i-1;j]*/
    if ((i > 0) && (mat[i-1][j]/100 == 1))
	{
        mat[i][j] = mat[i][j] + 1;
	}

    /*HORIZONTAL*/
    /*vérification des cases [i;j+1]*/
    if ((j < (taille_t - 1)) && (mat[i][j+1]/100 == 1))
	{
		mat[i][j] = mat[i][j] + 1;
	}

    /*vérification des cases [i;j-1]*/
    if ((j > 0) && (mat[i][j-1]/100 == 1))
	{
		mat[i][j] = mat[i][j] + 1;
	}

    /*EN DIAGONALE*/
    /*vérification des cases [i-1;j-1]*/
    if ((i > 0) && (j > 0) && (mat[i-1][j-1]/100 == 1))
    {
        mat[i][j] = mat[i][j] + 1;
    }

    /*vérification des cases [i-1;j+1]*/
    if ((i > 0) && (j < (taille_t - 1)) && (mat[i-1][j+1]/100 == 1))
    {
        mat[i][j] = mat[i][j] + 1;
    }

    /*vérification des cases [i+1,j-1]*/
    if ((i < (taille_t - 1)) && (j > 0) && (mat[i+1][j-1]/100 == 1))
    {
        mat[i][j] = mat[i][j] + 1;
    }

    /*vérification des cases [i+1,j+1]*/
    if ((i < (taille_t - 1)) && (j < (taille_t - 1)) && (mat[i+1][j+1]/100 == 1))
    {
        mat[i][j] = mat[i][j] + 1;
    }

}

/* Fonction : REMPLIRJOUEUR
 *
 * Remplie la grille du Joueur selon les règles du Démineur.
 *
 * En entrée : la matrice.
 *             les coordonées i et j de la matrice (int)*(int).
 *
 * En sortie : rien.
 */


void remplirJoueur(int ** mat, int ** mat_t, int i, int j, int taille_t)
{
    /*variables locales*/

    if (mat[i][j]%100 == 0)
    {
        mat_t[i][j] = 0;

        /*EN VERTICAL*/
        /*vérification des cases [i+1;j]*/
        if ((i < (taille_t - 1)) && (mat_t[i+1][j] == -1) && (mat[i+1][j]%100 == 0))
        {
            remplirJoueur(mat,mat_t,i+1,j,taille_t);
	    }
        else if ((i < (taille_t - 1)) && (mat[i+1][j]%100 != 0))
        {
            mat_t[i+1][j] = mat[i+1][j]%100;
	    }

        /*vérification des cases [i-1;j]*/
        if ((i > 0) && (mat_t[i-1][j] == -1) && (mat[i-1][j]%100 == 0))
	    {
            remplirJoueur(mat,mat_t,i-1,j,taille_t);
	    }
        else if ((i > 0) && (mat[i-1][j]%100 != 0))
	    {
            mat_t[i-1][j] = mat[i-1][j]%100;
	    }

        /*EN HORIZONTAL*/
        /*vérification des cases [i;j+1]*/
        if ((j < (taille_t - 1)) && (mat_t[i][j+1] == -1) && (mat[i][j+1]%100 == 0))
	    {
		    remplirJoueur(mat,mat_t,i,j+1,taille_t);
	    }
        else if ((j < (taille_t - 1)) && (mat[i][j+1]%100 != 0))
	    {
		    mat_t[i][j+1] = mat[i][j+1]%100;
	    }

        /*vérification des cases [i;j-1]*/
        if ((j > 0) && (mat_t[i][j-1] == -1) && (mat[i][j-1]%100 == 0))
	    {
		    remplirJoueur(mat,mat_t,i,j-1,taille_t);
	    }
        else if ((j > 0) && (mat[i][j-1]%100 != 0))
	    {
            mat_t[i][j-1] = mat[i][j-1]%100;
	    }

        /*EN DIAGONALE*/
        /*vérification des cases [i-1;j-1]*/
        if ((i > 0) && (j > 0) && (mat_t[i-1][j-1] == -1) && (mat[i-1][j-1]%100 == 0))
        {
            remplirJoueur(mat,mat_t,i-1,j-1,taille_t);
        }
        else if ((i > 0) && (j > 0) && (mat[i-1][j-1]%100 != 0))
        {
            mat_t[i-1][j-1] = mat[i-1][j-1]%100;
        }

        /*vérification des cases [i-1;j+1]*/
        if ((i > 0) && (j < (taille_t - 1)) && (mat_t[i-1][j+1] == -1) && (mat[i-1][j+1]%100 == 0))
        {
            remplirJoueur(mat,mat_t,i-1,j+1,taille_t);
        }
        else if ((i > 0) && (j < (taille_t - 1)) && (mat[i-1][j+1]%100 != 0))
        {
            mat_t[i-1][j+1] = mat[i-1][j+1]%100;
        }

        /*vérification des cases [i+1,j-1]*/
        if ((i < (taille_t - 1)) && (j > 0) && (mat_t[i+1][j-1] == -1) && (mat[i+1][j-1]%100 == 0))
        {
            remplirJoueur(mat,mat_t,i+1,j-1,taille_t);
        }
        else if ((i < (taille_t - 1)) && (j > 0) && (mat[i+1][j-1]%100 != 0))
        {
            mat_t[i+1][j-1] = mat[i+1][j-1]%100;
        }
        /*vérification des cases [i+1,j+1]*/
        if ((i < (taille_t - 1)) && (j < (taille_t - 1)) && (mat_t[i+1][j+1] == -1) && (mat[i+1][j+1]%100 == 0))
        {
            remplirJoueur(mat,mat_t,i+1,j+1,taille_t);
        }
        else if ((i < (taille_t - 1)) && (j < (taille_t - 1)) && (mat[i+1][j+1]%100 != 0))
        {
            mat_t[i+1][j+1] = mat[i+1][j+1]%100;
        }

    }
    else
    {
        mat_t[i][j] = mat[i][j]%100;
    }

}


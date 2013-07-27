/*
 *      floodit.c
 *
 *
 * Rapport Valgrind : ERROR SUMMARY: 1565 errors from 101 contexts (suppressed: 2 from 2)
 * -> Je ne sais pas comment les corriger.
 */

#include <stdio.h>
#include <stdlib.h>

#define TAILLE 12
#define COULEUR 7

/*d�clarations*/
void afficheGrille(int ** mat);
void afficheIteration(int ** mat);
int fin(int ** mat);
void initialiser(int ** mat);
void remplir(int ** mat, int old_color, int new_color, int i, int j, int iteration);

int main(int argc, char** argv)
{
	/*variables locales*/
    int  ** mat;
    int     i=0, j=0, k=0;
    int     iteration = 0;
    int     valeur_t = 0, old_color, new_color;
    int     iteration_max_t;
    int     verif_alloc = 0;

    /*saisie des param�tres par l'utilisateur*/
    printf("Nombre d'iterations maximales ? ");
    fflush(stdout);
    scanf("%d%*c", &iteration_max_t);

    /*allocation m�moire de la matrice*/
    mat = (int **) malloc(sizeof(int *)*TAILLE);

    if (mat == NULL)
    {
        printf("Allocation de mat impossible");
    }
    else
    {
        /*allocation m�moire des lignes*/
        for (i=0;i<TAILLE;i++)
        {
            mat[i] = (int *) malloc(sizeof(int)*TAILLE);

            if (mat[i] == NULL)
            {
                printf("Allocation de mat[%d] impossible", i);
                verif_alloc = 1;

                for(j=i;j==0;j--)
                {
                    free(mat[j]);
                }
                free(mat);
                break;
            }
        }

        if (verif_alloc == 0)
        {
            /*initialisation de la grille et des variables*/
            initialiser(mat);
            old_color = mat[0][0]/100;

            afficheGrille(mat);

            while ((fin(mat) != 1) & (valeur_t != 999) & (iteration <= iteration_max_t))
            {
                /*choix de la valeur de raz-de-marree par l'utilisateur*/
                printf("Veuillez entrer la valeur de raz-de-marree : ");
                fflush(stdout);
                scanf("%d%*c", &valeur_t);

                /*remplissage de la matrice selon les conditions*/
                if ((valeur_t != old_color) && (valeur_t >= 0) && (valeur_t < COULEUR))
                {
                    new_color = valeur_t;
                    iteration = iteration + 1;

                    remplir(mat,old_color,new_color,0,0,iteration);
                    afficheGrille(mat);
                    old_color = mat[0][0]/100;
                }
                /*affichage de la matrice d'it�ration selon les conditions*/
                else if ((valeur_t >= 900) & (valeur_t < 999))
                {
                    afficheIteration(mat);
                }
            }

            afficheGrille(mat);
            afficheIteration(mat);

            /*v�rification de la grille (fausse ou compl�te)*/
            if (fin(mat) == 1)
            {
                printf("\nGAGNE !\nVous avez effectue %d iterations.\n",iteration);
            }
            else
            {
                printf("\nPERDU !\n");
            }

            /*lib�ration de l'allocation m�moire*/
            for (k=(TAILLE - 1);k==0;k-=1)
            {
                free(mat[k]);
            }
            free(mat);

        }
    }
    return 0;
}


/* Fonction : initialiser
 *
 * Initialise la matrice mat avec des couleurs au hasard et met 0 � l'it�ration
 *
 * En entr�e : la matrice.
 *
 * En sortie : rien.
 */

void initialiser(int ** mat)
{
    /*variables locales*/
    int i=0,j=0;
    int germe;

    printf("germe ? ");
    fflush(stdout);
    scanf("%d%*c", &germe);
    printf("\n");

    /*initialisation du germe*/
    srand(germe);

    for(i=0;i<TAILLE;i++)
    {
        for(j=0;j<TAILLE;j++)
        {
            /*initialisation de la grille*/
            mat[i][j] = (rand()%COULEUR)*100;
        }
    }
}

/* Fonction : afficheGrille
 *
 * Affiche la grille mat.
 *
 * En entr�e : la matrice.
 *
 * En sortie : rien.
 */

void afficheGrille(int ** mat)
{
    /*variables locales*/
    int i=0,j=0;

    for(i=0;i<TAILLE;i++)
    {
        for(j=0;j<TAILLE;j++)
        {
            /*affichage de la grille*/
            printf("%d ",mat[i][j]/100);
        }
        printf("\n");
    }
    printf("\n");
}

/* Fonction : afficheIteration
 *
 * Affiche la grille mat des it�rations.
 *
 * En entr�e : la matrice.
 *
 * En sortie : rien.
 */

void afficheIteration(int ** mat)
{
    /*variables locales*/
    int i=0,j=0;

    for(i=0;i<TAILLE;i++)
    {
        for(j=0;j<TAILLE;j++)
        {
            if (mat[i][j]%100 - 10 < 0)
            {
                /*affichage de la grille*/
                printf("%d  ",mat[i][j]%100);
            }
            else
            {
                printf("%d ",mat[i][j]%100);
            }

        }
        printf("\n");
    }
    printf("\n");
}

/* Fonction : fin
 *
 * Renvoie 1 si la grille est remple de cases de la m�me couleur, 0 sinon.
 *
 * En entr�e : la matrice.
 *
 * En sortie : rien.
 */

int fin(int ** mat)
{
    /*variables locales*/
    int i=0,j=0;
    int valeur_origine = mat[0][0]/100;
    int verif = 1;

    for(i=0;i<TAILLE;i++)
    {
        for(j=0;j<TAILLE;j++)
        {
            /*verifie la matrice*/
            if (mat[i][j]/100 != valeur_origine)
            {
                verif = 0;
                break;
            }
        }
    }
    return verif;
}

/* Fonction : remplir
 *
 * Remplie la grille selon les r�gles de Flood It.
 *
 * En entr�e : la matrice.
 *             l'ancienne couleur (int).
 *             les coordon�es i et j de la matrice (int)*(int).
 *             la valeur de l'it�ration courante (int).
 *
 * En sortie : rien.
 */

void remplir(int ** mat, int old_color, int new_color, int i, int j, int iteration)
{
    /*variables locales*/
    int cour = mat[i][j];
    int iter_cour = mat[i][j]%100;

    /*v�rification de la couleur de la case*/
    if (cour/100 == old_color)
    {
        mat[i][j] = new_color*100 + iter_cour;

        /*v�rification de l'it�ration de la case*/
        if (cour%100 == 0)
        {
                mat[i][j] = mat[i][j] + iteration;
        }

        /*v�rification des cases [i+1;j]*/
        if ((i < (TAILLE - 1)) && (mat[i+1][j]/100 == old_color))
        {
            remplir(mat, old_color, new_color, i+1, j, iteration);
		}

        /*v�rification des cases [i-1;j]*/
        if ((i > 0) && (mat[i-1][j]/100 == old_color))
		{
            remplir(mat, old_color, new_color, i-1, j, iteration);
		}

        /*v�rification des cases [i;j+1]*/
        if ((j < (TAILLE - 1)) && (mat[i][j+1]/100 == old_color))
		{
			remplir(mat, old_color, new_color, i, j+1, iteration);
		}

        /*v�rification des cases [i;j-1]*/
        if ((j > 0) && (mat[i][j-1]/100 == old_color))
		{
			remplir(mat, old_color, new_color, i, j-1, iteration);
		}
    }
}


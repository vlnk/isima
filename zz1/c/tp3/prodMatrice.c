/*
 *    nom : prodMatrice.c
 *    auteur : laurentv@etud
 *
 *    date : 9/10/12
 *
 *    NB : � tester avec les fichiers "vecteur.txt" et "matrice.txt".
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_NOM 100

double ** lectureMat(int * taille_m, char nom[]);
void afficheMat(int taille_m, double ** mat, char * nomMat);
double * lectureVect(int * taille_v, char nom[]);
void afficheVect(int taille_v, double * vect, char * nomVect);
double  prodScalaire(int taille_v, int taille_m, double * vect, double * matLigne);
double * prodMatVect(int taille_v, int taille_m, double * vect, double ** mat);



/*
 * fonction : main
 *
 * Effectue le produit entre une matrice et un vecteur.
 *
 */


int main(int argc, char** argv)
{

    /*var locales*/
    int taille_m, taille_v, i;
    double ** mat;
    double * vect;
    char nomVect[TAILLE_NOM];
    char nomMat[TAILLE_NOM];
    double * prod;

    /*demande de saisi du fichier de matrice*/
    printf("Saisissez le fichier de la matrice : ");
    fflush(stdout);
    scanf("%s%*c", nomMat);

    /*demande de saisi du fichier de vecteur*/
    printf("Saisissez le fichier du vecteur : ");
    fflush(stdout);
    scanf("%s%*c", nomVect);

    /*lecteur et affichage de la matrice*/
    mat = lectureMat(&taille_m, nomMat);
    afficheMat(taille_m, mat, nomMat);

    /*lecture et affichage du vecteur*/
    vect = lectureVect(&taille_v, nomVect);
    afficheVect(taille_v, vect, nomVect);

    /*Calcul et affichage du produit matriciel*/
    prod = prodMatVect(taille_v,taille_m,vect,mat);
    afficheVect(taille_m, prod, "produit");

    /*lib�ration de la m�moire*/
    for(i = 0;i < taille_m;i++)
    {
        free(mat[i]);
    }

    free(mat);
    free(vect);
    free(prod);

    return 0;
}

/*
 * fonction : lectureMat
 *
 * Lit le fichier de matrice et rentre ces valeurs dans la matrice mat en argument.
 *
 * entr�e : *taille_m : le pointeur vers la taille de la matrice (int).
 *          nom[] : le nom du fichier de la matrice (char[TAILLE_NOM]).
 *
 * sortie : p : la matrice dans laquelle sont copi�es les valeurs du fichier texte (*double).
 *
 */

double ** lectureMat(int * taille_m, char nom[])
{
    /*var locales*/
    FILE * fichMatrice;
    double ** p;
    int i=0,k;

    /*lecture*/
    fichMatrice = fopen(nom, "r");

    /*test overture fichier*/
    if (fichMatrice==NULL)
    {
        printf("Probl�me d'ouverture\n");
    }
    else
    {
        printf("\nLe fichier \"%s\" est ouvert.", nom);

        /*lecture de l'ordre de la Matrice(n*n)*/
        fscanf(fichMatrice, "%d", taille_m);

        /*allocation du vecteur contenant les lignes de la matrice*/
        p = (double **) malloc ((*taille_m)*sizeof(double *));

        if (p == NULL)
        {
            printf("allocation de m�moire impossible");
        }
        else
        {

            /*l'allocation de m�moire a eu lieu*/

            for(i = 0;i < *taille_m;i++)
            {
                /*allocation de la ligne de la matrice*/
                p[i] = (double *) malloc ((*taille_m)*sizeof(double));

                if (p[i] == NULL)
                {
                    printf("allocation de m�moire impossible");
                }
                else
                {

                    for(k = 0;k < *taille_m;k++)
                    {
                        fscanf(fichMatrice,"%lf", &p[i][k]);
                    }
                }
            }
        }

        printf("\n");

        /*fermeture du fichier*/
        fclose(fichMatrice);

    }

    return p;
}


/*
 * fonction : lectureVect
 *
 * Lit le fichier de vecteur et rentre ces valeurs dans le vecteur vect en argument.
 *
 * entr�e : *taille_v : le pointeur vers la taille du vecteur (int).
 *          nom[] : le nom du fichier de vecteur (char[TAILLE_NOM]).
 *
 * sortie : p : le vecteur dans lequel sont copi�es les valeurs du fichier texte (*double).
 *
 */

double * lectureVect(int * taille_v, char nom[])
{
    /*var locales*/
    FILE * fichVecteur;
    double * p;
    int i=0;

    /*lecture*/
    fichVecteur = fopen(nom, "r");

    /*test overture fichier*/
    if (fichVecteur==NULL)
    {
        printf("Probl�me d'ouverture\n");
    }
    else
    {
        printf("Le fichier \"%s\" est ouvert.", nom);
        fflush(stdout);


        /*lecture de l'ordre du vecteur*/
        fscanf(fichVecteur, "%d", taille_v);

        /*allocation du vecteur*/
        p = (double *) malloc ((*taille_v)*sizeof(double));

        if (p == NULL)
        {
            printf("allocation de m�moire impossible");
        }
        else
        {
            /*l'allocation de m�moire a eu lieu*/
            while(!feof(fichVecteur))
            {
                fscanf(fichVecteur,"%lf", &p[i]);
                i++;
            }
        }

        printf("\n");

        /*fermeture du fichier*/
        fclose(fichVecteur);


    }

    return p;
}


/*
 * fonction : afficheVect
 *
 * Affiche les composantes d'un vecteur de taille taille_v.
 *
 * entr�e : *taille_v : pointeur sur la taille du vecteur (int *).
 *          *vect : le vecteur/tableau contenant les composantes � afficher (double *).
 *          *nomVect : le nom du fichier de vecteur (char *), n�cessaire pour l'affichage.
 * sortie : rien.
 *
 */

void afficheVect(int taille_v, double * vect, char * nomVect)
{
    /*var locales*/
    int i = 0;

    /*affichage de la taille*/
    printf("La taille du vecteur \"%s\" est %d.\n", nomVect, taille_v);

    for(i = 0;i < taille_v;i++)
    {
        /*affichage des composantes*/
        printf("%2.1lf\n", vect[i]);
    }

    printf("\n");
}


/*
 * fonction : afficheMat
 *
 * Affiche les composantes d'un vecteur de taille taille_m.
 *
 * entr�e : *taille_m : pointeur sur la taille de la matrice (int *).
 *          *mat : le vecteur/tableau contenant les composantes � afficher (double *).
 *          *nomMat : le nom du fichier de matrice (char *), n�cessaire pour l'affichage.
 *
 * sortie : rien.
 *
 */

void afficheMat(int taille_m, double ** mat, char * nomMat)
{
    /*var locales*/
    int i=0, j=0;

    /*affichage de la taille*/
    printf("La taille de la matrice \"%s\" est %d.\n\n", nomMat, taille_m);

    for(i = 0;i < taille_m;i++)
    {
        for(j = 0;j < taille_m;j++)
        {
            /*affichage des composantes*/
            printf("%2.1lf  ", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

/*
 * fonction : prodScalaire
 *
 * Calcule le produit de deux vecteurs (vect1 et vect2).
 *
 * entr�e : *taille_v : pointeur sur la taille du vecteur vect (int *).
 *          *taille_m : pointeur sur la taille de la matrice mat (int *).
 *          *vect : vecteur (double *).
 *          *matLigne : la ligne de la matrice n�cessaire pour faire le produit lignes par colonnes (double *).
 *
 * sortie : prodS : le r�sultat du produit scalaire entre matLigne et vect (double).
 *
 */

double  prodScalaire(int taille_v, int taille_m, double * vect, double * matLigne)
{
    /*var locales*/
    int i;
    double prodS=0;

    /*v�rifie si le ps est possible*/
    if (taille_v != taille_m)
    {
        printf("les ordres sont diff�rents, le produit sclaire n'est pas calculable");
    }
    else
    {
        /*calcul du ps*/
        for(i = 0;i < taille_v;i++)
        {
            prodS += vect[i] * matLigne[i];
        }

    }

    return prodS;
}


/*
 * fonction : prodMatVect
 *
 * Calcule le produit de deux vecteurs (vect1 et vect2).
 *
 * entr�e : *taille_v : pointeur sur la taille du vecteur vect (int *).
 *          *taille_m : pointeur sur la taille de la matrice mat (int *).
 *          *vect : vecteur (double *).
 *          *mat : matrice (double **).
 *
 * sortie : prodMV : le r�sultat du produit matriciel entre mat et vect (double *).
 *
 */

double * prodMatVect(int taille_v, int taille_m, double * vect, double ** mat)
{
    /*var locales*/
    double * prodMV;
    int i;

    /*allocation du vecteur produit*/
    prodMV = (double *) malloc(taille_v*sizeof(double));

    for(i = 0;i < taille_m;i++)
    {
        /*calcul du produit matriciel ligne par colonne*/
        prodMV[i] = prodScalaire(taille_v,taille_m,vect,mat[i]);
    }

    return prodMV;
}



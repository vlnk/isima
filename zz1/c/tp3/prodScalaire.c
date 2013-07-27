/*
 * nom : prodScalaire.c
 *
 * auteur : laurentv
 *
 * date : 5/10/12
 *
 * NB : à tester avec les fichier "vecteur.txt" et "vecteur2.txt"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_NOM 100

double * lecture(int * taille_v, char nom[]);
void afficheVect(int taille_v, double * vect, char * nom);
double prodScalaire(int taille_v1, int taille_v2, double * vect1, double * vect2, char * nom1, char * nom2);


/*
 * fonction : main
 *
 * Effectue le produit scalaire de 2 vecteurs.
 *
 */

int main(int argc, char ** argv)
{

  /*var locales*/
  int taille_v1=0,taille_v2=0;
  double * vect1;
  double * vect2;
  char nom1[TAILLE_NOM];
  char nom2[TAILLE_NOM];
  double prodS;

  printf("Saisissez le fichier du vecteur n°1 : ");
  fflush(stdout);
  scanf("%s%*c", nom1);

  printf("Saisissez le fichier du vecteur n°2 : ");
  fflush(stdout);
  scanf("%s%*c", nom2);

  vect1 = lecture(&taille_v1, nom1);
  afficheVect(taille_v1, vect1, nom1);

  vect2 = lecture(&taille_v2, nom2);
  afficheVect(taille_v2, vect2, nom2);

  prodS = prodScalaire(taille_v1, taille_v2, vect1, vect2, nom1, nom2);

  free(vect1);
  free(vect2);

  return 0;
}

/*
 * fonction : lecture
 *
 * Lit le fichier de vecteur et rentre ces valeurs dans le vecteur vect en argument.
 *
 * entrée : *taille_v : le pointeur vers la taille du vecteur (int).
 *          nom[] : le nom du fichier de vecteur (char[TAILLE_NOM]).
 *
 * sortie : p : le vecteur dans lequel sont copiées les valeurs du fichier texte (double *).
 *
 */

double * lecture(int * taille_v, char nom[])
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
        printf("Problème d'ouverture\n");
    }
    else
    {
        printf("Le fichier \"%s\" est ouvert.", nom);
        fflush(stdout);

        /*lecture de l'ordre du vecteur*/
        fscanf(fichVecteur, "%d", taille_v);

        p = (double *) malloc ((*taille_v)*sizeof(double));

        if (p == NULL)
        {
            printf("allocation de mémoire impossible");
        }
        else
        {
            /*l'allocation de mémoire a eu lieu*/
            while(!feof(fichVecteur))
            {
                fscanf(fichVecteur,"%lf", &p[i]);
                i++;
            }
        }

        printf("\n");
        fclose(fichVecteur);


    }

    return p;
}

/*
 * fonction : afficheVect
 *
 * Affiche les composantes d'un vecteur de taille taille_v.
 *
 * entrée : *taille_v : pointeur sur la taille du vecteur (int *).
 *          *vect : le vecteur/tableau contenant les composantes à afficher (double *).
 *          *nom : nom de fichier de vecteur (char *).
 *
 * sortie : rien.
 *
 */

void afficheVect(int taille_v, double * vect, char * nom)
{
    /*var locales*/
    int i = 0;

    printf("La taille du vecteur \"%s\" est %d.\n", nom, taille_v);

    for(i = 0;i < taille_v;i++)
    {
        printf("vect[%d] = %f\n", i, vect[i]);
    }

    printf("\n");
}

/*
 * fonction : prodScalaire
 *
 * Calcule le produit de deux vecteurs (vect1 et vect2).
 *
 * entrée : *taille_v1 : pointeur sur la taille du vecteur vect1 (*int).
 *          *taille_v2 : pointeur sur la taille du vecteur vect2 (*int).
 *          *vect1 : vecteur n°1 (double *).
 *          *vect2 : vecteur n°2 (double *).
 *          *prodS : pointeur vers le résultat du produit scalaire entre vect1 et vect2 (double *).
 *          *nom1 : nom du fichier de vect1 (char *).
 *          *nom2 : nom du fichier de vect2 (char *).
 *
 * sortie : rien.
 *
 */

double  prodScalaire(int taille_v1, int taille_v2, double * vect1, double * vect2, char * nom1, char * nom2)
{
    /*var locales*/
    int i;
    double prodS=0;

    if (taille_v1 != taille_v2)
    {
        printf("les ordres sont différents, le produit sclaire n'est pas calculable");
    }
    else
    {
        for(i = 0;i < taille_v1;i++)
        {
            prodS += vect1[i] * vect2[i];
        }

        printf("le produit scalaire de \"%s\" et \"%s\" est %f\n", nom1, nom2, prodS);

    }

    return prodS;
}







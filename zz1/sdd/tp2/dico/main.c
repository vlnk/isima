/* Malrin Vincent
 * Laurent Valentin
 * 4/06/2013
 * DICO MAIN : main.c
 */


/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lifo.h"
#include "arbre.h"
#include "chaine.h"

/*DEFINE*/
#define TMAX 100
#define TRUE 1
#define FALSE 0

int main(int argc, char * argv[])
{
    /*variables globales*/
    abr_t **    arbre = NULL;
    FILE *      f_lecture = NULL;
    char *      chaine = NULL;
    int         compt_ch = 2;
    int         err = FALSE;

    if (argc < 2)
    {
        printf("USAGE : %s <fichier de lecture> <chaines d'insertions>\n",argv[0]);
        fflush(stdout);
    }
    else
    {
        arbre = (abr_t **)malloc(sizeof(abr_t *));
        f_lecture = fopen(argv[1],"r");
        chaine = (char *)malloc(sizeof(char)*TMAX);

        if (! f_lecture)
        {
            printf("Fichier invalide !\n");
        }
        else if (! arbre || ! chaine)
        {
            printf("Allocations impossibles");
        }

        if (arbre && chaine && f_lecture)
        {
            fgets(chaine,TMAX,f_lecture);   /*lecture du fichier texte*/
            printf("\n# Affichage de la notation parenthesee :\n%s\n",chaine);
            err = lecture_abr(chaine,arbre);      /*creation de l'arbre*/

            if (! err)
            {
                if (argc > 2)
                {
                    while (compt_ch < argc)
                    {
                        err = verif_argument(argv[compt_ch]);

                        if (err)
                        {
                            printf("L'argument '%s' n'est pas un mot valide !\n",argv[compt_ch]);
                        }
                        else
                        {
                            insertion_abr(arbre,argv[compt_ch]);    /*insertion*/
                        }
                        compt_ch++;
                    }
                }

                printf("\n# Affichage des mots du dictionnaire :\n");
                affichage_abr(arbre);   /*affichage*/

                /*liberation des ressources*/
                printf("\n# Liberation de l'arbre :\n");
                liberation_abr(arbre);  /*liberation arbre*/
            }
            free(arbre);
            arbre = NULL;
            free(chaine);
            fclose(f_lecture);
        }
    }
    return 0;
}


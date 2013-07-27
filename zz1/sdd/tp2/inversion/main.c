/* Malrin Vincent
 * Laurent Valentin
 * 4/06/2013
 * INVERSION MAIN : main.c
 */

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lifo.h"
#include "fifo.h"

/*DEFINE*/
#define TMAX 100
#define TRUE 1
#define FALSE 0

int main(int argc, char ** argv)
{
    /*variables locales*/
    lifo_t *    p = NULL;       /*pile*/
    int         err = TRUE;     /*erreur d'allocation*/

    /*test des arguments*/
    if (argc < 2)
    {
        printf("USAGE %s <chaine a inverser>\n",argv[0]);
    }
    else
    {
        /*initialisation*/
        p = (lifo_t *)malloc(sizeof(lifo_t));
        err = init_lifo(p,TMAX);

        if (!err && p)
        {
            lecture_pile(p,argv[1]);
            inversion_pile(p);

            /*liberation des ressources*/
            free_lifo(p);
            p = NULL;
        }
    }
    return 0;
}


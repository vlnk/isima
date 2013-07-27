/* Malrin Vincent
 * Laurent Valentin
 * 4/06/2013
 * INVERSION LIFO : lifo.h
 */

/*INCLUDE*/
#include "lifo.h"
#include "fifo.h"

/*DEFINE*/
#define TRUE 1
#define FALSE 0

int empiler(lifo_t * p, type_t val)
{
    /*variables locales*/
    int         err = FALSE;    /*code erreur*/

    /*teste si la lifo est pleine*/
    if (p->t_max > (p->taille + 1))
    {
        p->taille++;    /*on incremente la taille*/
        p->tab[p->taille]=val;  /*insertion de la valeur dans la pile*/
        err=TRUE;   /*on valide le code erreur*/
    }
    return err;
}

type_t depiler(lifo_t * p)
{
    /*variables locales*/
    type_t        val;

    if (!lifo_vide(p))  /*si pile non vide*/
    {
        val=p->tab[p->taille];  /*on recupere la valeur*/
        p->taille--;    /*on decremente la taille*/

    }
    return val;
}

int init_lifo(lifo_t * p, int t_max)
{
    /*variables locales*/
    int         err = TRUE;

    /*initialisation de la lifo*/
    p->t_max = t_max;   /*initialisation de la taille max*/
    p->taille = -1;     /*la taille allouee vaut -1 -> pile vide*/
    p->tab = (type_t*)malloc(t_max*sizeof(type_t));

    if (p->tab)     /*on verifie l'allocation*/
    {
        err = FALSE;
    }
    return err;
}

int lifo_vide(lifo_t* p)
{
    /*variables locales*/
    int ret = FALSE;

    if (p->taille < 0)  /*on verifie l'indice de pile*/
    {
        ret = TRUE;
    }
    return ret;
}

int lifo_pleine(lifo_t* p)
{
    /*variables locales*/
    int ret = FALSE;

    if (p->taille == p->t_max) /*on verifie l'indice de pile*/
    {
        ret = TRUE;
    }
    return ret;
}

void free_lifo(lifo_t* p)
{

    free(p->tab);   /*libere l'espace d'empilage*/
    free(p);
}

void afficher_lifo(lifo_t * p)
{
    /*variables locales*/
    int         cour = 0;               /*parcours de pile*/
    int         taille = p->taille;     /*parcours de l'espace d'empilage*/

    while (cour <= taille)  /*boucle de parcours*/
    {
        printf("%c\n",(p->tab[cour]));
        fflush(stdout);
        cour++;
    }
    printf("\n");
}

void inversion_pile(lifo_t * p)
{
    /*variables locales*/
    fifo_t *        f = NULL;   /*file*/
    type_t          tmp;        /*valeurs a afficher*/
    int             err;        /*erreur*/

    /*initialisation*/
    f = (fifo_t *)malloc(sizeof(fifo_t));
    err = init_fifo(f,p->t_max);

    if (! err)
    {
        printf("Pile a inverser :\n");
        afficher_lifo(p);

        /*parcours de la pile*/
        while (!lifo_vide(p))
        {
            tmp = depiler(p);   /*passage des valeurs*/
            enfiler(f,tmp);
        }

        printf("Etat de la file :\n");
        afficher_fifo(f);

        while (! fifo_vide(f))
        {
            tmp = defiler(f);   /*passage des valeurs*/
            empiler(p,tmp);
        }

        /*liberation de la file*/
        free_fifo(f);
    }

    printf("Pile inversee :\n");
    afficher_lifo(p);
}

void lecture_pile(lifo_t * p, char * ch)
{
    /*variables locales*/
    int         compt = 0;

    while (ch[compt] != '\0')
    {
        empiler(p,ch[compt]);
        compt++;
    }
}


/* Malrin Vincent
 * Laurent Valentin
 * 4/06/2013
 * FIFO : fifo.c
 */


/*INCLUDE*/
#include "fifo.h"

/*DEFINE*/
#define TRUE 1
#define FALSE 0

int enfiler(fifo_t * f, type_t val)
{
    /*variables locale*/
    int         err = TRUE; /*code erreur*/

    /*teste si la fifo est pleine*/
    if (! fifo_pleine(f))
    {
        f->in++;    /*incremente l'indice d'entree*/
        f->tab[f->in % f->t_max] = val;     /*on enfile la valeur*/
        err = FALSE;
    }
    return err;
}

type_t defiler(fifo_t * f)
{
    /*variable locale*/
    type_t        val;  /*valeur cherchee*/

    if (!fifo_vide(f))
    {
        f->out++;   /*incremente l'indice de sortie*/
        val = f->tab[f->out % f->t_max];    /*on defile la valeur*/
    }
    return val;
}

int init_fifo(fifo_t * f, int t_max)
{
    /*variables locales*/
    int         err = TRUE;

    /*initialisation de la fifo*/
    f->t_max = t_max;   /*initialise la taille max*/
    f->tab = (type_t*)malloc(t_max*sizeof(type_t));

    if (f->tab)
    {
        f->in = 0;  /*initialise les indices*/
        f->out = 0;
        err = FALSE;
    }
    return err;
}

int fifo_vide(fifo_t * f)
{
    /*variables locales*/
    int         ret = FALSE;

    if ((f->in - f->out) == 0)  /*file vide -> indice aux meme endroits*/
    {
        ret = TRUE;
    }

    return ret;
}

int fifo_pleine(fifo_t * f)
{
    /*variables locales*/
    int ret = FALSE;

    if ((f->in - f->out) == f->t_max) /*file pleine -> la distance des indice*/
    {                                 /* vaut taille max*/
        ret = TRUE;
    }
    return ret;
}

void free_fifo(fifo_t* f)
{
    free(f->tab);   /*libere l'espace d'enfilage*/
    free(f);
}

void afficher_fifo(fifo_t * f)
{
    /*variables locales*/
    int                 cour = f->out + 1;      /*parcours*/
    int                 nb = f->in - f->out;    /*nb d'elements*/

    while (nb > 0)
    {
        printf("%c\n",f->tab[cour]);
        cour++;     /*avance dans la file*/
        cour = cour % f->t_max;
        nb--;
    }
    printf("\n");
}


/* lifo.c
*/

#include "lifo.h"

/*DEFINE*/
#define TRUE 1
#define FALSE 0

/* FONCTION : empiler
 * Empile un element dans la lifo (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 *          la valeur a inserer (type_t *)
 * sortie : le code d'erreur (int)
 */
int empiler(lifo_t * p, type_t val)
{
    /*variables locales*/
    int         err=FALSE; /*code erreur*/

    /*teste si la lifo est pleine*/
    if (p->t_max > (p->taille + 1))
    {
        p->taille++;
        p->tab[p->taille]=val;
        err=TRUE;
    }
    return err;
}

/* FONCTION : empiler
 * Empile un element dans la lifo (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 *          la valeur a inserer (type_t *)
 * sortie : le code d'erreur (int)
 */
type_t depiler(lifo_t * p)
{
    /*variables locales*/
    type_t        val;

    if (!lifo_vide(p))
    {
        val=p->tab[p->taille];
        p->taille--;

    }
    return val;
}

/* FONCTION : init_lifo
 * Initialise la lifo (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 *          la taille maximale (int)
 * sortie : le code d'erreur (int)
*/
int init_lifo(lifo_t * p, int t_max)
{
    /*variables locales*/
    int         err = TRUE;

    /*initialisation de la lifo*/
    p->t_max = t_max;
    p->taille = -1;
    p->tab = (type_t*)malloc(t_max*sizeof(type_t));

    if (p->tab)
    {
        err = FALSE;
    }
    return err;
}

/* FONCTION : est_vide
 * Vérifie si la lifo est vide (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 * sortie : le code d'erreur (int)
*/
int lifo_vide(lifo_t* p)
{
    /*variables locales*/
    int ret = FALSE;

    if (p->taille < 0)
    {
        ret = TRUE;
    }
    return ret;
}

/* FONCTION : est_pleine
 * Vérifie si la lifo est pleine (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 * sortie : le code d'erreur (int)
*/
int lifo_pleine(lifo_t* p)
{
    /*variables locales*/
    int ret = FALSE;

    if (p->taille == p->t_max)
    {
        ret = TRUE;
    }
    return ret;
}

/* FONCTION : free_lifo
 * Libère la lifo (lifo_t).
 *
 * entree : le pointeur de la lifo (lifo_t)
 * sortie : le code d'erreur (int)
*/
void free_lifo(lifo_t* p)
{
    type_t      tmp;

    while (! lifo_vide(p))
    {
        tmp = depiler(p);
        free(*tmp);
        *tmp = NULL;
    }

    free(p->tab);
    free(p);
    p = NULL;
}

/* FONCTION : afficher_lifo
 * Affiche la pile.
 *
 * entree : le pointeur de la lifo (lifo_t)
 */
void afficher_lifo(lifo_t * p)
{
    /*variables locales*/
    int         cour = 0;
    int         taille = p->taille;

    while (cour <= taille)
    {
        printf("%c",(*p->tab[cour])->val);
        fflush(stdout);
        cour++;
    }
    printf("\n");
}

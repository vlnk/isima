/* Malrin Vincent
 * Laurent Valentin
 * 4/06/2013
 * ARBRE : arbre.c
 */

/*INCLUDE*/
#include "lifo.h"
#include "chaine.h"

/*DEFINE*/
#define TRUE 1
#define FALSE 0
#define TMAX 50

/* FONCTION : construction
 * Construit un noeud à partir de sa valeur (noeud_t).
 *
 * entree : la valeur (char)
 * sortie : le code erreur (int)
 */

int construction(char val, abr_t ** a)
{
    /*variables locales*/
    int         err = TRUE;

    /*allocation memoire*/
    *a = (abr_t *)malloc(sizeof(abr_t));

    /*verification*/
    if (*a)
    {
        err = FALSE;
        (*a)->val = val;        /*insertion de la valeur*/
        (*a)->fils = NULL;      /*initialisation du fils*/
        (*a)->frere = NULL;     /*initialisation du frere*/
    }
    return err;
}

int lecture_abr(char * ch, abr_t ** r)
{
    /*variables locales*/
    lifo_t *        p = (lifo_t *)malloc(sizeof(lifo_t));   /*pile*/
    abr_t **        cour = r;                               /*pointeur de parcours*/
    int             compt = 0;                              /*compteur sur la chaine*/
    int             compt_parenthese = 0;                   /*compteur de parentheses*/
    int             err = FALSE;

    /*initialisation de la pile*/
    err = init_lifo(p,TMAX);

    if (err)
    {
        printf("Erreur : pile non initialisee !\n");
    }

    err = verif_chaine(ch);

    if (ch[compt] != '(' && ! err)   /*verification 1ere parenthese*/
    {
        printf("Parametre incorrect : il manque la 1ere parenthese !\n");
        err = TRUE;
    }
    else if (! err)
    {
        compt_parenthese++; /*on compte la 1ere parenthese*/
        compt++; /*on avance dans la chaine*/

        if (ch[compt] != ')') /*arbre NON vide*/
        {
            construction(ch[compt],cour);   /*initialisation de la racine*/
            compt++;
            *r = *cour; /*initialisation des pointeurs*/
        }
        else    /*arbre vide*/
        {
            cour = NULL;
            compt_parenthese--;
        }

        /*boucle*/
        while ((compt_parenthese > 0) && (! err))
        {
            switch(ch[compt])
            {
                case '(':
                    empiler(p,cour); /*on empile l'adr*/
                    compt++; /*on avance dans la chaine*/
                    compt_parenthese++; /*on incremente le compteur de parentheses*/
                    cour = &(*cour)->fils; /*on deplace cour sur le fils*/
                    construction(ch[compt],cour); /*on cree le fils*/
                    compt++; /*on avance dans la chaine*/
                    break;

                case ')':
                    if (compt_parenthese > 0)
                    cour = depiler(p); /*on depile l'adr*/
                    compt++; /*on avance dans la chaine*/
                    compt_parenthese--; /*on decremente le compteur de parentheses*/
                    break;

                case ',':
                    compt++; /*on avance dans la chaine*/
                    break;

                default:
                    cour = &(*cour)->frere; /*on deplace cour sur le frere*/
                    construction(ch[compt],cour); /*on construit une nouvelle cellule*/
                    compt++; /*on avance dans la chaine*/
            }
        }
    }
    free_lifo(p);    /*libération des ressources*/

    return err;
}

int liberation_abr(abr_t ** r)
{
    lifo_t *        p = (lifo_t *)malloc(sizeof(lifo_t));   /*pile*/
    abr_t **        cour = r;                               /*pointeur de parcours*/
    abr_t **        tmp = NULL;                             /*pointeur de liberation*/
    int             fin = FALSE;                            /*fin de parcours (pile vide)*/
    int             err = FALSE;                            /*erreur d'allocation*/

    err = init_lifo(p,TMAX);    /*initialisation de la pile*/

    if (err)    /*verification d'allocation*/
    {
        printf("Erreur : pile non initialisee !");
    }

    while ((! fin))     /*boucle de parcours*/
    {
        while (*cour)   /*parcours postfixe*/
        {
            empiler(p,cour);    /*si il a un fils : on empile l'adr*/
            cour = &(*cour)->fils;
        }
        if (! lifo_vide(p))
        {
            cour = depiler(p);      /*feuille : on depile les cellule parcourues*/
            tmp = cour;

            if ((*cour)->frere)     /*si il a un frere : on empile l'adr*/
            {
                empiler(p,cour);
                cour = &(*cour)->frere;
            }
            else
            {
                cour = &(*cour)->frere;     /*sinon on libere la memoire*/
                printf("free(%c)\n",(*tmp)->val);  /*affichage pour tests*/
                fflush(stdout);
                free(*tmp);
                *tmp = NULL;
            }
        }
        else
        {
            fin = TRUE;     /*fin de parcours : pile vide*/
        }
    }

    free_lifo(p); /*liberation des ressources*/

    return err;
}

int affichage_abr(abr_t ** r)
{
    lifo_t *        p = (lifo_t *)malloc(sizeof(lifo_t));   /*pile*/
    abr_t **        cour = r;                               /*pointeur de parcours*/
    int             fin = FALSE;                            /*fin de parcours*/
    int             err = FALSE;                            /*erreur d'allocation*/

    err = init_lifo(p,TMAX);    /*initialisation de la pile*/

    if (err) /*verification de l'allocation*/
    {
        printf("Erreur : pile non initialisee !");
    }

    while ((! fin) && (! err))  /*boucle de parcours*/
    {
        while (*cour) /*parcours en profondeur*/
        {
            empiler(p,cour);

            /*verifie si on parcours une majuscule*/
            if (((*cour)->val > 64) && ((*cour)->val < 91))
            {
                afficher_lifo(p);   /*si majuscule : on affiche le mot parcouru*/
            }
            cour = &(*cour)->fils;  /*on avance dans la structure (mot suivant)*/
        }
        if (! lifo_vide(p))     /*on depile jusqu'au frere suivant*/
        {
            cour = depiler(p);
            cour = &(*cour)->frere;
        }
        else    /*fin de parcours : pile vide*/
        {
            fin = TRUE;
        }
    }
    free_lifo(p);    /*liberation des ressources*/

    return err;
}

int insertion_abr(abr_t ** r, char * ch)
{
    abr_t **        prec = r;       /*pointeur sur precedent (parcours)*/
    int             err = FALSE;    /*erreur d'allocation*/
    int             i = 0;
    abr_t *         tmp = NULL;     /*valeur temporaire (insertion)*/
    char            char_ch;        /*carctere pointe dans l'abr*/
    char            char_abr;       /*caractere pointe dans la chaine*/

    while(ch[i] != '\0')
    {
        if (*prec)
        {
            char_ch = ch[i] % 32; /*initialisation des caracteres parcourus*/
            char_abr = (*prec)->val % 32;

            if (char_abr == char_ch)    /*si les caracteres sont les mêmes...*/
            {
                if(ch[i+1] == '\0')     /*gestion dernière lettre*/
                {
                    (*prec)->val=toupper(ch[i]);
                }
                else
                {
                    prec = &(*prec)->fils;  /*...on continue le parcours (fils)*/
                }
                i++;
            }
            else if (char_abr < char_ch) /* si le car mot > car abr...*/
            {
                prec = &(*prec)->frere;     /*...on continue le parcours (frere)*/
            }
            else
            {
                tmp = *prec;    /*...a la place de la cellule courante...*/

                if(ch[i+1] == '\0') /*gestion dernière lettre*/
                {
                    construction(toupper(ch[i]),prec);
                }
                else
                {
                    construction(ch[i],prec);
                }

                (*prec)->frere = tmp;   /*...qui devient le frere*/
                prec = &(*prec)->fils;
                i++;
            }
        }
        else
        {
            if(ch[i+1] == '\0') /*gestion dernière lettre*/
            {
                construction(toupper(ch[i]),prec);
            }
            else
            {
                construction(ch[i],prec);   /*on insere le reste du mot*/
            }

            prec = &(*prec)->fils;
            i++;
        }
    }
    return err;
}


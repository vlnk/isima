/* Malrin Vincent
 * Laurent Valentin
 * 4/06/2013
 * CHAINE : chaine.c
 */

/*INCLUDE*/
#include "chaine.h"

/*DEFINE*/
#define FALSE 0
#define TRUE 1

int verif_chaine(char * ch)
{
    /*variables locales*/
    int         compt = 0;              /*compteur dans la chaine*/
    int         compt_parenthese = 0;   /*compteur de parenthese*/
    int         err = FALSE;            /*erreur*/
    int         abr_vide = FALSE;       /*cas particuler : l'abr vide*/

    /*initialisation de la chaine*/
    ch[strlen(ch) - 1] = '\0';

    if (ch[compt] == '(' && ch[compt + 1] == ')' && ch[compt + 2] == '\0')
    {
        abr_vide = TRUE; /*verifie si c'est l'arbre vide*/
    }

    while (ch[compt + 1] != '\0' && ! err && ! abr_vide)
    {
        switch(ch[compt])
        {
            case '(': /*si le caractere est '(' -> une lettre ou '('*/
                if(isalpha(ch[compt + 1]) || ch[compt + 1] == '(')
                {
                    compt_parenthese++;
                    compt++;
                }
                else
                {
                    err = TRUE;
                }
                break;
            case ')': /*si le caractere est ')' -> une lettre ou ')'*/
                if(isalpha(ch[compt + 1]) || ch[compt + 1] == ')')
                {
                    compt_parenthese--;
                    compt++;
                }
                else
                {
                    err = TRUE;
                }
                break;
            case ',': /*si le caractere est '(' -> une lettre*/
                if(isalpha(ch[compt + 1]))
                {
                    compt++;
                }
                else
                {
                    err = TRUE;
                }
                break;
            default: /*sinon c'est une lettre non suivie d'une autre lettre*/
                if(isalpha(ch[compt]))
                {
                    if(ch[compt + 1] == ')' || ch[compt + 1] == '(' || ch[compt + 1] == ',')
                    {
                        compt++;
                    }
                    else
                    {
                        err = TRUE;
                    }
                }
                else /*n'est pas une lettre*/
                {
                    err = TRUE;
                }
        }
    }

    if (ch[compt] == ')')
    {
        compt_parenthese--;
    }

    if (compt_parenthese != 0) /*les parentheses '(' et ')' doivent etre de nbr egal*/
    {
        err = TRUE;
    }

    if (err)
    {
        printf("Ecriture parenthesee incorrecte !\n");
    }

    return err;
}

int verif_argument(char * ch)
{
    /*variables locales*/
    int         compt = 0;              /*compteur dans la chaine*/
    int         err = FALSE;            /*erreur*/

    while(ch[compt] != '\0' && ! err)
    {
        if (! isalpha(ch[compt]))
        {
            err = TRUE;
        }
        compt++;
    }
    return err;
}

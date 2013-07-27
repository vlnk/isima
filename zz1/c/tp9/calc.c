/* calc.c
 *
 * Evaluation et calcul d'une expression saisie pas l'utilisateur.
 *
 * Version 0.2
 * Auteur : Valentin
 * Date : 20/01/13
 *
 * Compilation : gcc calc_txt.c -o calculatrice -Wall -Wextra -g -ansi -pedantic -lm
 */

/*EN TETE*/
#include "calc_txt.h"

/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*PROGRAMME PRINCIPAL*/
int main(int argc, char** argv)
{
    /*variables locales*/
    int             verif_intervalle = FALSE;
    char            chaine[TMAX];
    intervalle      inter;
    double          cour;
    int             menu = TRUE;

    /*affichage menu*/
    printf("#---------------------------------------------------------#\n");
    printf("#                      CALCULATRICE                       #\n");
    printf("#                                                         #\n");
    printf("# Lorsque la valeur de l'expression est remplacée par 'x',#\n");
    printf("# on considère l'ensemble des résultats sur un intervalle #\n");
    printf("# [a,b] avec un pas 'delta'.                              #\n");
    printf("# exemple : exp(x),a,b,delta                              #\n");
    printf("#                                                         #\n");
    printf("# Attention : La priorité des opérateurs n'est pas gérée. #\n");
    printf("# Le parenthésage des expressions non plus.               #\n");
    printf("# exemple : exp(x) * (4 + 7) -> erreur                    #\n");
    printf("#                                                         #\n");
    printf("# Pour quitter -> exit                                    #\n");
    printf("#---------------------------------------------------------#\n");

    /*saisie de l'expression*/

    while(menu)
	{
		printf("\n? > ");
	    fflush(stdin);
	    fgets(chaine, TMAX, stdin);
	    chaine[strlen(chaine) - 1] = '\0'; /*Supprime le saut de ligne en fin de saisie*/

        if(strcmp(chaine,"exit") == 0)
        {
            menu = FALSE;
        }
        else if(verifIntervalle(chaine,&verif_intervalle))
        {
            /*initialisation*/
            inter = lectureIntervalle(chaine);
            cour = inter.inf;

            while(cour <= inter.sup)
            {
                printf("Resultat pour [x = %f] : %f\n", cour, evalIntervalle(chaine,cour,&verif_intervalle));
                cour = cour + inter.delta;
            }
        }
        else
        {
            printf("Resultat : %f\n", eval(chaine,&verif_intervalle));
        }

        verif_intervalle = FALSE;
	}

    return 0;
}



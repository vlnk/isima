/* calc_txt.h
 *
 * Evaluation et calcul d'une expression saisie pas l'utilisateur.
 *
 * Version TEXTE : 0.2
 * Auteur : Valentin
 * Date : 20/01/13
 *
 * Compilation : gcc calc_txt.c -o calculatrice -Wall -Wextra -g -ansi -pedantic -lm
 */

#include "calc_txt.h"
#include "fonctions.h"

/* fonction : IDENTIFICATIONFONCTION
 *
 * renvoie l'indice du tableau de fonction correspondant à l'expression lue, -1 sinon
 *
 * en entrée : l'expression à interpréter (char*)
 *             le tableau de fonction (const char**)
 * en sortie : l'indice du tableau (int)
 */
int identificationFonction(char* expression,const char** tab_fct)
{
    /*variables locales*/
    int               r = -1;
    int               i;

    /*initialisation de l'indice de parcours*/
    i=0;

    /*parcours du tableau*/
    while(tab_fct[i] != NULL)
    {
        /*vérification de l'expression*/
        if (strcmp(tab_fct[i],expression) == 0)
        {
            r = i;
        }
        i++;
    }

    /*affichage de l'indice (debug)*/
    /*printf("idFct(%s) : %d\n", expression,r);*/

    /*renvoi de l'indice correspondant*/
    return r;
}

/* fonction : IDENTIFICATIONOPERATION
 *
 * renvoie l'indice du tableau de fonction correspondant à l'expression lue, -1 sinon
 *
 * en entrée : l'expression à interpréter (char*)
 *             le tableau de fonction (const char**)
 * en sortie : l'indice du tableau (int)
 */
int identificationOperation(char expression,const char* tab_op)
{
    /*variables locales*/
    int               r = -1;
    int               i;

    /*initialisation de l'indice de parcours*/
    i=0;

    /*parcours du tableau*/
    while(tab_op[i] != '\0')
    {
        /*vérification de l'expression*/
        if (tab_op[i] == expression)
        {
            r = i;
        }
        i++;
    }

    /*affichage de l'indice (debug)*/
    /*printf("idOp(%c) : %d\n", expression,r);*/
    /*printf("%d",r);*/

    /*renvoi de l'indice correspondant*/
    return r;
}

/* fonction : EVAL
 *
 * renvoie le résultat du calcul de l'expression évaluée.
 *
 * en entrée : la valeur saisie (double)
 *             le pointeur sur l'entier d'activation de l'évaluation d'intervalles.
 * en sortie : la valeur de l'expression évaluée (double)
 */

double eval(char* expr, int* verif_intervalle)
{
	double          r = 0;
	fonction        expr_fct;   /*Découpage d'un texte de type fonction*/
	operation       expr_op;    /*Découpage d'un texte de type operation*/
	int             indice;     /*Indice de l'operation ou de la fonction identifiee*/
	double          val1;       /*Stocke un calcul temporaire*/
	double          val2;       /*idem*/
    const char      *tab_fct[]={"id","sin","cos","exp","log",NULL};
    const char      tab_op[]={'+','-','*','/','\0'};

	indice = 0;

    /*si c'est une fonction -> lecture du nom et des paramètres
     *                         identification de la fonction
     *                         evaluation de fonction(paramètre)*/
	if(verifFonction(expr))
	{
		expr_fct = lectureFonction(expr,verif_intervalle);
        /*printf("fonction : %s\n", expr_fct.fct);
        printf("parametre : %s\n", expr_fct.param);*/
		indice = identificationFonction(expr_fct.fct,tab_fct);
		
		if(indice == -1)
		{
			printf("Fonction inconnue (%s)\n", expr_fct.fct);
		}
		else
		{
			if(verifNum(expr_fct.param))
			{
				val1 = atof(expr_fct.param);
			}
			else
			{
				val1 = eval(expr_fct.param,verif_intervalle);
			}
			r = evalFonction(val1, indice);
    		}
		
            /*libération des ressources*/
		    free(expr_fct.fct);
            free(expr_fct.param);
	}

    /*si c'est une operation -> lecture de l'operateur et des paramètres
     *                          identification de l'operateur
     *                          evaluation de l'operation (param1 op param2*/

	else
	{
		expr_op = lectureOperation(expr);
        /*printf("exp1 : %s\n", expr_op.exp1);
        printf("op : %c\n", expr_op.op);
        printf("exp1 : %s\n", expr_op.exp2);*/
		indice = identificationOperation(expr_op.op,tab_op);
		
		if(indice == -1)
		{
			printf("Operation inconnue (%c)\n",expr_op.op);
		}
		else
		{
			if(verifNum(expr_op.exp1))
            {
				val1 = atof(expr_op.exp1);
			}
            else
            {
				val1 = eval(expr_op.exp1,verif_intervalle);
			}
			
			if(verifNum(expr_op.exp2))
            {
				val2 = atof(expr_op.exp2);
			}
            else
            {
				val2 = eval(expr_op.exp2,verif_intervalle);
			}
			
			r = evalOperation(val1, val2, indice);
		}
		
		/*libération des ressources*/
		free(expr_op.exp1);
        free(expr_op.exp2);
	}
	
	/*printf("[%s] = %f\n", expr, r);*/
	
	return(r);
}

/* fonction : EVALINTERVALLE
 *
 * renvoie le résultat du calcul de l'expression évaluée.
 *
 * en entrée : la valeur saisie (double)
 *             le pointeur sur l'entier d'activation de l'évaluation d'intervalles.
 * en sortie : la valeur de l'expression évaluée (double)
 */

double evalIntervalle(char* expr,double cour,int* verif_intervalle)
{
	double          r = 0;
	fonction        expr_fct;   /*Découpage d'un texte de type fonction*/
	operation       expr_op;    /*Découpage d'un texte de type operation*/
	int             indice;     /*Indice de l'operation ou de la fonction identifiee*/
	double          val1;       /*Stocke un calcul temporaire*/
	double          val2;       /*idem*/
    const char      *tab_fct[]={"id","sin","cos","exp","log",NULL};
    const char      tab_op[]={'+','-','*','/','\0'};

	indice = 0;

    if(! *verif_intervalle)
    {
        printf("Expression non définie !");
    }
    else
    {

        /*si c'est une fonction -> lecture du nom et des paramètres
        *                         identification de la fonction
        *                         evaluation de fonction(paramètre)*/
	    if(verifFonction(expr))
	    {
		    expr_fct = lectureFonction(expr,verif_intervalle);
            /*printf("fonction : %s\n", expr_fct.fct);
            printf("parametre : %s\n", expr_fct.param);*/
		    indice = identificationFonction(expr_fct.fct,tab_fct);
		
		    if(indice == -1)
		    {
			    printf("Fonction inconnue (%s)\n", expr_fct.fct);
		    }
		    else
		    {
			    if(verifNum(expr_fct.param))
			    {
				    val1 = atof(expr_fct.param);
			    }
			    else if(strcmp(expr_fct.param,"x") == 0)
                {
                    val1 = cour;
                }
                else
			    {
				    val1 = evalIntervalle(expr_fct.param,cour,verif_intervalle);
			    }
			    r = evalFonction(val1, indice);
    		}
		
            /*libération des ressources*/
		    free(expr_fct.fct);
            free(expr_fct.param);
	    }

        /*si c'est une operation -> lecture de l'operateur et des paramètres
        *                          identification de l'operateur
        *                          evaluation de l'operation (param1 op param2*/

	    else
	    {
		    expr_op = lectureOperation(expr);
            /*printf("exp1 : %s\n", expr_op.exp1);
            printf("op : %c\n", expr_op.op);
            printf("exp2 : %s\n", expr_op.exp2);*/
		    indice = identificationOperation(expr_op.op,tab_op);
		
		    if(indice == -1)
		    {
			    printf("Operation inconnue (%c)\n",expr_op.op);
		    }
		    else
		    {
			    if(verifNum(expr_op.exp1))
                {
				    val1 = atof(expr_op.exp1);
			    }
                else if(strcmp(expr_op.exp1,"x") == 0)
                {
                    val1 = cour;
                }
                else
                {
                    val1 = evalIntervalle(expr_op.exp1,cour,verif_intervalle);
		        }
			
		        if(verifNum(expr_op.exp2))
                {
			        val2 = atof(expr_op.exp2);
			    }
                else if(strcmp(expr_op.exp2,"x") == 0)
                {
                   val2 = cour;
                }
                else
                {
			        val2 = evalIntervalle(expr_op.exp2,cour,verif_intervalle);
		        }
		
                r = evalOperation(val1, val2, indice);
            }

            /*libération des ressources*/
		    free(expr_op.exp1);
            free(expr_op.exp2);
	    }
			
	    /*printf("[%s] = %f\n", expr, r);*/
    }
	return(r);
}

/* fonction : EVALFONCTION
 *
 * renvoie la valeur de la fonction évaluée avec une valeur saisie "fonction(valeur)"
 *
 * en entrée : la valeur saisie (double)
 *             l'indice du tableau correspondant à la fonction (int)
 * en sortie : la valeur de l'expression évaluée (double)
 */
double evalFonction(double valeur, int i)
{
    /*varaibles locales -> tableau de fonctions*/
    double          (*tabpf[])(double)={id,sin,cos,exp,log};

    return tabpf[i](valeur);
}

/* fonction : EVALOPERATION
 *
 * lit une chaine de caractère et renvoie un tableau contenant la fonction et la valeur associée
 *
 * en entrée : la chaine saisie (char*)
 *             le tableau de chaine (char**)
 * en sortie : le tableau contenant les deux chaines (char**)
 */

double evalOperation(double val1, double val2, int i)
{
    /*variables locales*/
    double      val;

    switch(i)
    {
        /*addition*/
        case 0 :
            val =  val1 + val2;
            break;
        /*soustraction*/
        case 1 :
            val =  val1 - val2;
            break;
        /*multiplication*/
        case 2 :
            val =  val1 * val2;
            break;
        /*division*/
        case 3 :
            val =  val1 / val2;
            break;
        default :
            val = -1;
            printf("Operateur inconnu !\n");
    }

    return val;
}

/* fonction : LECTUREOPERATION
 *
 * lit une chaine de caractère et stocke dans une structure l'opperateur et ses valeurs associées
 *
 * en entrée : la chaine saisie (char*)
 * en sortie : l'opérateur et ses valeurs associées dans une structure operation.
 *             ex : "4 + 3" -> ("4", '+', "3")
 */
operation lectureOperation(char* chaine)
{
    /*variables locales*/
    int         i = 0,j = 0,k = 0;      /*compteurs*/
    char        verif_alloc = 2;
    char *      exp1 = NULL;
    char *      exp2 = NULL;
    char        op = '\0';
    operation   r;

    /*initialisation*/
    r.exp1 = NULL;
    r.exp2 = NULL;

    /* i se déplace dans la chaine de caractères chaine
     * j se déplace dans la chaine de caractères nomfct
     * k compte le nombre de paranthèses*/

    exp1 = malloc(sizeof(char)*(strlen(chaine) + 1));
    exp2 = malloc(sizeof(char)*(strlen(chaine) + 1));

    /*vérification de l'allocation de nomfct*/
    if (exp1 == NULL)
    {
        /*l'allocation a échouée*/
        printf("Allocation de mémoire impossible\n");
        verif_alloc--;
    }

    /*vérification de l'allocation de paramfct*/
    if (exp2 == NULL)
    {
        /*l'allocation a échouée*/
        printf("Allocation de mémoire impossible\n");
        verif_alloc--;
    }

    if (verif_alloc == 2)
    {
        r.exp1 = exp1;
    	r.exp2 = exp2;

        /*sscanf(chaine, "%s %c %s", exp1, &op, exp2);*/
	    if(strlen(chaine) < 3)
	    {
		    printf("Operation inconnue !(%s)\n", chaine);
	    }
	    else
	    {
            /*copie de l'expression 1*/
		    while((chaine[i+2] != '\0') && ((k != 0) || !((chaine[i] == ' ') && !(isalnum(chaine[i+1])) && (chaine[i+2] == ' '))))
		    {
			    if(chaine[i] == ')')
			    {
				    k--;
			    }
			    else if(chaine[i] == '(')
			    {
				    k++;
			    }
			    exp1[j] = chaine[i];
			    i++;
			    j++;
		    }

            /*ajout du dernier caractère*/
		    exp1[j] = '\0';

		    if(chaine[i+2] == '\0')
		    {
			    printf("Expression erronee !\n");
		    }
		    else
		    {
                /*copie de l'opérateur*/
			    op = chaine[i+1];

                /*initialisation des compteurs*/
                j = 0;
			    i = i + 3; /*on avance jusqu'à l'expression après l'opérateur*/

                /*copie de l'expression 2*/
			    while((chaine[i] != '\0') && (chaine[i] != ','))
			    {
				    exp2[j] = chaine[i];
				    j++;
				    i++;
			    }

                /*ajout du dernier caractère*/
			    exp2[j] = '\0';
		    }
        }
    }
	
	r.op = op;
	return(r);
}

/* fonction : LECTUREFONCTION
 *
 * Récupère le nom d'une fonction et son paramètre à partir d'une chaine de caractère.
 *
 * en entrée : la chaine saisie (char*)
 *             le pointeur sur l'entier d'activation de l'évaluation d'intervalles.
 * en sortie : le nom et le paramètre de la fonction sous la structure fonction.
 *             ex : "cos(x)" -> ("cos","x")
 */

fonction lectureFonction(char* chaine,int* verif_intervalle)
{
	fonction    r;
	char *      nom_fct;
	char *      param_fct;
    int         verif_alloc = 2;
	int         i = 0, j = 0, k = 0;    /*compteurs*/

    /* i se déplace dans la chaine de caractères chaine
     * j se déplace dans la chaine de caractères nomfct
     * k compte le nombre de paranthèses*/
	
    /*initialisation*/
    r.fct = NULL;
    r.param = NULL;

    /*allocations*/
    nom_fct = malloc(sizeof(char)*(strlen(chaine) + 1));
    param_fct = malloc( sizeof( char)*(strlen(chaine) + 1));

    /*vérification de l'allocation de nomfct*/
    if (nom_fct == NULL)
    {
        /*l'allocation a échouée*/
        printf("Allocation de mémoire impossible\n");
        verif_alloc--;
    }

    /*vérification de l'allocation de paramfct*/
    if (param_fct == NULL)
    {
        /*l'allocation a échouée*/
        printf("Allocation de mémoire impossible\n");
        verif_alloc--;
    }

    if (verif_alloc == 2)
    {
        r.fct = nom_fct;
    	r.param = param_fct;
        if(strcmp(chaine,"x") == 0)
        {
            if(! *verif_intervalle)
            {
                printf("Expression non définie !\n");
            }
            else
            {
                strcpy(nom_fct,"id");
                strcpy(param_fct, chaine);
            }
        }
        /*valeur numérique -> id(x)*/
        if(verifNum(chaine))
	    {
		    strcpy(nom_fct, "id");
		    strcpy(param_fct, chaine);
	    }
	    else
	    {
            /*copie du nom de la fonction*/
		    while((chaine[i] != '\0') && (chaine[i] != '('))
		    {
			    nom_fct[j] = chaine[i];
			    i++;
                j++;
		    }
		    nom_fct[i] = '\0';
		
		    if(chaine[i] != '\0')
            {
			    i++;
            }

		    j=0;
			
            /*copie des paramètres*/
		    while((chaine[i] != '\0') && ((k != 0) || ((chaine[i] != ')'))))
		    {
			    if(chaine[i] == '(')
			    {
				    k++;
			    }
			    else if(chaine[i] == ')')
			    {
				    k--;
			    }
                param_fct[j] = chaine[i];
			    i++;
			    j++;
		    }
		    param_fct[j]  = '\0';
	    }
    }
	return(r);
}

/* fonction : LECTUREINTERVALLE
 *
 * Récupère les bornes d'un intervalle et son pas delta à partir d'une chaine de caractère.
 *
 * en entrée : la chaine saisie (char*)
 * en sortie : les bornes et le pas de l'intervalle sous la structure intervalle.
 *             ex : "expression,a,b,delta" -> ("a","b","delta")
 */
intervalle lectureIntervalle(char * chaine)
{
    /*variables locales*/
    intervalle      r;
    int             i = 0, j = 0;
    char *          borne_sup;
    char *          borne_inf;
    char *          delta;
    double          tmp;
    int             verif_alloc = 3;

    /* i se déplace dans la chaine de caractères chaine
     * j se déplace dans la chaine de caractères borne
     * k compte le nombre de paranthèses*/
	
    /*initialisation*/
    r.sup = 0;
    r.inf = 0;
    r.delta = 0;

    /*allocation de borne_sup, borne_inf et delta*/
    borne_sup = malloc(sizeof(char)*(strlen(chaine) + 1));
    borne_inf = malloc(sizeof(char)*(strlen(chaine) + 1));
    delta = malloc(sizeof(char)*(strlen(chaine) + 1));

    /*vérification de l'allocation de borne_sup*/
    if (borne_sup == NULL)
    {
        /*l'allocation a échouée*/
        printf("Allocation de mémoire impossible\n");
        verif_alloc--;
    }

    /*vérification de l'allocation de borne_inf*/
    if (borne_inf == NULL)
    {
        /*l'allocation a échouée*/
        printf("Allocation de mémoire impossible\n");
        verif_alloc--;
    }

    /*vérification de l'allocation de delta*/
    if (delta == NULL)
    {
        /*l'allocation a échouée*/
        printf("Allocation de mémoire impossible\n");
        verif_alloc--;
    }

    if (verif_alloc == 3)
    {
        /*valeur numérique -> id(x)*/
		while((chaine[i] != '\0') && (chaine[i] != ','))
		{
			i++;
		}
		
		if(chaine[i] == '\0')
        {
		    printf("Aucun intervalle n'est défini\n");
        }
        else
        {
		    i++;
			
            /*copie d'une borne*/
		    while((chaine[i] != '\0') && ((chaine[i] != ',')))
		    {
                borne_inf[j] = chaine[i];
			    i++;
			    j++;
		    }
		    borne_inf[j]  = '\0';

            if(chaine[i] == '\0')
            {
		        printf("Aucun intervalle n'est défini\n");
            }
            else
            {
		        i++;
                j = 0;
			
                /*copie d'une borne*/
		        while((chaine[i] != '\0') && ((chaine[i] != ',')))
                {
                    borne_sup[j] = chaine[i];
                    i++;
                    j++;
                }
                borne_sup[j]  = '\0';

                /*valeur de delta par defaut*/
                if(chaine[i] == '\0')
                {
                    strcpy(delta,"1");
                }
                else
                {
                    i++;
                    j = 0;

                    /*copie de delta*/
                    while((chaine[i] != '\0') && ((chaine[i] != ',')))
                    {
                        delta[j] = chaine[i];
                        i++;
                        j++;
                    }
                    delta[j]  = '\0';
                }
            }
        }

        /*vérification des bornes*/
        if ((verifNum(borne_sup)) && (verifNum(borne_inf)) && (verifNum(delta)))
        {
            r.sup = atof(borne_sup);
            r.inf = atof(borne_inf);
            r.delta = atof(delta);

            if (r.sup < r.inf)
            {
                tmp = r.sup;
                r.sup = r.inf;
                r.inf = tmp;
            }
        }
        else
        {
            printf("Intervalle mal défini\n");
        }
    }

    /*libération des ressources*/
    free(borne_sup);
    free(borne_inf);
    free(delta);

     /*printf("sup : %f\n", r.sup);
     printf("inf : %f\n", r.inf);
     printf("delta : %f\n", r.delta);*/

    return r;
}

/* fonction : VERIFFONCTION
 *
 * Vérifie si l'expression est une fonction.
 *
 * en entrée : la chaine saisie (char*)
 * en sortie : VRAI(int) si c'est une fonction, FAUX(int) sinon.
 */

int verifFonction(char * chaine)
{
    /*varibales locales*/
	int         r = TRUE;       /*sortie*/
	int         i = 0,j = 0;    /*compteurs*/

    /* i se déplace dans la chaine de caractères
     * j compte le nombre de parenthèses*/
	

	if((!verifNum(chaine)) && (strcmp(chaine,"x") != 0))
	{
        /*verification du nom de la fonction*/
		while((chaine[i] != '\0') && (isalpha(chaine[i]))) /*isalpha vérifie si chaine[i] est dans l'alphabet*/
		{
			i++;
		}
		if(chaine[i] != '(')
		{
			r = FALSE;
		}
		else
		{
			j ++;
			i ++;

            /*comptage des parentheses -> verif des paramètres*/
			while((chaine[i] != '\0') && (j != 0))
			{
				if(chaine[i] == ')')
				{
					j--;
				}
				else if(chaine[i] == '(')
				{
					j++;
				}
				i++;
			}
			if((chaine[i] != '\0') && (chaine[i] != ','))
			{
				r = FALSE;
			}
		}
	}
	return(r);
}

/* fonction : VERIFNUM
 *
 * Vérifie si l'expression est une valeur numérique.
 *
 * en entrée : la chaine saisie (char*)
 * en sortie : VRAI(int) si c'est une valeur numérique, FAUX(int) sinon.
 */

int verifNum(char* chaine)
{
    /*variables locales*/
	int         r = TRUE;       /*sortie*/
    int         i = 0;          /*compteur*/
	
    /* i se déplace dans la chaine de caractères*/

	while((chaine[i] != '\0') && (r))
	{
		if ((!isdigit(chaine[i])) && (chaine[i] != '.'))/*isdigit vérifie si chaine[i] est un chiffre (digits)*/
        {
            r = FALSE;
        }
		i++;
	}
    /*printf("%s -> %d\n",chaine,r);*/
	return(r);
}

/* fonction : VERIFINTERVALLE
 *
 * Vérifie si l'expression est une valeur numérique.
 *
 * en entrée : la chaine saisie (char*)
 *             le pointeur sur l'entier d'activation de l'évaluation d'intervalles.
 * en sortie : VRAI(int) si il y a un intervalle de déclaré, FAUX(int) sinon.
 */

int verifIntervalle(char * chaine, int * verif_intervalle)
{
    /*variables locales*/
    int         r = FALSE;
    int         i = 0;

    /* i se déplace dans la chaine de caractères*/
    while((chaine[i] != '\0') && (!r))
	{
		if (chaine[i] == ',')
        {
            r = TRUE;
        }
		i++;
	}
    /*printf("Intervalle %s -> %d\n",chaine,r);*/
	*verif_intervalle = r;

    return r;
}

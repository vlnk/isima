/* Nom : login2.c
 *
 * Auteur : valentin.laurent@poste.isima.fr (G11)
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAILLE 20

/*structures*/
 typedef struct login 
    {
        char nom_de_login[TAILLE];
        char mot_de_pass[TAILLE];
        char nom_de_la_machine[100];
        int utilisation_machine;
        struct login * suivant;
    } login_t;

/*d�clarations*/
void inserTete (login_t ** ptete, login_t ** ajout);
void inserFin (login_t * ptete, login_t ** ajout);
void initialiser(login_t * ptete);
void affichage(login_t * ptete);
void liberation(login_t ** ptete);
void saisie (login_t * ptete);
void inserMilieu (login_t * ptete, login_t ** ajout);
int verifMotDePasse(char * mdp);
char * genereMotDePasse(int germe);
void supprimer (login_t ** ptete);


/* Fonction : main
 *
 * Menu d'ajout ou de modification des comptes.
 *
 * En entr�e : rien
 *
 * En sortie : rien
 */

int main(int argc, char** argv)
{
    /*variables locales*/
    login_t * ptete;
    login_t * ajout;
    int confirm = 1;
    char demande_ajout_t;
    char demande_position_t;

    /*allocation du pointeur vers le premier �lement de la structure*/
    ptete = (login_t *) malloc (sizeof(login_t));
    (*ptete).suivant = NULL;

    /*initialisation des �l�ments*/
    initialiser(ptete);

    while (confirm == 1)
    {
        /*demande/choix entre la modif ou la cr�ation d'un compte*/
        printf("Voulez-vous ajouter, supprimer un compte ou ne rien faire ? (a/s/f) ");
        fflush(stdout);
        scanf("%s%*c",&demande_ajout_t);

        if ((demande_ajout_t == 'a') && (strcmp("vide", (*ptete).nom_de_login) == 0))
        {
            /*ajout d'un compte sur un �l�ment vide*/
            saisie(ptete);
        }

        else if (demande_ajout_t == 'a')
        {
            /*ajout d'un compte par cr�ation d'un �l�ment*/
            ajout = (login_t *) malloc(sizeof(login_t));

            if (ajout == NULL)
            {
                printf("Erreur d'allocation");
            }
            else
            {
                /*saisie du compte*/
                saisie(ajout);

                /*ajout du compte au gestionnaire*/
                printf("Voulez-vous ajouter le compte en fin, au milieu ou au debut (f/n/d) ? ");
                fflush(stdout);
                scanf("%c%*c", &demande_position_t);

                if (demande_position_t == 'f')
                {
                    inserFin(ptete,&ajout);
                }
                else if (demande_position_t == 'd')
                {
                    inserTete(&ptete,&ajout);
                }
                else if (demande_position_t == 'm')
                {
                    inserMilieu(ptete,&ajout);
                }
            }
        }
        else if (demande_ajout_t == 's')
        {
            supprimer(&ptete);
        }
        else
        {
            confirm = 0;
        }
    }

    /*affichage des �lements*/
    affichage(ptete);

    /*lib�ration de la m�moire allou�e*/
    liberation(&ptete);

	return 0;
}

/* Fonction : inserTete
 *
 * Ins�re un �l�ment (un compte) en t�te de la liste chain�e.
 *
 * En entr�e : **ptete : le pointeur sur le pointeur de la liste chain�e de compte.
 *             **ajout : le pointeur sur le pointeur de l'�l�ment � ajouter.
 *
 * En sortie : rien
 */

void inserTete (login_t ** ptete, login_t ** ajout)
{
    /*ajout d'un �l�ment en t�te de liste et
     * d�placement du pointeur vers cet �l�ment*/
    (**ajout).suivant = *ptete;
    *ptete = *ajout;

}

/* Fonction : inserFin
 *
 * Ins�re un �l�ment (un compte) en fin de la liste chain�e.
 *
 * En entr�e : *ptete : le pointeur de la liste chain�e de compte.
 *             **ajout : le pointeur sur le pointeur de l'�l�ment � ajouter.
 *
 * En sortie : rien
 */


void inserFin (login_t * ptete, login_t ** ajoutFin)
{
    /*variables locales*/
    login_t * cour;

    cour = ptete;

    /*parcours de la liste chain�e*/
    while ((*cour).suivant != NULL)
    {
        cour = (*cour).suivant;
    }

    /*ajout d'un �l�ment en fin de liste*/
    (**ajoutFin).suivant = NULL;
    (*cour).suivant = *ajoutFin;
}

/* Fonction : inserMilieur
 *
 * Ins�re un �l�ment (un compte) au milieu de la liste chain�e.
 *
 * En entr�e : *ptete : le pointeur de la liste chain�e de compte.
 *             **ajout : le pointeur sur le pointeur de l'�l�ment � ajouter.
 *
 * En sortie : rien
 */

void inserMilieu (login_t * ptete, login_t ** ajout)
{
    /*variables locales*/
    login_t * cour;
    login_t * tmp;
    char login_avant[TAILLE];

    cour = ptete;

    printf("Veuillez saisir le login avant le compte a inserer : ");
    fflush(stdout);
    scanf("%s%*c", login_avant);

    while ((strcmp((*cour).nom_de_login,login_avant) != 0) & (cour != NULL))
    {
        cour = (*cour).suivant;
    }

    if (cour == NULL)
    {
        printf("Le login n'existe pas !\n");
    }
    else
    {
        tmp = (*cour).suivant;
        (*cour).suivant = *ajout;
        (**ajout).suivant = tmp;
    }
}

/* Fonction : supprimer
 *
 * Supprime un �l�ment (un compte) de la liste chain�e.
 *
 * En entr�e : *ptete : le pointeur de la liste chain�e de compte.
 *
 * En sortie : rien
 */

void supprimer(login_t ** ptete)
{
    /*variables locales*/
    login_t * cour = *ptete;
    login_t * prec;
    login_t * tmp;
    char login_suppr[TAILLE];

     printf("Veuillez saisir le login du compte a supprimer : ");
    fflush(stdout);
    scanf("%s%*c", login_suppr);

    if (strcmp((*cour).nom_de_login,login_suppr) != 0)
    {
        (*ptete) = (*cour).suivant;
        free(cour);
    }
    else
    {
        prec = *ptete;
        cour = (**ptete).suivant;

        while ((cour != NULL) & (strcmp((*cour).nom_de_login,login_suppr) != 0))
        {
            prec = cour;
            cour = (*cour).suivant;
        }

        if (cour == NULL)
        {
            printf("Le login n'existe pas !\n");
        }
        else
        {
            tmp = (*cour).suivant;
            free(cour);
            (*prec).suivant = tmp;
        }
    }
}


/* Fonction : initialiser
 *
 * Initialise les �l�ments (comptes) de la liste chain�e.
 *
 * En entr�e : *ptete : le pointeur sur la liste chain�e.
 *
 * En sortie : rien
 */

void initialiser(login_t * ptete)
{
    /*variables locales*/
    login_t * cour;
    cour = ptete;

    /*parcours de la liste chain�e*/
    while ((cour) != NULL)
    {
        /*initialisation de tous les �l�ments � vide*/
        strcpy((*cour).nom_de_login,"vide");
        strcpy((*cour).mot_de_pass,"vide");
        strcpy((*cour).nom_de_la_machine,"vide");
        (*cour).utilisation_machine = 10;

        cour = (*cour).suivant;
    }
}


/* Fonction : affichage
 *
 * Affiche chaque �l�ment (compte) de la liste chain�e.
 *
 * En entr�e : *ptete : le pointeur sur la liste chain�e.
 *
 * En sortie : rien.
 */

void affichage(login_t * ptete)
{
    /*variables locales*/
    login_t * cour;
    cour = ptete;

    printf("\n");

    /*parcours de la liste chain�e*/
    while ((cour) != NULL)
    {
        printf("Compte de %s\n", (*cour).nom_de_login);
        printf("Mot de passe : %s\n", (*cour).mot_de_pass);
        printf("Nom de la machine : %s\n", (*cour).nom_de_la_machine);
        printf("Taux d'utilisation : %i\n", (*cour).utilisation_machine);
        printf("\n");

        cour = (*cour).suivant;
    }
}


/* Fonction : liberation
 *
 * Lib�re la m�moire allou�e pour la liste chain�e.
 *
 * En entr�e : le pointeur pointant sur le pointeur de la liste chain�e.
 *
 * En sortie :  rien
 */

void liberation(login_t ** ptete)
{
    /*variales locales*/
    login_t * cour;
    cour = *ptete;

    /*parcours de la liste chain�e*/
    while ((cour) != NULL)
    {
        *ptete = (*cour).suivant;

        /*lib�ration de l'�l�ment visit�*/
        free(cour);
        cour = *ptete;
    }
}


/* Fonction : saisie
 *
 * Permet la saisie d'un compte c'est-�-dire les modifications des diff�rents param�tres de la structure login_t.
 *
 * En entr�e : le pointeur de la liste chain�e de compte.
 *
 * En sortie : rien
 */

void saisie (login_t * ptete)
{
    /*variables locales*/
    char nom_de_login_t[100];
    char mot_de_pass_t[100];
    int utilisation_machine_t = 10;
    int verifMDP = 0;

    /*saisie du login et v�rification de la taille*/
    printf("\nNom de login ? ");
    fflush(stdout);
    scanf("%s%*c", nom_de_login_t);

     while (strlen(nom_de_login_t) > 20)
     {
        printf("Erreur : nom de login trop long !");
        printf("\nNom de login ? ");
        fflush(stdout);
        scanf("%s%*c", nom_de_login_t);
     }

    strcpy((*ptete).nom_de_login, nom_de_login_t);

    /*saisie du mot de passe et v�rification*/
    printf("\nMot de passe ? ");
    fflush(stdout);
    scanf("%s%*c", mot_de_pass_t);
    verifMDP = verifMotDePasse(mot_de_pass_t);

    while (verifMDP != 1)
    {
        printf("\nMot de passe ? ");
        fflush(stdout);
        scanf("%s%*c", mot_de_pass_t);
        verifMDP = verifMotDePasse(mot_de_pass_t);
    }

    strcpy((*ptete).mot_de_pass, mot_de_pass_t);

    /*saisie du nom de la machine et v�rification*/
    printf("\nNom de la machine ? ");
    fflush(stdout);
    scanf("%s%*c", (*ptete).nom_de_la_machine);

    /*saisie de taux d'utilisation et v�rification*/
    printf("\nUtilisation de la machine ? ");
    fflush(stdout);
    scanf("%d%*c", &utilisation_machine_t);

    while ((utilisation_machine_t < 0) || (utilisation_machine_t > 10))
    {
        printf("Erreur : taux d'utilisation incorrect !");
        printf("\nUtilisation de la machine ? ");
        fflush(stdout);
        scanf("%d%*c", &utilisation_machine_t);
    }

    (*ptete).utilisation_machine = utilisation_machine_t;

    printf("\n");

}


/* Fonction : verifMotDePasse
 *
 * V�rifie le mot de passe saisit par l'utilisateur selon le cahier des charges.
 *
 * En entr�e : *ptete : le pointeur de la liste chain�e.
 *
 * En sortie : une valeur de v�rification (0 = TRUE, 1 = FALSE)
 *
 * Cahier des charges : * 8 caract�res minimums
 *                      * 20 caract�res maximums (limite de la variable TAILLE)
 *                      * contient au moins un caract�re en majuscule
 *                      * contient au moins un chiffre
 *                      * contient au moins un caract�re diff�rent de l'alphabet (ou chiffre)
 */

int verifMotDePasse(char * mdp)
{
    /*variables locales*/
    int indMaj = 0;
    int indInt = 0;
    int indDif = 0;
    int tailleMDP = 0;
    int r = 0;
    int i = 0;
    char cour = mdp[0];

    tailleMDP = strlen(mdp);

    /*v�rification de la taille*/
    if ((tailleMDP > 20) | (tailleMDP < 8))
    {
        printf("Taille incorrecte !");
    }
    else
    {
        /*parcours du mot de passe*/
        while(cour != '\0')
        {
            /*v�rification des majuscules*/
            if ((cour > 64) & (cour < 91))
            {
                indMaj = 1;
            }

            /*v�rification des chiffres*/
            if ((cour > 47) & (cour < 58))
            {
                indInt = 1;
            }

            /*v�rification des caract�res sp�ciaux*/
            if (((cour >= 0) & (cour < 48)) | ((cour > 57) & (cour < 65)) | ((cour > 90) & (cour < 97)) | (cour > 122))
            {
                indDif = 1;
            }

            i++;
            cour = mdp[i];
        }

        /*v�rification globale*/
        if ((indMaj == 1) & (indInt == 1) & (indDif == 1))
        {
            printf("Mot de passe correct !\n");
            r = 1;
        }

        /*affichage des erreurs*/
        if (indMaj == 0)
        {
            printf("Il n'y a pas de majuscule ! ");
        }

        if (indInt == 0)
        {
            printf("Il n'y a pas de chiffre ! ");
        }

        if (indDif == 0)
        {
            printf("Il n'y a pas de carctere special ! ");
        }
    }

    return r;
}

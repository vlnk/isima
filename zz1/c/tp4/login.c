/* login.c
 *
 * auteur : Laurent Valentin
 * date : 19/10/12
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAILLE 8

/*structures*/
 typedef struct login
    {
        char nom_de_login[TAILLE];
        char mot_de_pass[TAILLE];
        char nom_de_la_machine[100];
        int utilisation_machine;
    } login_t;

/*déclarations*/
void saisie(int nb_log, login_t * tab_log);
void affichage(int nb_log, login_t * tab_log);
void initialiser(int nb_log, login_t * tab_log);

int main(int argc, char ** argv)
{
    /*variables locales*/
    int nb_log = 0;
    login_t * tab_log;
    char saisi_confirm;

    printf("Veuillez entrer le nombre de compte(s) a creer : ");
    fflush(stdout);
    scanf("%d%*c", &nb_log);

    tab_log = (login_t *) malloc (nb_log*sizeof(login_t));

    if (tab_log == NULL)
    {
        printf("Allocation impossible");
    }
    else
    {
        initialiser(nb_log, tab_log);

        do
        {
            printf("Voulez-vous modifier une compte ? (y/n) ");
            fflush(stdout);
            scanf("%c%*c", &saisi_confirm);
            printf("\n");

            if (saisi_confirm == 'y')
            {
                saisie(nb_log, tab_log);
            }

        } while (saisi_confirm != 'n');

        affichage(nb_log, tab_log);
    }

    free(tab_log);
    return 0;
}

void saisie (int nb_log, login_t * tab_log)
{
    /*variables locales*/
    int numero_compte;
    char nom_de_login_t[100];
    char mot_de_pass_t[100];
    int utilisation_machine_t = 10;

    printf("Numero de compte ? ");
    fflush(stdout);
    scanf("%d%*c", &numero_compte);
    numero_compte--;

    while ((numero_compte < 0) || (numero_compte >= nb_log))
    {
        printf("Erreur : aucun compte ne correspond !");
        printf("\nNumero de compte ? ");
        fflush(stdout);
        scanf("%d%*c", &numero_compte);
        numero_compte--;
    }

    printf("\nNom de login ? ");
    fflush(stdout);
    scanf("%s%*c", nom_de_login_t);

    while (strlen(nom_de_login_t) > 8)
    {
        printf("Erreur : nom de login trop long !");
        printf("\nNom de login ? ");
        fflush(stdout);
        scanf("%s%*c", nom_de_login_t);
    }

    strcpy(tab_log[numero_compte].nom_de_login, nom_de_login_t);

    printf("\nMot de pass ? ");
    fflush(stdout);
    scanf("%s%*c", mot_de_pass_t);

    while (strlen(mot_de_pass_t) > 8)
    {
        printf("Erreur : mot de pass trop long !");
        printf("\nMot de pass ? ");
        fflush(stdout);
        scanf("%s%*c", mot_de_pass_t);
    }

    strcpy(tab_log[numero_compte].mot_de_pass, mot_de_pass_t);

    printf("\nNom de la machine ? ");
    fflush(stdout);
    scanf("%s%*c", tab_log[numero_compte].nom_de_la_machine);

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

    tab_log[numero_compte].utilisation_machine = utilisation_machine_t;

    printf("\n");

}


void affichage(int nb_log, login_t * tab_log)
{
    /*variables locales*/
    int i;

    for(i=0; i<nb_log; i++)
    {
        printf("Compte %i\n", i+1);
        printf("Login : %s\n", tab_log[i].nom_de_login);
        printf("Mot de passe : %s\n", tab_log[i].mot_de_pass);
        printf("Nom de machine : %s\n", tab_log[i].nom_de_la_machine);
        printf("Utilisation de la machine : %d\n", tab_log[i].utilisation_machine);
        printf("\n");
    }
}

void initialiser(int nb_log, login_t * tab_log)
{
    /*variables locales*/
    int i;

    for(i=0; i<nb_log; i++)
    {
        strcpy(tab_log[i].nom_de_login, "vide");
        strcpy(tab_log[i].mot_de_pass, "vide");
        strcpy(tab_log[i].nom_de_la_machine, "vide");
        tab_log[i].utilisation_machine = 10;
    }
}



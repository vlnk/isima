/* TITRE : ABINAIRE
 * FICHIER : abinaire.c
 *
 * AUTEUR : Valentin Laurent
 * DATE : 24/01/13
 *
 * COMPILATION : gcc tp10.c -o tp10 -Wall -Wextra -g -ansi -pedantic -lm
 */

/* EN TETE */
#include "abinaire_txt.h"

/* PROGRAMME PRINCIPAL
 *
 * Lit un fichier source *.c et copie les lignes "#", les prototypes de fonctions et les commentaires du fichier source dans un autre fichier.
 *
 * ENTRÉE : argv1 (fichier *) fichier binaire.
 * SORTIE : Rien.
 */

int main(int argc, char ** argv)
{
    /*variables locales*/
    noeud_t *       pracine = NULL;
    int             choix = 1;
    char            choix_r;
    char            nom_t[M];
    char            prenom_t[M];
    char            nom_fic[M];

    /*allocation de la racine*/
    pracine = (noeud_t *) malloc(sizeof(noeud_t));

    /*vérification de l'allocation*/
    if (pracine == NULL)
    {
        printf("Allocation impossible !");
    }
    else
    {
        /*initialisation de pracine*/
        (*pracine).nom = NULL;
        (*pracine).prenom = NULL;
        (*pracine).d = NULL;
        (*pracine).g = NULL;

        while(choix != 0)
        {
            affiche_menu();
            printf("Que voulez-vous faire ? ");
            fflush(stdout);
            scanf("%d%*c",&choix);
            printf("\n");

            switch (choix)
            {
                case 0 :
                    printf("#----------Au revoir !----------#\n");
                    break;

                case 2 :
                    printf("#-----Mise à Jour/Insertion-----#\n");
                    miseAJour(&pracine,saisie());
                    break;

                case 1 :
                    printf("#-----------Affichage-----------#\n");
                    affichage(pracine,0);
                    break;

                case 3 :
                    printf("#-----------Suppression---------#\n");
                    suppression(&pracine,saisie());
                    break;

                case 4 :
                    printf("#-----------Recherche-----------#\n");
                    printf("Voulez-vous effectuer votre recherche par [N]om ou par [P]renom ? ");
                    fflush(stdout);
                    scanf("%c%*c",&choix_r);

                    if(choix_r == 'N')
                    {
                        /*Saisie du nom*/
                        printf("Veuillez saisir le nom à rechercher : ");
                        fflush(stdout);
                        fgets(nom_t, M, stdin);
                        nom_t[strlen(nom_t) - 1] = '\0'; /*Supprime le saut de ligne en fin de saisie*/

                        rechercheNom(pracine,nom_t);
                    }
                    else if(choix_r == 'P')
                    {
                        /*Saisie du prenom*/
                        printf("Veuillez saisir le prenom à rechercher : ");
                        fflush(stdout);
                        fgets(prenom_t, M, stdin);
                        prenom_t[strlen(prenom_t) - 1] = '\0'; /*Supprime le saut de ligne en fin de saisie*/

                        recherchePrenom(pracine,prenom_t);
                    }
                    break;

                case 5 :
                    printf("#-----------Ecriture------------#\n");

                    /*saisie du nom de fichier*/
                    printf("Veuillez saisir le nom du fichier .txt [ecriture.txt] : ");
                    fflush(stdout);
                    fgets(nom_fic, M, stdin);
                    nom_fic[strlen(nom_fic) - 1] = '\0'; /*Supprime le saut de ligne en fin de saisie*/

                    efface(nom_fic);
                    ecriture(pracine,nom_fic);
                    break;

                case 6 :
                    printf("#------------Lecture------------#\n");

                    /*saisie du nom de fichier*/
                    printf("Veuillez saisir le nom du fichier .txt [lecture.txt] : ");
                    fflush(stdout);
                    fgets(nom_fic, M, stdin);
                    nom_fic[strlen(nom_fic) - 1] = '\0'; /*Supprime le saut de ligne en fin de saisie*/

                    lecture(&pracine,nom_fic);
                    break;

                case 7 :
                    printf("#----------Liberation-----------#\n");
                    liberation(&pracine);
                    break;


                default :
                    printf("Choix non reconnu !\n");
                    break;
            }
        }
    }
    liberation(&pracine);

    free(pracine);
    pracine = NULL;

    return 0;
}


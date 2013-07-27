/* Malrin Vincent
 * Laurent Valentin
 * 25/03/2013
 * MAIN : agenda.c
 * Creer une structure de données en mémoire à partir d'un fichier texte.
 *
 * EXEMPLE : 201321110TP de SDD
 *           chaine_sem[6]chaine_act[3 + 10]
 *
 * entree : choix du menu (int)
 *          nom du fichier texte (char *)
 *          arguments : date (char *) ou nom de fichier d'ecriture (char *)
 *
 * USAGE : agenda <choix menu> <fichier de lecture> <argument>
 */

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

int main (int argc, char ** argv)
{
    /*variables locales*/
    semaine_t *         p_sem = NULL;

    semaine_t **        rech_sem = NULL;
    action_t **         rech_act = NULL;

    bilatere_t *        p_bil = NULL;

    motif_t *           p_motif = NULL; /*liste de motifs*/
    int                 compteur_motif = 0;

    char                chaine_sem[7]; /*copies des informations*/
    char                chaine_act[4];
    char                dechet[100];
    char                libelle[11];

    int                 choix = 1; /*choix par defaut*/
    int                 erreur = 0;

    if (argc < 3) /*vérification arguments*/
    {
        printf("USAGE : %s <choix menu> <fichier de lecture> <argument>\n",argv[0]);
        /*affichage du menu et saisie du choix*/
        Menu(0,&choix);
    }
    else
    {
        /*initialisation du choix*/
        choix = atoi(argv[1]);

        /*lecture du fichier*/
        erreur = Lecture(&p_sem,argv[2]);

        /*initialisation des chaines*/
        chaine_sem[6] = '\0';
        chaine_act[3] = '\0';

        while (choix != 0)
        {

            switch(choix)
            {
                case 0 :
                    break;

                case 1 :
                    /*affichage*/
                    Affichage(p_sem);
                    break;

                case 2 :
                    /*recherche par date*/
                    if ((argc >= 4) && (strlen(argv[3]) == 9)) /*vérification arguments*/
                    {
                        /*copie de la date à rechercher*/
                        sscanf(argv[3],"%6c%3c%*c",chaine_sem,chaine_act);

                        /*recherche dans l'agenda*/
                        rech_sem = RechercheSem(&p_sem,chaine_sem);

                        if (*rech_sem != NULL)
                        {
                            rech_act = RechercheAct(&(**rech_sem).action_s,chaine_act);
                        }

                        if ((*rech_sem != NULL) && (*rech_act != NULL))
                        {
                            sscanf((**rech_act).chaine_act,"%3c%10c",dechet,libelle);
                            libelle[10] = '\0';
                            printf("LIBELLE RECHERCHEE : %s\n",libelle);
                        }
                        else if ((*rech_sem == NULL) || (*rech_act == NULL)) /*affichage de l'erreur*/
                        {
                            printf("Aucune page n'est trouvee\n");
                        }
                    }
                    else
                    {
                        printf("Erreur : date incomplete\n");
                    }
                    break;

                case 3 :
                    /*suppression par date*/
                    if ((argc >= 4) && (strlen(argv[3]) == 9)) /*vérification arguments*/
                    {
                        /*copie de la date à supprimer*/
                        sscanf(argv[3],"%6c%3c%*c",chaine_sem,chaine_act);

                        /*recherche dans l'agenda*/
                        rech_sem = RechercheSem(&p_sem,chaine_sem);

                        if (*rech_sem != NULL)
                        {
                            rech_act = RechercheAct(&(**rech_sem).action_s,chaine_act);
                        }

                        if ((*rech_sem != NULL) && (*rech_act != NULL))
                        {
                            sscanf((**rech_act).chaine_act,"%3c%10c",dechet,libelle);
                            libelle[10] = '\0';
                            printf("LIBELLE SUPPRIMEE : %s\n\n",libelle);

                            SuppressionAct(rech_act);

                            if ((**rech_sem).action_s == NULL)
                            {
                                SuppressionSem(rech_sem);
                            }

                            Affichage(p_sem);
                        }
                        else if ((*rech_sem == NULL) || (*rech_act == NULL)) /*affichage de l'erreur*/
                        {
                            printf("Aucune page n'est supprimee\n");
                        }
                    }
                    else
                    {
                        printf("Erreur : date incomplete\n");
                    }
                    break;

                case 4 :
                    /*ecriture*/
                    if (argc >= 4) /*vérification arguments*/
                    {
                        Ecriture(p_sem,argv[3]);
                    }
                    break;

                case 5 :
                    /*transformation en liste bilatère*/
                    p_bil = (bilatere_t *) malloc(sizeof(bilatere_t));
                    strcpy((*p_bil).chaine_sem,"\0");
                    (*p_bil).action_s = NULL;
                    (*p_bil).suiv = p_bil;
                    (*p_bil).prec = p_bil;

                    if (p_bil) /*vérification de l'allocation*/
                    {
                        TransfoBilatere(&p_sem,p_bil);
                        LiberationBil(p_bil);
                        free(p_bil);
                    }
                    break;

                case 6 :
                    /*recherche de motif*/
                    p_motif = (motif_t *) malloc(sizeof(motif_t)*TMAX);

                    if ((argc >= 4) && (strlen(argv[3]) < 11) && p_motif) /*vérification arguments*/
                    {
                        /*copie du motif à rechercher*/
                        sscanf(argv[3],"%s%*c",libelle);

                        compteur_motif = RechercheMotif(p_sem,p_motif,libelle);
                        AffichageMotif(p_motif,compteur_motif);
                        free(p_motif);
                    }
                    else
                    {
                        printf("Erreur : motif incorrect\n");
                    }
                    break;

                default :
                    printf("Choix non identifie !\n");
                    break;
            }

            /*reinitialisation des pointeurs*/
            rech_sem = NULL;
            rech_act = NULL;

            /*reinitialisation du choix (sinon boucle infinie)*/
            /*Menu(1,&choix);*/
            choix = 0;
        }

        /*libération des ressources*/
        Liberation(p_sem);

        printf("Fin du programme\n");
    }

    return 0;
}

/* TITRE : ABINAIRE_TXT
 * FICHIER : abinaire_txt.c
 *
 * AUTEUR : Valentin Laurent
 * DATE : 24/01/13
 *
 * ATTENTION : L'écriture se fait dans un fichier .txt, ecriture.txt est
 * prévu à cet effet.
 */

/* EN TETE */
#include "abinaire_txt.h"

/*SOUS-PROGRAMMES*/

/* AFFICHAGE
 *
 * Parcours un arbre binaire et affiche ses informations.
 *
 * ENTRÉE : r(struct noeud) un noeud de l'arbre.
 * SORTIE : Rien.
 */
void affichage (noeud_t * r, int prof)
{
    if ((r != NULL) && ((*r).nom != NULL))
    {
        /*variables locales*/
        int             i = 0;

        /*affichage du nom*/
        for (i=0; i<prof; i++)
        {
            if (i != prof - 1)
            {
                printf("|    ");
            }
            else
            {
                printf("|--> ");
            }
        }
        printf("[nom : %s]\n",(*r).nom);

        /*affichage du prenom*/
        for (i=0; i<prof; i++)
        {
            printf("|    ");
        }
        printf("[prenom : %s]\n",(*r).prenom);

        /*affichage du login*/
        for (i=0; i<prof; i++)
        {
            printf("|    ");
        }
        printf("[login : %s]\n",(*r).login);

        /*affichage du mot de passe*/
        for (i=0; i<prof; i++)
        {
            printf("|    ");
        }
        printf("[mot de passe : %s]\n",(*r).mdp);

        /*recursivité sur les noeuds fils*/
        if ((*r).g)
        {
            affichage((*r).g,prof + 1);
        }
        if ((*r).d)
        {
            affichage((*r).d,prof + 1);
        }
    }
    else
    {
        printf("Il n'y a aucune fiche !\n");
    }
}

/* RECHERCHE
 *
 * Effectue une recherche sur le graphe pour l'insertion.
 *
 * ENTRÉE : pracine(** noeud_t) le pointeur sur la racine de l'arbre.
 *          saisie_t(* noeud_t) pointeur sur le noeud à rechercher.
 * SORTIE : prec(** noeud) adresse du noeud rechercher ou correspondant au tri des fiches.
 */

noeud_t ** recherche (noeud_t ** pracine, noeud_t * saisie_t)
{
    /*variables locales*/
    char *          nom_t = (*saisie_t).nom;
    char *          prenom_t = (*saisie_t).prenom;
    noeud_t **      cour = pracine;
    noeud_t **      prec = cour;
    int             comp_nom = 0;       /*comparateur de noms*/
    int             comp_prenom = 0;    /*comparateur de prenom*/

    /*boucle de recherche*/
    while ((cour != NULL) && (*cour != NULL) && ((**cour).nom != NULL))
    {
        prec = cour;
        comp_nom = strcmp((**cour).nom,nom_t);

        /*si les noms sont les mêmes...*/
        if (comp_nom == 0)
        {
            /*...on regarde le champs des prenoms*/
            if ((**cour).prenom != NULL)
            {
                /*initialisation du comparateur de prenom*/
                comp_prenom = strcmp((**cour).prenom,prenom_t);
                if (comp_prenom == 0)
                {
                    cour = NULL;
                }
                /*si les prenoms sont les mêmes*/
                else if (comp_prenom > 0)
                {
                    cour = &(**cour).g;
                }
                else
                {
                    cour = &(**cour).d;
                }
            }
        }
        else if (comp_nom > 0)
        {
            cour = &(**cour).g;
        }
        else
        {
            cour = &(**cour).d;
        }
    }

    return prec;
}


/* LIBERATION
 *
 * Parcourt un arbre binaire et libère l'espace alloué.
 *
 * ENTRÉE : r(struct noeud) un noeud de l'arbre.
 * SORTIE : Rien.
 */

void liberation (noeud_t ** pracine)
{
    /*variable locale*/
    noeud_t **      cour = pracine;

    if ((cour != NULL) && (*cour != NULL) && ((**cour).nom != NULL))
    {
        if ((**cour).g != NULL)
        {
            liberation(&(**cour).g);
        }
        if ((**cour).d != NULL)
        {
            liberation(&(**cour).d);
        }

        free((**cour).nom);
        free((**cour).prenom);
        free((**cour).login);
        free((**cour).mdp);

    }
}

/* SAISIE
 *
 * Crée un noeud contenant les informations saisies.
 *
 * ENTRÉE : Rien.
 * SORTIE : Rien.
 */
noeud_t * saisie ()
{
    /*variables locales*/
    noeud_t *       saisie_t;
    char            nom[M];
    char            prenom[M];
    char            login[M];
    char            mdp[M];

    /*allocation de la fiche*/
    saisie_t = (noeud_t *) malloc(sizeof(noeud_t));

    /*vérification de l'allocation*/
    if (saisie_t == NULL)
    {
        printf("L'alloction a échoué !\n");
    }

    /*l'allocation a réussi*/
    else
    {
        /*initialisation de saisie_t*/
        (*saisie_t).nom = NULL;
        (*saisie_t).prenom = NULL;
        (*saisie_t).d = NULL;
        (*saisie_t).g = NULL;

        /*saisie du nom*/
        printf("Quel nom ? ");
        fflush(stdout);
        fgets(nom, M, stdin);
        nom[strlen(nom) - 1] = '\0'; /*Supprime le saut de ligne en fin de saisie*/

        /*saisie du prenom*/
        printf("Quel prénom ? ");
        fflush(stdout);
        fgets(prenom, M, stdin);
        prenom[strlen(prenom) - 1] = '\0'; /*Supprime le saut de ligne en fin de saisie*/

        /*saisie du prenom*/
        printf("Quel login ? ");
        fflush(stdout);
        fgets(login, M, stdin);
        login[strlen(login) - 1] = '\0'; /*Supprime le saut de ligne en fin de saisie*/

        /*saisie du prenom*/
        printf("Quel mot de passe ? ");
        fflush(stdout);
        fgets(mdp, M, stdin);
        mdp[strlen(mdp) - 1] = '\0'; /*Supprime le saut de ligne en fin de saisie*/

        if ((strcmp(prenom,"\0") != 0) && (strcmp(nom,"\0") != 0))
        {
            /*allocation des informations*/
            (*saisie_t).nom = (char *) malloc(sizeof(char)*M);
            (*saisie_t).prenom = (char *) malloc(sizeof(char)*M);
            (*saisie_t).login = (char *) malloc(sizeof(char)*M);
            (*saisie_t).mdp = (char *) malloc(sizeof(char)*M);

            /*verification de l'allocation*/
            if (((*saisie_t).nom == NULL) || ((*saisie_t).prenom == NULL) || ((*saisie_t).login == NULL) || ((*saisie_t).mdp == NULL))
            {
                printf("Allocation impossible !\n");
            }
            else
            {
                /*copie des informations dans la structure*/
                strcpy((*saisie_t).nom,nom);
                strcpy((*saisie_t).prenom,prenom);
                strcpy((*saisie_t).login,login);
                strcpy((*saisie_t).mdp,mdp);
                (*saisie_t).g = NULL;
                (*saisie_t).d = NULL;
            }
        }
        else
        {
            printf("Fiche incomplète !\n");
            saisie_t = NULL;
        }
    }

    return saisie_t;
}

/* INSERER
 *
 * Parcourt un arbre binaire et affiche ses informations.
 *
 * ENTRÉE : pracine(noeud **) l'adresse du pointeur de la racine.
 *          saisie_t(noeud_t *) pointeur sur le noeud à insérer.
 * SORTIE : Rien.
 */
void inserer (noeud_t ** pracine, noeud_t * saisie_t)
{
    /*variables locales*/
    noeud_t **      cour;
    int             comp_nom = 0;
    int             comp_prenom = 0;

    if (saisie_t != NULL)
    {
        /*insertion triée de la fiche*/
        cour = recherche(pracine,saisie_t);

        /*cas de base : aucune fiche n'est encore insérée*/
        if (((*cour) == NULL) || ((**cour).nom == NULL))
        {
            *cour = saisie_t;
        }
        else
        {
            comp_nom = strcmp((**cour).nom,(*saisie_t).nom);
            comp_prenom = strcmp((**cour).prenom,(*saisie_t).prenom);

            if (comp_nom == 0)
            {
                if (comp_prenom == 0)
                {
                    printf("Cet utilisateur est déjà inscrit !\n");
                    cour = NULL;
                }
                else if (comp_prenom > 0)
                {
                    cour = &(**cour).g;
                }
                else
                {
                    cour = &(**cour).d;
                }
            }
            else if (comp_nom > 0)
            {
                cour = &(**cour).g;
            }
            else
            {
                cour = &(**cour).d;
            }

            /*vérifie si la recherche n'a pas fourni d'erreurs*/
            if (cour != NULL)
            {
                *cour = saisie_t;
            }
        }
    }
}

/* SUPPRESSION
 *
 * Supprime un noeud correspondant aux coordonnées saisies.
 *
 * ENTRÉE : pracine(noeud **) l'adresse du pointeur de la racine.
 *          saisie_t(noeud_t *) pointeur sur le noeud à supprimer.
 * SORTIE : Rien.
 */
void suppression (noeud_t ** pracine, noeud_t * saisie_t)
{
    /*variables locales*/
    noeud_t **      cour;
    noeud_t *       dracine;
    noeud_t *       gracine;

    if (saisie_t != NULL)
    {
        /*insertion triée de la fiche*/
        cour = recherche(pracine,saisie_t);
        free(saisie_t);

        if ((*cour != NULL) && ((**cour).nom != NULL))
        {
            /*vérifie si la recherche n'a pas fourni d'erreurs*/
            if ((strcmp((**cour).nom,(*saisie_t).nom) == 0) && (strcmp((**cour).prenom,(*saisie_t).prenom) == 0))
            {
                /*racines des arbres à réinsérer*/
                dracine = (**cour).d;
                gracine = (**cour).g;

                /*libération et suppression du noeud ciblé*/
                free((**cour).nom);
                free((**cour).prenom);
                free((**cour).login);
                free((**cour).mdp);
                free(*cour);
                *cour = NULL;

                /*insertion des fils*/
                supprAux(pracine,dracine);
                supprAux(pracine,gracine);
            }
            else
            {
                printf("Cette fiche n'existe pas !\n");
            }
        }
    }
}

/* SUPPRAUX
 *
 * Réinsère les fils du noeud supprimé dans SUPPRESSION.
 *
 * ENTRÉE : pracine(noeud **) l'adresse du pointeur de la racine.
 *          r (noeud_t *) pointeur sur le noeud à réinsérer.
 * SORTIE : Rien.
 */
void supprAux (noeud_t ** pracine, noeud_t * r)
{
    if (r != NULL)
    {
        inserer(pracine,r);
        supprAux(pracine,(*r).d);
        supprAux(pracine,(*r).g);
    }
}

/* MISEAJOUR
 *
 * Supprime un noeud correspondant aux coordonnées saisies.
 *
 * ENTRÉE : pracine(noeud **) l'adresse du pointeur de la racine.
 *          saisie_t(noeud_t *) pointeur sur le noeud à supprimer.
 * SORTIE : Rien.
 */
void miseAJour (noeud_t ** pracine, noeud_t * saisie_t)
{
    /*variables locales*/
    noeud_t **      cour;
    char            choix_t;

    if (saisie_t != NULL)
    {
        /*insertion triée de la fiche*/
        cour = recherche(pracine,saisie_t);

        /*cas de base : aucune fiche n'est encore insérée*/
        if (((*cour) == NULL) || ((**cour).nom == NULL) || ((strcmp((**cour).nom,(*saisie_t).nom)) != 0))
        {
            printf("La fiche à mettre à jour n'existe pas !\n");
            printf("Voulez-vous en insérer une nouvelle ? ([O]ui/[N]on) ");
            fflush(stdout);
            scanf("%c%*c",&choix_t);

            if ((choix_t == 'O') || (choix_t == 'o'))
            {
                inserer(pracine,saisie_t);
            }
        }
        else
        {
            strcpy((**cour).nom,(*saisie_t).nom);
            strcpy((**cour).prenom,(*saisie_t).prenom);
            strcpy((**cour).login,(*saisie_t).login);
            strcpy((**cour).mdp,(*saisie_t).mdp);
        }
    }
}

/* RECHERCHENOM
 *
 * Effectue une recherche sur le graphe par nom et affiche les comptes correspondants.
 *
 * ENTRÉE : pracine(** noeud_t) le pointeur sur la racine de l'arbre.
 *          saisie_t(* noeud_t) pointeur sur le noeud à rechercher.
 * SORTIE : prec(** noeud) adresse du noeud rechercher ou correspondant au tri des fiches.
 */
void rechercheNom (noeud_t * r,char * nom_t)
{
    /*variables locales*/
    int             comp_nom = 0;       /*comparateur de noms*/

    /*boucle de recherche*/
    if ((r != NULL) && ((*r).nom != NULL))
    {
        comp_nom = strcmp((*r).nom,nom_t);

        /*si les noms sont les mêmes...*/
        if (comp_nom == 0)
        {
            printf("[nom : %s]\n",(*r).nom);
            printf("[prenom : %s]\n",(*r).prenom);
            printf("[login : %s]\n",(*r).login);
            printf("[mdp : %s]\n",(*r).mdp);
            printf("\n");
        }

        rechercheNom((*r).d,nom_t);
        rechercheNom((*r).g,nom_t);
    }
}

/* RECHERCHEPRENOM
 *
 * Effectue une recherche sur le graphe par prenom et affiche les comptes correspondants.
 *
 * ENTRÉE : pracine(** noeud_t) le pointeur sur la racine de l'arbre.
 *          saisie_t(* noeud_t) pointeur sur le noeud à rechercher.
 * SORTIE : prec(** noeud) adresse du noeud rechercher ou correspondant au tri des fiches.
 */
void recherchePrenom (noeud_t * r, char * prenom_t)
{
    /*variables locales*/
    int             comp_prenom = 0;       /*comparateur de prenoms*/

    /*boucle de recherche*/
    if ((r != NULL) && ((*r).nom != NULL))
    {
        comp_prenom = strcmp((*r).prenom,prenom_t);

        /*si les noms sont les mêmes...*/
        if (comp_prenom == 0)
        {
            printf("[nom : %s]\n",(*r).nom);
            printf("[prenom : %s]\n",(*r).prenom);
            printf("[login : %s]\n",(*r).login);
            printf("[mdp : %s]\n",(*r).mdp);
            printf("\n");
        }

        recherchePrenom((*r).d,prenom_t);
        recherchePrenom((*r).g,prenom_t);
    }
}

/* ECRITURE
 *
 * Parcourt l'arbre binaire et écrit les informations qu'il contient dans un fichier binaire.
 *
 * ENTREE : pracine(noeud_t *) pointeur sur la racine de l'arbre.
 *          nom(char *) nom du fichier d'écriture.
 * SORTIE : Rien.
 */
void ecriture (noeud_t * r, char * nom_fic)
{
    /*VARIABLES LOCALES*/
    FILE *          fic_ecriture;

    /*ouverture du fichier*/
    fic_ecriture = fopen(nom_fic,"a+");

    /*ouverture incorrecte*/
    if(fic_ecriture == NULL)
    {
        printf("Problème d'ouverture");
    }
    /*ouverture réussie*/
    else if ((r != NULL) && ((*r).nom != NULL))
    {
        fprintf(fic_ecriture,"%s\n",(*r).nom);
        fprintf(fic_ecriture,"%s\n",(*r).prenom);
        fprintf(fic_ecriture,"%s\n",(*r).login);
        fprintf(fic_ecriture,"%s\n",crypt((*r).mdp,"va"));
        fprintf(fic_ecriture,"\n");

        printf("ecriture : %s\n",(*r).nom);
    }

    fclose(fic_ecriture);

    /*recursivité sur les noeuds fils*/
    if ((*r).g)
    {
        ecriture((*r).g,nom_fic);
    }
    if ((*r).d)
    {
        ecriture((*r).d,nom_fic);
    }
    else
    {
        fclose(fic_ecriture);
    }
}

/* LECTURE
 *
 * Lit un fichier texte et écrit les informations qu'il contient dans un arbre binaire.
 *
 * ENTREE : pracine(noeud_t *) pointeur sur la racine de l'arbre.
 *          nom(char *) nom du fichier d'écriture.
 * SORTIE : Rien.
 */
void lecture (noeud_t ** pracine, char * nom_fic)
{
    /*VARIABLES LOCALES*/
    FILE *          fic_ecriture;
    noeud_t *       lecture_t;
    int             verif = TRUE;
    char            nom[M];
    char            prenom[M];
    char            login[M];
    char            mdp[M];
    char            tmp[M];

    /*ouverture du fichier*/
    fic_ecriture = fopen(nom_fic,"r+");

    /*ouverture incorrecte*/
    if (fic_ecriture == NULL)
    {
        printf("Problème d'ouverture\n");
    }
    /*ouverture & allocation réussies*/
    else
    {
        while ((!feof(fic_ecriture)) && (verif))
        {
            /*allocation de la fiche*/
            lecture_t = (noeud_t *) malloc(sizeof(noeud_t));

            /*initialisation de saisie_t*/
            (*lecture_t).nom = NULL;
            (*lecture_t).prenom = NULL;
            (*lecture_t).d = NULL;
            (*lecture_t).g = NULL;


            /*allocation des informations*/
            (*lecture_t).nom = (char *) malloc(sizeof(char)*M);
            (*lecture_t).prenom = (char *) malloc(sizeof(char)*M);
            (*lecture_t).login = (char *) malloc(sizeof(char)*M);
            (*lecture_t).mdp = (char *) malloc(sizeof(char)*M);

            /*vérification de l'allocation*/
            if ((lecture_t == NULL) || ((*lecture_t).nom == NULL) || ((*lecture_t).prenom == NULL) || ((*lecture_t).login == NULL) || ((*lecture_t).mdp == NULL))
            {
                printf("L'alloction a échoué !\n");
                verif = FALSE;
            }
            else
            {
                fgets(nom,M,fic_ecriture);
                nom[strlen(nom) - 1] = '\0';

                fgets(prenom,M,fic_ecriture);
                prenom[strlen(prenom) - 1] = '\0';

                fgets(login,M,fic_ecriture);
                login[strlen(login) - 1] = '\0';

                fgets(mdp,M,fic_ecriture);
                mdp[strlen(mdp) - 1] = '\0';

                fgets(tmp,M,fic_ecriture);

                /*copie des informations dans la structure*/
                strcpy((*lecture_t).nom,nom);
                strcpy((*lecture_t).prenom,prenom);
                strcpy((*lecture_t).login,login);
                strcpy((*lecture_t).mdp,mdp);
                (*lecture_t).g = NULL;
                (*lecture_t).d = NULL;

                printf("lecture : %s\n",(*lecture_t).nom);
                inserer(pracine,lecture_t);
            }
        }

        fclose(fic_ecriture);
    }
}

/* EFFACE
 *
 * Efface les données d'un fichier binaire.
 *
 * ENTREE : pracine(noeud_t *) pointeur sur la racine de l'arbre.
 *          nom(char *) nom du fichier d'écriture.
 * SORTIE : Rien.
 */
void efface (char * nom_fic)
{
    /*VARIABLES LOCALES*/
    FILE *          fic_ecriture;

    /*ouverture du fichier*/
    fic_ecriture = fopen(nom_fic,"w+");

    /*ouverture incorrecte*/
    if(fic_ecriture == NULL)
    {
        printf("Problème d'ouverture");
    }
    /*ouverture réussie*/
    else
    {
        fclose(fic_ecriture);
    }
}


/* AFFICHE_MENU
 *
 * Parcours un arbre binaire et affiche ses informations.
 *
 * ENTRÉE : r(struct noeud) un noeud de l'arbre.
 * SORTIE : Rien.
 */
void affiche_menu ()
{
    printf("\n");
    printf("#-------------------------------#\n");
    printf("#      Gestion de fichiers      #\n");
    printf("#                               #\n");
    printf("# 0 -> Quitter                  #\n");
    printf("# 1 -> Affichage                #\n");
    printf("# 2 -> Insertion/Mise a jour    #\n");
    printf("# 3 -> Suppression              #\n");
    printf("# 4 -> Recherche                #\n");
    printf("# 5 -> Ecriture                 #\n");
    printf("# 6 -> Lecture                  #\n");
    printf("# 7 -> Liberation               #\n");
    printf("#-------------------------------#\n");
    printf("\n");
}

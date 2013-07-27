/* demineur_xlib.c
 *
 * Affichage graphique du programme demineur.
 *
 * Compilation MacOSX : gcc demineur_xlib.c -o demineur -L/opt/X11/lib -lX11 -pedantic -Wall -Wextra -ansi
 *
 */

/*INCLUDES*/
#include "demineur_txt.h"
#include "demineur.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

/*DEFINES*/
#define COULEUR 9

/*position de la grille*/
#define XG 20
#define YG 20

/*taille d'une case*/
#define TC 30

/*taille des pixels*/
#define TP 10

/*séparation grille-interface*/
#define GI 20

/*VARIABLES GLOBALES*/
Bool            sortie = False; /* Indicateur de fin de pgm              */

Window          win;            /* Fenetre de travail                    */
Display *       dpy;            /* Display de ce pgm                     */

XEvent          ev;             /* Declare une variable evenement        */
unsigned long   mask;           /* Declare un mask d'evenement           */

GC              gcontext;       /* Pour le contexte graphique            */
XGCValues       gcv;
unsigned long   gcmask;

unsigned long   val_pixels[COULEUR];   /* Indices des cellules de couleurs allouees dans cmap */

XFontStruct *   fontstruct;


/* MAIN
 *
 * Définition des contextes graphiques et tout le tralala.
 *
 */

int main(int argc, char ** argv)
{
    /*VARIABLES XLIB*/
    /*Fenetre racine (fond de l'ecran)*/
	Window          root;

    /* Declaration de l'ecran par defaut*/
    int             ecran;

     /*Variables temporaires pour la couleur white et black (fg, bg)*/
	unsigned long   wpx,
				    bpx;
	
    /*Table de couleurs*/
	Colormap        cmap;
	XColor          couleur, exact;

    /*VARIABLES LOCALES*/
	int **          mat;
    int **          mat_t;

    int             i=0, j=0, k=0, l=0;

    int             verif_alloc = 0;

    /*variable de triche*/
    int             cheat = 0;
    int             voir = 0;

    int             restart = 1;   /*boucle de recommencement du programme*/
    int             nb_bombe = 10;
    int             taille_t = 12;
    int             germe;
    int             verif_case = 0;

    int             posx;
    int             posy;
    int             deminage = 0;

   while(restart == 1)
   {
	    /*Connexion au serveur*/
	    dpy = XOpenDisplay(NULL);
	    if (!dpy) 
        {
		    fprintf(stderr, "Impossible d'ouvrir le display.\n");
		    fprintf(stderr, "Assurez-vous que la variable DISPLAY est initialisee.\n");
		    fprintf(stderr, "Elle doit contenir, par exemple : \"termx:0\"\n");
		    exit(1);
	    }

	    /*Recup. de l'ecran par defaut et la fenetre root*/
	    ecran    = DefaultScreen(dpy);
	    root     = DefaultRootWindow(dpy);

	    /*Recup. couleur de l'avant plan et l'arriere plan*/
	    bpx      = BlackPixel(dpy,ecran);
	    wpx      = WhitePixel(dpy,ecran);

	    /*Allocation des couleurs*/
	    cmap = DefaultColormap(dpy,ecran);
	
	    /*allocation de couleurs rouge, vert, bleu*/
	    if (XAllocNamedColor(dpy, cmap, "darkgrey", &couleur, &exact))
		    val_pixels[0] = couleur.pixel;
	    else
		    val_pixels[0] = bpx;
	
	    if (XAllocNamedColor(dpy, cmap, "indianred", &couleur, &exact))
		    val_pixels[1] = couleur.pixel;
	    else
		    val_pixels[1] = wpx;
	
	    if (XAllocNamedColor(dpy, cmap, "white", &couleur, &exact))
		    val_pixels[2] = couleur.pixel;
	    else
		    val_pixels[2] = bpx;

        if (XAllocNamedColor(dpy, cmap, "royalblue", &couleur, &exact))
		    val_pixels[3] = couleur.pixel;
	    else
		    val_pixels[3] = bpx;

        if (XAllocNamedColor(dpy, cmap, "orangered", &couleur, &exact))
		    val_pixels[4] = couleur.pixel;
	    else
		    val_pixels[4] = bpx;

        if (XAllocNamedColor(dpy, cmap, "darkgreen", &couleur, &exact))
		    val_pixels[5] = couleur.pixel;
	    else
		    val_pixels[5] = bpx;

        if (XAllocNamedColor(dpy, cmap, "firebrick", &couleur, &exact))
		    val_pixels[6] = couleur.pixel;
	    else
		    val_pixels[6] = bpx;

        if (XAllocNamedColor(dpy, cmap, "darkmagenta", &couleur, &exact))
		    val_pixels[7] = couleur.pixel;
	    else
		    val_pixels[7] = bpx;

        if (XAllocNamedColor(dpy, cmap, "darkblue", &couleur, &exact))
		    val_pixels[8] = couleur.pixel;
	    else
		    val_pixels[8] = bpx;

        /*initialisation de la matrice*/
        printf("Veuillez saisir la valeur du germe (entre 0 et 10 000) : ");
        fflush(stdout);
        scanf("%d%*c", &germe);

        printf("Veuillez saisir la taille de la grille [12] : ");
        fflush(stdout);
        scanf("%d%*c", &taille_t);


        printf("Veuillez saisir le nombre de bombes [10] : ");
        fflush(stdout);
        scanf("%d%*c", &nb_bombe);

        posx = 2*XG+taille_t*(TC+1);
        posy = 3*YG+taille_t*(TC+1);

	    /*Creation de la fenetre: Epaiss 6 pixels, L 600 H 500*/
	    win = XCreateSimpleWindow(dpy,root,0,0,posx,posy,6,wpx,bpx);
    	XStoreName(dpy,win,"demineur v1.0");


	    /*Definition des evenements qui les concernent*/
	    XSelectInput(dpy,win,ButtonPressMask |
                             ButtonReleaseMask |
                             Button1MotionMask |
                             KeyPressMask |
                             ExposureMask );
    	/*Affichage de la fenetre*/
	    XMapWindow(dpy,win);


	    /*Creation de contexte graphique*/
	    gcv.foreground = wpx;
	    gcv.background = bpx;
	    gcv.line_width = 3;
	    gcv.function   = GXcopy;
	    gcmask = GCForeground | GCBackground | GCLineWidth | GCFunction;
	    gcontext = XCreateGC(dpy,win,gcmask,&gcv);


         /*allocation mémoire des 2 matrices*/
        mat   = (int **) malloc(sizeof(int *)*taille_t);
        mat_t = (int **) malloc(sizeof(int *)*taille_t);

        if (mat == NULL)
        {
            verif_alloc = 1;
            printf("Allocation de mat impossible");
        }
        else if (mat_t == NULL)
        {
            verif_alloc = 1;
            printf("Allocation de mat_t impossible");
        }
        else
        {
            /*allocation mémoire des lignes des 2 matrices*/
            for (i=0;i<taille_t;i++)
            {
                mat[i]   = (int *) malloc(sizeof(int)*taille_t);
                mat_t[i] = (int *) malloc(sizeof(int)*taille_t);

                if (mat[i] == NULL)
                {
                    printf("Allocation de mat[%d] impossible", i);
                    verif_alloc = 1;

                    for(j=i;j==0;j--)
                    {
                        free(mat[j]);
                    }
                    free(mat);
                    break;
                }
                else if (mat_t[i] == NULL)
                {
                    printf("Allocation de mat_t[%d] impossible", i);
                    verif_alloc = 1;

                    for(j=i;j==0;j--)
                    {
                        free(mat[j]);
                    }
                    free(mat);
                    break;
                }
            }

            if (verif_alloc == 0)
            {
                /*initialisation de la grille et des variables*/
                sortie = False;

                initialiserJeu(mat,taille_t);
                initialiserJoueur(mat_t,taille_t);

                /*Placement des bombes dans la matrice de jeu*/
                placerBombe(mat,nb_bombe,taille_t, germe);

                /*Remplissage de la matrice de jeu*/
                for(k=0;k<taille_t;k++)
                {
                    for(l=0;l<taille_t;l++)
                    {
                        remplirJeu(mat,k,l,taille_t);
                    }
                }

                /*initialisation de la verification*/
                verif_case = 0;
                deminage = 0;

                /*Boucle principale*/
                while (!sortie)
                {
                    XNextEvent(dpy,&ev);
                    switch(ev.type)
                    {
                        case Expose       : /*affichage de la grille*/
                                            afficheGrille(mat_t,taille_t,wpx);
                                            break;

                        case KeyPress     : saisie(&cheat,&restart,&deminage,&voir);
                                            if (voir == 1)
                                            {
                                                afficheGrille(mat,taille_t,wpx);
                                                voir = 0;
                                            }
                                            else
                                            {
                                                afficheGrille(mat_t,taille_t,wpx);
                                            }
                                            afficheMenu(taille_t,&deminage,wpx,bpx);

                                            break;

                        case ButtonPress  : clique(mat,mat_t,taille_t,&verif_case,&deminage);
                                            afficheGrille(mat_t,taille_t,wpx);
                                            afficheMenu(taille_t,&deminage,wpx,bpx);
                                            if ((fin(mat,mat_t,taille_t) == 1) | (verif_case == 1))
                                            {
                                                afficheDemineur(wpx, bpx, taille_t);
                                                afficheFin(mat, mat_t, wpx, cheat,taille_t);
                                            }
                                            break;

                        default           : /*puts("Evenement Inconnu !");*/
                                            break;
                    }
                }

                /*libération de l'allocation mémoire*/
                for (k=(taille_t - 1);k==0;k-=1)
                {
                    free(mat[k]);
                    free(mat_t[k]);
                }
                free(mat);
                free(mat_t);
            }
        }

        /*Liberation des ressources*/
	    XDestroyWindow(dpy,win);
	    XFreeGC(dpy, gcontext);
	    XCloseDisplay(dpy);

    }
	return 0;
}

/*PROGRAMMES XLIB*/

/* fonction : SAISIE
 *
 * Saisie de touches
 *
 * en entrée : le pointeur sur la variable d'activation du Cheat Mode (int * cheat).
 *             le pointeur sur la variable d'activation du Mode Deminage (int * deminage).
 *             le pointeur sur la variable de recommencement du jeu (int * restart).
 *             le pointeur sur la variable d'activation de l'affichage de la matrice de jeu (int * deminage).
 * en sortie : rien
 */

void saisie(int *cheat,int *restart,int *deminage,int *voir)
{
    /*VARIABLES LOCALES*/
    char            chaine[2];
	KeySym          ks;
    int             val_ks;

    /*Affectation de la touche*/
	XLookupString(&ev.xkey,chaine, 2, &ks, NULL);

    val_ks = (int)ks;

    /*VERIFICATION DE LA TOUCHE CLAVIER*/
    /*Fin du programme si la touche FIN est enfoncee*/
    if ((ks == XK_End)|(val_ks == 113))
    {
        sortie = True;
        *restart = 0;
    }
    /* Relance le programme*/
    else if (val_ks == 114)
    {
        sortie = True;
    }
    /* Active l'écran de victoire du joueur*/
    else if (val_ks == 99)
    {
        *cheat = 1;
        printf("Cheat Mode activé !\n");

    }
    /*rend visible la grille de jeu*/
    else if (val_ks == 120)
    {
        *voir = 1;
    }
    /*active le déminage*/
    else if (val_ks == 100)
    {
        *deminage = 1;
    }
}

/* fonction : CLIQUE
 *
 * Saisie de touches
 *
 * en entrée : la matrice de jeu (int ** mat).
 *             la matrice de joueur (int ** mat_t).
 *             la taille des matrices (int taille_t).
 *             le pointeur sur la variable de vérification de case [BOMBE] (int * verif_case).
 *             le pointeur sur la variable d'activation du Mode Deminage (int * deminage).
 * en sortie : rien
 */

void clique(int ** mat, int ** mat_t, int taille_t,int * verif_case,int * deminage)
{

	float           x=ev.xbutton.x;
	float           y=ev.xbutton.y;
    int             i = (x-XG)/(TC+1);
    int             j = (y-YG)/(TC+1);

    if ((YG<y) && (y<YG+taille_t*(TC+1)) && (x>XG) && (x<XG+taille_t*(TC+1)))
    {
        if (*deminage != 1)
        {
            /*la case n'est pas une bombe*/
            if (mat[i][j]/100 != 1)
            {
                remplirJoueur(mat,mat_t,i,j,taille_t);
            }
            /*la case est une bombe*/
            else
            {
                *verif_case = 1;
            }

        }

        else if (*deminage == 1)
        {
            /*placement de drapeau*/
            if (mat_t[i][j]/100 == 0)
            {
                mat_t[i][j] = 100;
            }

            /*placement impossible -> on enlève le drapeau*/
            else
            {
                mat_t[i][j] = -1;
            }
            *deminage = 0;
        }
    }
}

/* fonction : AFFICHEGRILLE
 *
 * affiche la grille mat
 *
 * en entrée : la matrice de jeu (int ** mat).
 *             la taille des matrices (int taille_t).
 *             la couleur blanche (unsigned long wpx).
 * en sortie : rien
 */

void afficheGrille(int ** mat, int taille_t, unsigned long wpx)
{
    /*variables locales*/
    char        string[3];
    int         i=0,j=0;

    for(i=0;i<taille_t;i++)
    {
        for(j=0;j<taille_t;j++)
        {
            /*affichage de la grille*/
            if(mat[i][j]/100 == 1)
            {
                /*affichage des bombes*/
                XSetForeground(dpy, gcontext, val_pixels[1]);
                XFillRectangle(dpy,win,gcontext, i*(TC+1)+XG, j*(TC+1)+YG,TC,TC);
            }
            else
            {
                if (mat[i][j]%100 == -1)
                {
                    /*affichage des cases mystères*/
                    XSetForeground(dpy, gcontext, val_pixels[0]);
                    XFillRectangle(dpy,win,gcontext, i*(TC+1)+XG, j*(TC+1)+YG,TC,TC);
                }
                else
                {
                    /*affichage des autres cases*/
                    XSetForeground(dpy, gcontext, wpx);
                    XFillRectangle(dpy,win,gcontext, i*(TC+1)+XG, j*(TC+1)+YG,TC,TC);

                    sprintf(string,"%d",mat[i][j]%100);

                    XSetForeground(dpy, gcontext, val_pixels[mat[i][j]%100 + 2]);
                    XDrawString(dpy,win, gcontext, i*(TC+1)+XG+10, j*(TC+1)+YG+20, string, strlen(string));
                }
            }

        }
    }
}

/* fonction : AFFICHEMENU
 *
 * affiche le menu du jeu.
 *
 * en entrée : la matrice de jeu (int ** mat).
 *             la taille des matrices (int taille_t).
 *             le pointeur sur la variable d'activation du Mode Deminage (int * deminage).
 *             la couleur blanche (unsigned long wpx).
 * en sortie : rien
 */

void afficheMenu(int taille_t, int * deminage, unsigned long wpx, unsigned long bpx)
{
    /*variables locales*/
    char        string_a[40]="Mode deminage actif !";
    char        string_d[50]="Mode deminage innactif, appuyez sur [D] !";
    int         posx = XG;
    int         posy = 2*YG+taille_t*(TC+1);

    /*Affiche un rectangle noir -> permet réaffichage du texte*/
    XSetForeground(dpy, gcontext, bpx);
    XFillRectangle(dpy,win,gcontext, posx,YG+taille_t*(TC+1),taille_t*(TC+1),TC);
    XSetForeground(dpy, gcontext, wpx);

    /*Affiche le Mode Deminage*/
    if (*deminage == 1)
    {
        XDrawString(dpy,win, gcontext, posx, posy, string_a, strlen(string_a));
    }
    else
    {
        XDrawString(dpy,win, gcontext, posx, posy, string_d, strlen(string_d));
    }
}

/* fonction : AFFICHEDEMINEUR
 *
 * affiche le nom du jeu pixélisé "DEMINEUR".
 *
 * en entrée : la couleur blanche (unsigned long wpx).
 *             la couleur noire (unsigned long bpx).
 *             la taille des matrices (int taille_t).
 * en sortie : rien
 */

void afficheDemineur(unsigned long wpx, unsigned long bpx,int taille_t)
{
    /*VARIABLES LOCALES*/
    int         posx = XG+taille_t*TC+42+2*GI+20;
    int         posy = YG+taille_t*TC+42;

    if (posy < 24+COULEUR*(42+10))
    {
        posy = 24+COULEUR*(42+10) + 50;
    }

    /*Réinitialisation de l'écran*/
    XSetForeground(dpy, gcontext, bpx);
    XFillRectangle(dpy,win,gcontext, 0, 0,posx,posy);

    /*AFFICHAGE MESSAGE*/
    XSetForeground(dpy, gcontext, wpx);

    /*Affichage d*/
    XFillRectangle(dpy,win,gcontext, XG+ 0*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 0*TP   , YG+ 3*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 1*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 1*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 1*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 1*TP   , YG+ 3*TP  ,TP,TP);

    /*Affichage E*/
    XFillRectangle(dpy,win,gcontext, XG+ 3*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 3*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 3*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 3*TP   , YG+ 3*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 4*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 4*TP   , YG+ 3*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 4*TP   , YG+ 1*TP  ,TP,TP);

    /*Affichage M*/
    XFillRectangle(dpy,win,gcontext, XG+ 6*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 6*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 6*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 6*TP   , YG+ 3*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 7*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 8*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 8*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 8*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+ 9*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+10*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+10*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+10*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+10*TP   , YG+ 3*TP  ,TP,TP);

    /*Affichage i*/
    XFillRectangle(dpy,win,gcontext, XG+12*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+12*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+12*TP   , YG+ 3*TP  ,TP,TP);

    /*Affichage n*/
    XFillRectangle(dpy,win,gcontext, XG+14*TP   , YG+ 0*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+14*TP   , YG+ 1*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+14*TP   , YG+ 2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+14*TP   , YG+ 3*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+15*TP   , YG+ 1*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+16*TP   , YG+ 2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+17*TP   , YG+ 0*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+17*TP   , YG+ 1*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+17*TP   , YG+ 2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+17*TP   , YG+ 3*TP   ,TP,TP);

    /*Affichage E2*/
    XFillRectangle(dpy,win,gcontext, XG+19*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+19*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+19*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+19*TP   , YG+ 3*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+20*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+20*TP   , YG+ 3*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+20*TP   , YG+ 1*TP  ,TP,TP);

    /*Affichage U*/
    XFillRectangle(dpy,win,gcontext, XG+22*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+22*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+22*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+22*TP   , YG+ 3*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+23*TP   , YG+ 3*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+24*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+24*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+24*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+24*TP   , YG+ 3*TP  ,TP,TP);

    /*Affichage R*/
    XFillRectangle(dpy,win,gcontext, XG+26*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+26*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+26*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+26*TP   , YG+ 3*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+27*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+27*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+27*TP   , YG+ 2*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+28*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+28*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+28*TP   , YG+ 3*TP  ,TP,TP);

    /*Affichage !*/
    XFillRectangle(dpy,win,gcontext, XG+30*TP   , YG+ 0*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+30*TP   , YG+ 1*TP  ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+30*TP   , YG+ 3*TP  ,TP,TP);

}

/* fonction : AFFICHEFIN
 *
 * affiche la fin du jeu [win/lose].
 *
 * en entrée : la matrice de jeu (int ** mat).
 *             la matrice du joueur (int ** mat_t).
 *             la couleur blanche (unsigned long wpx).
 *             la variable d'enclenchement du Cheat Mode (int cheat).
 *             la taille des matrices (int taille_t).
 * en sortie : rien
 */

void afficheFin(int ** mat,int ** mat_t, unsigned long wpx, int cheat,int taille_t)
{
    /*VARIABLES LOCALES*/
    int         posx=XG;
    int         posy=YG+4*TC;

    char        string_fin[40]="Appuyez sur [Fin] ou [Q] pour quitter.";
    char        string_rec[40]="Appuyez sur [R] pour recommencer.";
    char        string_win[40]="Vous avez GAGNE !";
    char        string_los[40]="Vous avez PERDU !";

    XSetForeground(dpy, gcontext, wpx);

    if ((fin(mat,mat_t,taille_t) == 1)|(cheat == 1))
    {
        XDrawImageString(dpy,win, gcontext, posx, posy,string_win , strlen(string_win));
    }
    else
    {
        XDrawImageString(dpy,win, gcontext, posx, posy,string_los , strlen(string_los));
    }

    XDrawImageString(dpy,win, gcontext, posx, posy + 40, string_fin, strlen(string_fin));
    XDrawImageString(dpy,win, gcontext, posx, posy + 60, string_rec, strlen(string_rec));
}

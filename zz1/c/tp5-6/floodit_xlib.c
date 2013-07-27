/* floodit_xlib.c
 *
 * Affichage graphique du programme floodit.
 *
 * Compilation MacOSX : gcc floodit_xlib.c -o floodit -L/opt/X11/lib -lX11 -pedantic -Wall -Wextra -ansi
 *
 */

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

/*DEFINES*/
#define COULEUR 7

/*position de la grille*/
#define XG 20
#define YG 20

/*taille d'une case*/
#define TC 30

/*taille des pixels*/
#define TP 10

/*dimension de la fenêtre*/
#define LONGF 5000
#define HIGHF 2000

/*séparation grille-interface*/
#define GI 20

/*DECLARATIONS*/
/* déclarations fonctions xlib*/
void afficheGrille(int ** mat,int taille_t);
void saisie(int ** mat,int old_color,int * iteration, int * cheat,int * restart,int taille_t);
void clique(int ** mat,int old_color,int * iteration,int taille_t);
void afficheFin(int ** mat,int iteration, unsigned long wpx, int cheat,int taille_t);
void afficheFloodIt(unsigned long wpx, unsigned long bpx,int taille_t);

void afficheIt(int iteration, unsigned long wpx, unsigned long bpx, int iter_max,int taille_t);


/*déclarations fonctions floodit*/
void afficheIteration(int ** mat, int taille_t);
int fin(int ** mat, int taille_t);
void initialiser(int ** mat,int germe,int taille_t);
void remplir(int ** mat, int old_color, int new_color, int i, int j, int iteration, int taille_t);

/*Declaration de variables globales*/
Bool           sortie = False; /* Indicateur de fin de pgm              */

Window         win;            /* Fenetre de travail                    */
Display       *dpy;            /* Display de ce pgm                     */

XEvent         ev;             /* Declare une variable evenement        */
unsigned long  mask;           /* Declare un mask d'evenement           */

GC             gcontext;       /* Pour le contexte graphique            */
XGCValues      gcv;
unsigned long  gcmask;

unsigned long val_pixels[COULEUR];   /* Indices des cellules de couleurs allouees dans cmap */

XFontStruct   *fontstruct;


/* MAIN
 *
 * Définition des contextes graphiques et tout le tralala.
 *
 */

int main(int argc, char ** argv)
{
    /*VARIABLES XLIB*/
    /*Fenetre racine (fond de l'ecran)*/
	Window        root;

    /* Declaration de l'ecran par defaut*/
    int           ecran;

     /*Variables temporaires pour la couleur whithe et black (fg, bg)*/
	unsigned long wpx,
				  bpx;
	
    /*Table de couleurs*/
	Colormap      cmap;
	XColor        couleur, exact;

    /*VARIABLES LOCALES*/
	int           ** mat;

    int           i=0, j=0, k=0;

    int           iteration = 0;
    int           old_color;
    int           verif_alloc = 0;
    int           cheat = 1;
    int           restart = 1;   /*boucle de recommencement du programme*/
    int           iter_max = 22;
    int           taille_t = 12;
    int           germe = 0;

    int         posx;
    int         posy;

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
	    if (XAllocNamedColor(dpy, cmap, "indian red", &couleur, &exact))
		    val_pixels[0] = couleur.pixel;
	    else
		    val_pixels[0] = bpx;
	
	    if (XAllocNamedColor(dpy, cmap, "sky blue", &couleur, &exact))
		    val_pixels[1] = couleur.pixel;
	    else
		    val_pixels[1] = wpx;
	
	    if (XAllocNamedColor(dpy, cmap, "sea green", &couleur, &exact))
		    val_pixels[2] = couleur.pixel;
	    else
		    val_pixels[2] = bpx;

        if (XAllocNamedColor(dpy, cmap, "plum", &couleur, &exact))
		    val_pixels[3] = couleur.pixel;
	    else
		    val_pixels[3] = bpx;

        if (XAllocNamedColor(dpy, cmap, "gold", &couleur, &exact))
		    val_pixels[4] = couleur.pixel;
	    else
		    val_pixels[4] = bpx;

        if (XAllocNamedColor(dpy, cmap, "peru", &couleur, &exact))
		    val_pixels[5] = couleur.pixel;
	    else
		    val_pixels[5] = bpx;

        if (XAllocNamedColor(dpy, cmap, "moccasin", &couleur, &exact))
		    val_pixels[6] = couleur.pixel;
	    else
		    val_pixels[6] = bpx;

        /*initialisation de la matrice*/
        printf("Veuillez saisir la valeur du germe (entre 0 et 10 000) : ");
        fflush(stdout);
        scanf("%d%*c", &germe);

        printf("Veuillez saisir la taille de la grille [12] : ");
        fflush(stdout);
        scanf("%d%*c", &taille_t);


        printf("Veuillez saisir le nombre d'itérations maximales [22] : ");
        fflush(stdout);
        scanf("%d%*c", &iter_max);
        iter_max = iter_max - 1;

        posx = 2*XG+taille_t*TC;
        posy = 2*YG+taille_t*TC;

        if (posy < 24+COULEUR*(42+10))
        {
            posy = 24+COULEUR*(42+10) + 50;
        }

	    /*Creation de la fenetre: Epaiss 6 pixels, L 600 H 500*/
	    win = XCreateSimpleWindow(dpy,root,0,0,posx,posy,6,wpx,bpx);
    	XStoreName(dpy,win,"flood it v1.1");


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


        /*Allocation mémoire de la grille*/
        mat = (int **) malloc(sizeof(int *)*taille_t);

        if (mat == NULL)
        {
            printf("Allocation de mat impossible");
        }
        else
        {
            /*Allocation mémoire des lignes*/
            for (i=0;i<taille_t;i++)
            {
                mat[i] = (int *) malloc(sizeof(int)*taille_t);

                if (mat[i] == NULL)
                {
                    /*si l'allocation échoue on termine le programme*/
                    printf("Allocation de mat[%d] impossible", i);
                    verif_alloc = 1;

                    for(j=i;j>=0;j--)
                    {
                        free(mat[j]);
                    }
                    free(mat);

                }
            }

            if (verif_alloc == 0)
            {
                /*initialisation de la grille et des variables*/
                sortie = False;
                iteration = 0;
                initialiser(mat,germe,taille_t);

                old_color = mat[0][0]/100;
                /*Boucle principale*/
                while (!sortie)
                {
                    XNextEvent(dpy,&ev);
                    switch(ev.type)
                    {
                        case Expose       : /*affichage de la grille*/
                                            afficheGrille(mat,taille_t);
                                            break;

                        case KeyPress     : saisie(mat,old_color,&iteration,&cheat,&restart,taille_t);
                                            afficheGrille(mat,taille_t);
                                            afficheIt(iteration,wpx,bpx,iter_max,taille_t);
                                            old_color = mat[0][0]/100;
                                            if ((fin(mat,taille_t) == 0) | (iteration > iter_max) | (cheat == 0))
                                            {
                                                afficheFloodIt(wpx, bpx,taille_t);
                                                afficheFin(mat,iteration, wpx, cheat,taille_t);
                                            }
                                            break;

                        case ButtonPress  : clique(mat,old_color,&iteration,taille_t);
                                            afficheGrille(mat,taille_t);
                                            old_color = mat[0][0]/100;
                                            afficheIt(iteration,wpx,bpx,iter_max,taille_t);
                                            if ((fin(mat,taille_t) == 0) | (iteration > iter_max))
                                            {
                                                afficheFloodIt(wpx, bpx, taille_t);
                                                afficheFin(mat,iteration, wpx, cheat,taille_t);
                                            }
                                            break;

                        default           : /*puts("Evenement Inconnu !");*/
                                            break;
                    }
                }

                /*libération de l'allocation mémoire*/
                for (k=0;k<taille_t;k++)
                {
                    if (mat[k] != NULL)
                    {
                        free(mat[k]);
                    }
                }
                free(mat);
                mat = NULL;
            }
        }

        /*Liberation des ressources*/
	    XDestroyWindow(dpy,win);
	    XFreeGC(dpy, gcontext);
	    XCloseDisplay(dpy);

    }
	return 0;
}


/*SOUS-PROGRAMMES*/

/* fonction : SAISIE
 *
 * Saisie de touches
 *
 */

void saisie(int ** mat,int old_color,int * iteration,int *cheat,int *restart,int taille_t)
{
    /*VARIABLES LOCALES*/
    char            chaine[2];
	KeySym          ks;
    int             val_ks;
    int             new_color = old_color;

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
        *cheat = 0;
    }
    else
    {
        /*pad numérique -> 0*/
        if ((old_color != 0) && (val_ks == 65456))
        {
            new_color = 0;
        }
        /*pad numérique -> 1*/
        else if ((old_color != 1) && (val_ks == 65457))
        {
            new_color = 1;
        }
        /*pad numérique -> 2*/
        else if ((old_color != 2) && (val_ks == 65458))
        {
            new_color = 2;
        }
        /*pad numérique -> 3*/
        else if ((old_color != 3) && (val_ks == 65459))
        {   
            new_color = 3;
        }
        /*pad numérique -> 4*/
        else if ((old_color != 4) && (val_ks == 65460))
        {
            new_color = 4;
        }
        /*pad numérique -> 5*/
        else if ((old_color != 5) && (val_ks == 65461))
        {
            new_color = 5;
        }
        /*pad numérique -> 6*/
        else if ((old_color != 0) && (val_ks == 65462))
        {
            new_color = 6;
        }
    }

    /*remplissage de la matrice*/
    if (old_color != new_color)
    {
        *iteration = *iteration+1;
        remplir(mat,old_color,new_color,0,0,*iteration,taille_t);
    }
}

/* fonction : CLIQUE
 *
 * Saisie de touches
 *
 */

void clique(int ** mat, int old_color, int * iteration,int taille_t)
{
	float           x=ev.xbutton.x;
	float           y=ev.xbutton.y;
    int             new_color = old_color;
    int             i = (x-XG)/TC;
    int             j = (y-YG)/TC;

    if ((YG<y) && (y<YG+taille_t*TC) && (x>XG) && (x<XG+taille_t*TC))
    {
        new_color=mat[i][j]/100;
    }

    /*remplissage de la matrice*/
    if (old_color != new_color)
    {
        *iteration = *iteration+1;
        remplir(mat,old_color,new_color,0,0,*iteration,taille_t);
    }
}


/* fonction : INITIALISER
 *
 * initialise mat avec des couleurs aux hasard.
 *
 * en entrée : la matrice
 * en sortie : rien
 */

void initialiser(int ** mat,int germe,int taille_t)
{
    /*variables locales*/
    int i=0,j=0;

    /*initialisation du germe*/
    srand(germe);

    for(i=0;i<taille_t;i++)
    {
        for(j=0;j<taille_t;j++)
        {
            /*initialisation de la grille*/
            mat[i][j] = (rand()%COULEUR)*100;
        }
    }
}


/* fonction : AFFICHEGRILLE
 *
 * affiche la grille mat
 *
 * en entrée : la matrice
 * en sortie : rien
 */

void afficheGrille(int ** mat, int taille_t)
{
    /*variables locales*/
    int i=0,j=0;

    for(i=0;i<taille_t;i++)
    {
        for(j=0;j<taille_t;j++)
        {
            /*affichage de la grille*/
            XSetForeground(dpy, gcontext, val_pixels[mat[i][j]/100]);
            XFillRectangle(dpy,win,gcontext, i*TC+XG, j*TC+YG,TC,TC);
        }
    }
}


/* fonction : AFFICHEITERATION
 *
 * affiche la grille des itérations.
 *
 * en entrée : la matrice
 * en sortie : rien
 */

void afficheIteration(int ** mat, int taille_t)
{
    /*variables locales*/
    int i=0,j=0;

    for(i=0;i<taille_t;i++)
    {
        for(j=0;j<taille_t;j++)
        {
            if (mat[i][j]%100 - 10 < 0)
            {
                /*affichage de la grille*/
                printf("%d  ",mat[i][j]%100);
            }
            else
            {
                printf("%d ",mat[i][j]%100);
            }

        }
        printf("\n");
    }
    printf("\n");
}



/* fonction : FIN
 *
 * renvoie 1 si la grille est remplie, 0 sinon
 *
 * en entrée : la matrice
 * en sortie : rien
 */

int fin(int ** mat, int taille_t)
{
    /*variables locales*/
    int i=0,j=0;
    int valeur_origine = mat[0][0]/100;
    int verif = 0;

    for(i=0;i<taille_t;i++)
    {
        for(j=0;j<taille_t;j++)
        {
            /*verifie la matrice*/
            if (mat[i][j]/100 != valeur_origine)
            {
                verif = 1;
                break;
            }
        }
    }
    return verif;
}



/* fonction : REMPLIR
 * Remplie la grille selon les règles de Flood It
 *
 * en entrée : la matrice
               l'ancienne couleur (int)
               les coordonées i et j de la matrice (int)*(int)
               la valeur de l'itération courante (int)

 * en sortie : rien
 */


void remplir(int ** mat, int old_color, int new_color, int i, int j, int iteration, int taille_t)
{
    /*variables locales*/
    int cour = mat[i][j];
    int iter_cour = mat[i][j]%100;

    /*vérification de la couleur de la case*/
    if (cour/100 == old_color)
    {
        mat[i][j] = new_color*100 + iter_cour;

        /*vérification de l'itération de la case*/
        if (cour%100 == 0)
        {
                mat[i][j] = mat[i][j] + iteration;
        }

        /*vérification des cases [i+1;j]*/
        if ((i < (taille_t - 1)) && (mat[i+1][j]/100 == old_color))
        {
            remplir(mat, old_color, new_color, i+1, j, iteration,taille_t);
		}

        /*vérification des cases [i-1;j]*/
        if ((i > 0) && (mat[i-1][j]/100 == old_color))
		{
            remplir(mat, old_color, new_color, i-1, j, iteration,taille_t);
		}

        /*vérification des cases [i;j+1]*/
        if ((j < (taille_t - 1)) && (mat[i][j+1]/100 == old_color))
		{
			remplir(mat, old_color, new_color, i, j+1, iteration,taille_t);
		}
        /*vérification des cases [i;j-1]*/
        if ((j > 0) && (mat[i][j-1]/100 == old_color))
		{
			remplir(mat, old_color, new_color, i, j-1, iteration,taille_t);
		}
    }
}

/*PROGRAMME GRAPHIQUE*/

/* fonction : AFFICHEINTERFACE
 *
 * affiche l'interface du jeu.
 *
 * en entrée : rien
 * en sortie : rien
 */

void afficheFloodIt(unsigned long wpx, unsigned long bpx,int taille_t)
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
    /*Affichage F*/
    XSetForeground(dpy, gcontext, wpx);
    XFillRectangle(dpy,win,gcontext, XG         , YG        ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+TP      , YG        ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG         , YG+TP     ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG         , YG+2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+TP      , YG+2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG         , YG+3*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+2*TP    , YG,TP     ,TP);

    /*Affichage L*/
    XFillRectangle(dpy,win,gcontext, XG+4*TP    , YG        ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+4*TP    , YG+TP     ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+4*TP    , YG+2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+4*TP    , YG+3*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+5*TP    , YG+3*TP   ,TP,TP);

    /*Affichage O*/
    XFillRectangle(dpy,win,gcontext, XG+7*TP    , YG+0*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+7*TP    , YG+1*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+7*TP    , YG+2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+7*TP    , YG+3*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+8*TP    , YG+0*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+8*TP    , YG+3*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+9*TP    , YG+0*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+9*TP    , YG+1*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+9*TP    , YG+2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+9*TP    , YG+3*TP   ,TP,TP);

    /*Affichage O2*/
    XFillRectangle(dpy,win,gcontext, XG+11*TP    , YG+0*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+11*TP    , YG+1*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+11*TP    , YG+2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+11*TP    , YG+3*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+12*TP    , YG+0*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+12*TP    , YG+3*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+13*TP    , YG+0*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+13*TP    , YG+1*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+13*TP    , YG+2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+13*TP    , YG+3*TP   ,TP,TP);

    /*Affichage d*/
    XFillRectangle(dpy,win,gcontext, XG+15*TP    , YG+2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+15*TP    , YG+3*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+16*TP    , YG+0*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+16*TP    , YG+1*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+16*TP    , YG+2*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+16*TP    , YG+3*TP   ,TP,TP);

    /*Affichage i*/
    XFillRectangle(dpy,win,gcontext, XG+0*TP    , YG+5*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+0*TP    , YG+7*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+0*TP    , YG+8*TP   ,TP,TP);

    /*Affichage t*/
    XFillRectangle(dpy,win,gcontext, XG+2*TP    , YG+5*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+2*TP    , YG+6*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+2*TP    , YG+7*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+2*TP    , YG+8*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+3*TP    , YG+6*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+3*TP    , YG+8*TP   ,TP,TP);

    /*Affichage !*/
    XFillRectangle(dpy,win,gcontext, XG+6*TP    , YG+5*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+6*TP    , YG+6*TP   ,TP,TP);
    XFillRectangle(dpy,win,gcontext, XG+6*TP    , YG+8*TP   ,TP,TP);

}

void afficheFin(int ** mat, int iteration, unsigned long wpx, int cheat,int taille_t)
{
    /*VARIABLES LOCALES*/
    int         posx=XG;
    int         posy=YG+4*TC;

    char        string_it[40];
    char        string_fin[40]="Appuyez sur [Fin] ou [Q] pour quitter.";
    char        string_rec[40]="Appuyez sur [R] pour recommencer.";
    char        string_win[40]="Vous avez GAGNE !";
    char        string_los[40]="Vous avez PERDU !";

    sprintf(string_it,"Vous avez effectue %d iterations.",iteration);

    XSetForeground(dpy, gcontext, wpx);

    if ((fin(mat,taille_t) == 0)|(cheat == 0))
    {
        XDrawImageString(dpy,win, gcontext, posx, posy,string_win , strlen(string_win));
    }
    else
    {
        XDrawImageString(dpy,win, gcontext, posx, posy,string_los , strlen(string_los));
    }

    XDrawImageString(dpy,win, gcontext, posx, posy + 20, string_it, strlen(string_it));
    XDrawImageString(dpy,win, gcontext, posx, posy + 40, string_fin, strlen(string_fin));
    XDrawImageString(dpy,win, gcontext, posx, posy + 60, string_rec, strlen(string_rec));
}




void afficheIt(int iteration, unsigned long wpx, unsigned long bpx, int iter_max, int taille_t)
{
    /*Variable locale*/
    char        string[3];

    sprintf(string,"%d",iter_max - iteration + 1);

    XSetForeground(dpy, gcontext, bpx);
    XDrawString(dpy,win, gcontext, XG+10, YG+20, string, strlen(string));
}






































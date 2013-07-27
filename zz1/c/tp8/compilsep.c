/* INCLUDE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*
 * strucure cle (nom), valeur (note)
 */

/* PROTOTYPES */
void initList(list_t * plist);
int insert(list_t * plist, char * nom, int note);
void displayByKey(list_t list);
void displayByValue(list_t list);
void freeList(list_t * plist);
void computeHisto(histogram_t h, list_t l);
void displayHisto(histogram_t h);
int maxHisto(histogram_t h);
float meanHisto(histogram_t h);
int countHisto(histogram_t h);
void displayGraphicalHisto(gdata_t g, histogram_t h);
void displayGraph(histogram_t h);
void displayText(histogram_t h);

/* VARIABLES GLOBALES */
int ERROR = 0;

/* DEFINE */
#define ERROR_OK          0
#define ERROR_LIST_ALLOC  1
#define EROOR_FILE        1

/* STRUCTURE */
typedef struct cell_s {
    char key[30];
    int  value;
    struct cell_s * nk, *nv;
} cell_t;

typedef struct list_s {
    cell_t * key;
    cell_t * value;
} list_t;

typedef struct gdata_s {
    Window         root;
    Window         win;
    Display       *dpy;
    int            ecran;
    GC             gcontext;
    XGCValues      gcv;
    Visual        *visual;
    Colormap       colormap;
    Font           font;
} gdata_t;

/* #define DEBUG*/
/* DEFINE */
#define HISTOSIZE 21

#ifdef DEBUG
    #define LOG(A) printf A
#else
    #define LOG(A) 
#endif

typedef int histogram_t[HISTOSIZE];

/* SOUS PROGRAMMES */

/* FONCTION : (void) initList
 *
 * Initialisation de la liste en début de programme.
 *
 * ENTRÉE : plist (list_t *) Pointeur sur la tête de liste.
 * SORTIE : Rien.
 */

void initList(list_t * plist) {
    plist->key = plist->value = 0;
}

/* FONCTION : (int) insert
 *
 * Insertion d'une valeur dans la liste chainée.
 *
 * ENTRÉE : plist (list_t *) Pointeur sur la tête de liste.
 *          nom (char *) Valeur de la case de mot.
 *          note (int) Valeur de la case valeur.
 * SORTIE : ret (int) Indique la réussite de l'insertion.
 */

int insert(list_t * plist, char * nom, int note) {
    int ret = 0;
    cell_t * prec = 0, *cour =0;
    cell_t * cell = (cell_t * )malloc(sizeof(cell_t));

    if (cell) {
        strcpy(cell->key, nom);
        cell->value = note;
        cell->nk = cell->nv = 0;
        LOG(("** INSERT %s %d\n", cell->key, cell->value));

        prec = 0;
        cour = plist->key;
        while (cour &&  strcmp(cell->key, cour->key)>0) {
            prec = cour;
            cour = cour->nk;
        }
        if (prec) {
            cell->nk = prec->nk; 
            prec->nk = cell;
        } else {
            cell->nk = plist->key;
            plist->key = cell;
        }
        prec = 0;
        cour = plist->value;
        while (cour &&  cell->value < cour->value) {
            prec = cour;
            cour = cour->nv;
        }
        if (prec) {
            cell->nv = prec->nv; 
            prec->nv = cell;
        } else {
            cell->nv = plist->value;
            plist->value = cell;
        }
        ret = 1;
    } else ERROR = ERROR_LIST_ALLOC;

    return ret;
}

/* FONCTION : (void) displayByKey
 *
 * Affichage des mots.
 *
 * ENTRÉE : (list_t *) Pointeur sur une liste.
 * SORTIE : Rien.
 */

void displayByKey(list_t list) {
    cell_t * cour = list.key;
    
    printf("by key\n");
    while (cour) {
        printf("%s %d\n", cour->key, cour->value);
        cour = cour->nk;
    }
}

/* FONCTION : (void) displayByValue
 *
 * Affichage des valeurs.
 *
 * ENTRÉE : (list_t *) Pointeur sur une liste.
 * SORTIE : Rien.
 */


void displayByValue(list_t list) {
    cell_t * cour = list.value;
    
    printf("by value\n");
    while (cour) {
        printf("%s %d\n", cour->key, cour->value);
       cour = cour->nv;
    }
}

/* FONCTION : (void) freeList
 *
 * Libération des structures allouées.
 *
 * ENTRÉE : (list_t *) Pointeur sur la tête de la liste.
 * SORTIE : Rien.
 */


void freeList(list_t * plist) {
    cell_t * courv = plist->value;

    while (courv->nv != NULL)
    {
        plist->value = courv->nv;
        free(courv);
        courv = plist->value;
    }

    free(plist->value);
    plist-> key = plist-> value = NULL;
}

/* FONCTION : (void) computeHisto
 *
 * Création et initialisation de l'histogramme.
 *
 * ENTRÉE : (list_t) une cellule de la liste.
 *          (histogram_t) une structure histogramme.
 * SORTIE : Rien.
 */

void computeHisto(histogram_t h, list_t l) {
    int i = 0;
    int j = 0;
    cell_t * cour = l.key;

    for (i=0; i < HISTOSIZE ; ++i)
        h[i] = 0.0;

    while (cour) {
        ++h[cour->value];
        cour = cour->nk;
        ++j;
    }
} 

/* FONCTION : (void) displayHisto
 *
 * Affichage de l'histogramme.
 *
 * ENTRÉE : (histogram_t) une structure histogramme.
 * SORTIE : Rien.
 */

void displayHisto(histogram_t h) {
    int i = 0;
    
    for (i=0; i < HISTOSIZE ; ++i)
        printf("[%2d] : %3d\n", i, h[i] );
}

/* FONCTION : (int) maxHisto
 *
 * Calcul du max de l'histogramme.
 *
 * ENTRÉE : (histogram_t) une structure histogramme.
 * SORTIE : max (int) le max de l'histogramme.
 */

int maxHisto(histogram_t h) {
    int i, max = h[0];
    
    for(i=1; i< HISTOSIZE; ++i)
        if (h[i]>max) max=h[i];
    
    return max;
}

/* FONCTION : (float) meanHisto
 *
 * Calcul de "valeur" de l'histogramme.
 *
 * ENTRÉE : (histogram_t) une structure histogramme.
 * SORTIE : mean (float) le mean de l'histogramme.
 */

float meanHisto(histogram_t h) {
    float som =0.;
    int   tot = 0, i;
    
    for (i=0; i< HISTOSIZE; ++i) {
        som  = h[i] * i;
        tot += h[i];
    }
    LOG(("MEAN %f / %d\n", som, tot));
    
    return som/(float)tot;
}

/* FONCTION : (int) maxHisto
 *
 * Calcul de "valeur" de l'histogramme.
 *
 * ENTRÉE : (histogram_t) une structure histogramme.
 * SORTIE : count (int) le count de l'histogramme.
 */

int countHisto(histogram_t h) {
    int   tot = 0, i;
    for (i=0; i< HISTOSIZE; ++i) {
        tot += h[i];
    }
    LOG(("TOT %d\n", tot));
  
    return tot;
}

/* FONCTION : (void) displayGraphicalHisto
 *
 * Affichage graphique de l'histogramme.
 *
 * ENTRÉE : (histogram_t) structure histogram_t.
 *          (gdata_t) structure (contexte graphique) gdata_t.
 * SORTIE : rien
 */

void displayGraphicalHisto(gdata_t g, histogram_t h) {
    char          chaine[255];
    int maxx = 600;
    int maxy = 400;
    int i;   
    int j = maxHisto(h);

    XClearWindow(g.dpy, g.win);

    for(i=0; i<HISTOSIZE; ++i) {
        XDrawLine(g.dpy,g.win,g.gcontext,(int)(maxx/22.0*(i+1)), maxy-(int)(h[i]/(float)j*300.) ,(int)(maxx/22.0*(i+1)),maxy);
        sprintf(chaine, "%d", i);
        XDrawString(g.dpy, g.win, g.gcontext, (int)(maxx/22.0*(i+1)-4), 420, chaine, strlen(chaine));
        if (h[i]>0) {
            sprintf(chaine, "%d", h[i]);
            XDrawString(g.dpy, g.win, g.gcontext, (int)(maxx/22.0*(i+1)-4), 75, chaine, strlen(chaine));
        }
    }
    strcpy(chaine, "Occurences");
    XDrawString(g.dpy, g.win, g.gcontext, maxx-100, 50, chaine, strlen(chaine));
    sprintf(chaine, "Notes [%d]", countHisto(h));
    XDrawString(g.dpy, g.win, g.gcontext, 10, 445, chaine, strlen(chaine));
    sprintf(chaine, "Moyenne : %f", meanHisto(h));
    XDrawString(g.dpy, g.win, g.gcontext, 10, 470, chaine, strlen(chaine));
}

/* FONCTION : (void) displayGraph
 *
 * Affichage graphique de du graphique.
 *
 * ENTRÉE : (histogram_t) structure histogram_t.
 * SORTIE : rien
 */

void displayGraph(histogram_t h) {
    gdata_t g;
    int wpx, bpx;
    int sortie = 0;
    XEvent ev;
    XGCValues      gcv;      
    char ** list;
    int count;         
    unsigned long  gcmask;

    g.dpy      = XOpenDisplay(0); 
    g.ecran    = DefaultScreen(g.dpy);
    g.root     = DefaultRootWindow(g.dpy);

    bpx      = BlackPixel(g.dpy,g.ecran);
    wpx      = WhitePixel(g.dpy,g.ecran);

    g.visual   = DefaultVisual(g.dpy, g.ecran);
    g.win = XCreateSimpleWindow(g.dpy,g.root,30,40,600,500,1,wpx,bpx);
    XStoreName(g.dpy,g.win,"Repartition des notes");

    XSelectInput(g.dpy,g.win,ButtonPressMask |
        ButtonReleaseMask |
        Button1MotionMask |
        KeyPressMask |
        ExposureMask );

    gcv.foreground = wpx;
    gcv.background = bpx;
    gcv.line_width = 2;
    gcv.function   = GXcopy;
    gcmask         = GCForeground | GCBackground | GCLineWidth | GCFunction;
    g.gcontext       = XCreateGC(g.dpy,g.win,gcmask,&gcv);

    list = XListFonts(g.dpy, "*-14-*", 10, &count); 
    g.font = XLoadFont(g.dpy, list[0] );  
    XSetFont(g.dpy,g.gcontext,g.font); 

    XMapWindow(g.dpy,g.win);           

    while(!sortie) {
        XNextEvent(g.dpy,&ev);
        switch(ev.type) {
            case Expose   : displayGraphicalHisto(g, h);
                break;
            case KeyPress : sortie =1;
                break;
        }
    }

    XUnloadFont(g.dpy,g.font); 
    XFreeFontNames(list);
    /*XFreeColormap(dpy, colormap);*/
    XDestroyWindow(g.dpy , g.win );
    XFreeGC(g.dpy,g.gcontext);
    XCloseDisplay(g.dpy);
}

/* FONCTION : (void) displayText
 *
 * Affichage textuel de du graphique.
 *
 * ENTRÉE : (histogram_t) structure histogram_t.
 * SORTIE : rien
 */

void displayText(histogram_t h) {
    displayHisto(h);
}

/* PROGRAMME PRINCIPALE
 *
 * Lit un fichier .text et créer un liste chainée triant chaque valeur et chaque lettre puis créer u histogramme de ces valeurs.
 *
 * ENTRÉE : Rien.
 * SORTIE : Rien.
 */

int main(int argc, char ** argv) {
    list_t list;
    histogram_t h;
    int text = 1;
    char * file = NULL;

    initList(&list);

    if (argc<2) {
        printf("[HELP] program file mode\n");
        printf("       where file is a text file\n");
        printf("       where mode belongs to text/graph\n\n");
    } else {
        /* first parameter is file */
        if (strcmp(argv[1], "text")  && strcmp(argv[1], "graph") ) {
            file = argv[1];
            if (argc>=3)
            text = strcmp(argv[2], "graph");  
        } else {
            /* first parameter is text/graph */
            text = strcmp(argv[1], "graph");
            if (argc>=3)
                file=argv[2];
        }

        printf("DEMO MODE -- dummy data");
        insert(&list, "un", 20);
        insert(&list, "deux", 10);
        insert(&list, "trois", 20);
        insert(&list, "quatre", 15);
        insert(&list, "cinq", 15);
        insert(&list, "six", 15);
        insert(&list, "sept", 0);
        insert(&list, "huit", 14);
        insert(&list, "neuf", 11);
        insert(&list, "dix", 7);
        displayByKey(list);
        displayByValue(list);
        computeHisto(h,list);

        if (text) {
            displayText(h);
        } else {
            displayGraph(h);
        }

        freeList(&list);
    }

    return 0;
}

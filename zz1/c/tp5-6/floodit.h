/* floodit.h [ENTÊTE]
 *
 * Affichage graphique du programme floodit.
 *
 * Compilation MacOSX : gcc floodit_xlib.c -o floodit -L/opt/X11/lib -lX11 -pedantic -Wall -Wextra -ansi
 *
 */

/* fonction : SAISIE
 *
 * Saisie de touches
 *
 */

void saisie(int ** mat,int old_color,int * iteration,int *cheat,int *restart,int taille_t);

/* fonction : CLIQUE
 *
 * Saisie de touches
 *
 */

void clique(int ** mat, int old_color, int * iteration,int taille_t);


/* fonction : AFFICHEGRILLE
 *
 * affiche la grille mat
 *
 * en entrée : la matrice (int ** mat).
 *             la taille des matrices (int taille_t).
 * en sortie : rien
 */

void afficheGrille(int ** mat, int taille_t);

/* fonction : AFFICHEITERATION
 *
 * affiche la grille des itérations.
 *
 * en entrée : la matrice (int ** mat).
 *             la taille des matrices (int taille_t).
 * en sortie : rien
 */

void afficheIteration(int ** mat, int taille_t);

/* fonction : AFFICHEFLOODIT
 *
 * affiche le nom "floodit".
 *
 * en entrée : la couleur blanche (unsigned long wpx).
 *             la couleur noire (unsigned long bpx).
 *             la taille des matrices (int taille_t).
 * en sortie : rien
 */

void afficheFloodIt(unsigned long wpx, unsigned long bpx,int taille_t);

/* fonction : AFFICHEFIN
 *
 * affiche la fin du jeu [win/lose].
 *
 * en entrée : la matrice de jeu (int ** mat).
 *             la variable d'itération (int iteration).
 *             la couleur blanche (unsigned long wpx).
 *             la variable d'enclenchement du Cheat Mode (int cheat).
 *             la taille des matrices (int taille_t).
 * en sortie : rien
 */

void afficheFin(int ** mat, int iteration, unsigned long wpx, int cheat,int taille_t);

/* fonction : AFFICHEFIT
 *
 * affiche le nombre d'itération possible.
 *
 * en entrée : la variable d'itération (int iteration).
 *             la couleur blanche (unsigned long wpx).
 *             la couleur noire (unsigned long bpx).
 *             la variable du nombre d'itérations maximales (int iter_max).
 *             la taille des matrices (int taille_t).
 * en sortie : rien
 */

void afficheIt(int iteration, unsigned long wpx, unsigned long bpx, int iter_max, int taille_t);





































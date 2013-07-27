/* demineur_xlib.h
 *
 * Affichage graphique du programme demineur.
 *
 * Compilation MacOSX : gcc demineur_xlib.c -o demineur -L/opt/X11/lib -lX11 -pedantic -Wall -Wextra -ansi
 *
 */

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

void saisie(int *cheat,int *restart,int *deminage,int *voir);

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

void clique(int ** mat, int ** mat_t, int taille_t,int * verif_case,int * deminage);

/* fonction : AFFICHEGRILLE
 *
 * affiche la grille mat
 *
 * en entrée : la matrice de jeu (int ** mat).
 *             la taille des matrices (int taille_t).
 *             la couleur blanche (unsigned long wpx).
 * en sortie : rien
 */

void afficheGrille(int ** mat, int taille_t, unsigned long wpx);

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

void afficheMenu(int taille_t, int * deminage, unsigned long wpx, unsigned long bpx);

/* fonction : AFFICHEDEMINEUR
 *
 * affiche le nom du jeu pixélisé "DEMINEUR".
 *
 * en entrée : la couleur blanche (unsigned long wpx).
 *             la couleur noire (unsigned long bpx).
 *             la taille des matrices (int taille_t).
 * en sortie : rien
 */

void afficheDemineur(unsigned long wpx, unsigned long bpx,int taille_t);

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

void afficheFin(int ** mat,int ** mat_t, unsigned long wpx, int cheat,int taille_t);

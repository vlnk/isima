/* demineur_txt.h [ENTÊTE]
 *
 * Fonctions de bases du démineur (crée à partir de la version texte pour la version xlib).
 *
 */

/*gardien*/
#ifndef demineur_txt_H
#define demineur_txt_H

/*PROTOTYPES*/

/* Fonction : INITIALISERJOUEUR
 *
 * Initialise la matrice mat_t avec des -1
 *
 * En entrée : la matrice.
 *
 * En sortie : rien.
 */

void initialiserJoueur(int ** mat_t, int taille_t);

/* Fonction : INITIALISERJEU
 *
 * Initialise la matrice mat avec des 0
 *
 * En entrée : la matrice.
 *
 * En sortie : rien.
 */

void initialiserJeu(int ** mat, int taille_t);

/* Fonction : PLACERBOMBE
 *
 * Initialise la matrice mat en plaçant des bombes au hasard.
 *
 * En entrée : la matrice.
 *
 * En sortie : rien.
 */

void placerBombe(int ** mat,int nb_bombe, int taille_t, int germe);

/* fonction : FIN
 *
 * renvoie 1 si la grille est remplie, 0 sinon
 *
 * en entrée : la matrice
 * en sortie : rien
 */

int fin(int ** mat,int ** mat_t,int taille_t);

/* Fonction : REMPLIRJEU
 *
 * Remplie la grille de Jeu selon les règles du Démineur.
 *
 * En entrée : la matrice.
 *             les coordonées i et j de la matrice (int)*(int).
 *
 * En sortie : rien.
 */

void remplirJeu(int ** mat, int i, int j, int taille_t);

/* Fonction : REMPLIRJOUEUR
 *
 * Remplie la grille du Joueur selon les règles du Démineur.
 *
 * En entrée : la matrice.
 *             les coordonées i et j de la matrice (int)*(int).
 *
 * En sortie : rien.
 */

void remplirJoueur(int ** mat, int ** mat_t, int i, int j, int taille_t);

#endif

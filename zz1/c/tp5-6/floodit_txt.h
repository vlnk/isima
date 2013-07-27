/* floodit_txt.c
 *
 * Partie "texte" du programme floodit.
 *
 */

/*gardien*/
#ifndef floodit_txt_H
#define floodit_txt_H

/* fonction : INITIALISER
 *
 * initialise mat avec des couleurs aux hasard.
 *
 * en entrée : la matrice
 * en sortie : rien
 */

void initialiser(int ** mat,int germe,int taille_t);

/* fonction : FIN
 *
 * renvoie 1 si la grille est remplie, 0 sinon
 *
 * en entrée : la matrice
 * en sortie : rien
 */

int fin(int ** mat, int taille_t);

/* fonction : REMPLIR
 * Remplie la grille selon les règles de Flood It
 *
 * en entrée : la matrice
               l'ancienne couleur (int)
               les coordonées i et j de la matrice (int)*(int)
               la valeur de l'itération courante (int)

 * en sortie : rien
 */

void remplir(int ** mat, int old_color, int new_color, int i, int j, int iteration, int taille_t);

#endif

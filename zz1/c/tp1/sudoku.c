/**
 * \file sudoku.c
 * \brief Jeu du sudoku programmé en C
 * \author Valentin Laurent
 * \version 1.0
 * \date 3 octobre 2012
 *
 * Programmation du sudoku en C (TP1)
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define N 9
#define HORIZ 0
#define VERT 1
#define MODIF 0
#define BLOQUE 1
#define NB_CHIFFRE 10

#define RESET	0
#define BRIGHT 1
#define	WHITE	7
#define BLACK 0
#define RED	1
#define YELLOW 3

/** VARIABLES GLOBALES (grille test) */
int grille_test[N][N]={{1,2,3,4,5,6,7,8,9},{4,5,6,7,8,9,1,2,3},{7,8,9,1,2,3,4,5,6},{2,3,4,5,6,7,8,9,1},{5,6,7,8,9,1,2,3,4},{8,9,1,2,3,4,5,6,7},{3,4,5,6,7,8,9,1,2},{6,7,8,9,1,2,3,4,5},{9,1,2,3,4,5,6,7,8}};

/** 
 * \fn void textcolor(int attr, int fg, int bg)
 *
 * \brief Change la couleur du texte affiché
 * \param  attr Le format d'écriture
 * \param  bg La couleur d'arrière plan
 * \param  fg La couleur du texte
 *
 * \return Rien du tout
 *
 * \brief NB : le code pour permettre la coloration synthaxique est tiré du site http://www.linuxjournal.com/article/8603
 */

void textcolor(int attr, int fg, int bg)
{	
  char command[13];

	/** Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

/** 
 * \fn int initialiser (int m[][N][2])
 * \brief Initialise la grille de Sudoku.
 *
 * \param int grille[N][N][2] La grille de sudoku.
 * \return Modification de la grille (initialisation de tous les termes à 0) et la valeur 0.
 *
 */

int initialiser(int m[][N][2])
{

  /** VARIABLES LOCALES */
  int i,j;
 
  /** INITIALISATION */
  for ( i=0; i<N; i++ )
  {
    for ( j=0; j<N; j++ )
    {
      m[i][j][0]=0;
      m[i][j][1]=MODIF;
    }
  }
	
  return 0;
}

/**
 * \fn affiche void affiche(int m[][N][2])
 * \brief Affiche la grille de Sudoku.
 *
 * \param  grille[N][N][2] La grille de sudoku.
 * \return Rien du tout.
 */

void affiche(int m[][N][2])
{
	/** VARIABLES LOCALES */
  int i,j;
	
	/** AFFICHAGE */
	printf("\n");
	for(i=0 ; i<N; i++ )
	{

		if ((i!=3) && (i!=6))
		{
			printf(" ");
		}

		for(j=0 ; j<N; j++ )
		{

      /** affichage des valeurs */
			if (m[i][j][1] == BLOQUE)
      {
        textcolor(BRIGHT, RED, BLACK);
        printf(" %d ", m[i][j][0]);
        textcolor(RESET, WHITE, BLACK);
			}
      else
      {
        printf(" %d ", m[i][j][0]);
      }
       
      /** affichage graphique */
			if ((j == 2) | (j == 5))
			{
				printf(" ");
			}
			
			if (j == 8)
			{
				printf("\n");
			}	
		}

		if ((i == 2) | (i == 5))
			{
				printf("\n ");
			}
	}
	
  printf("\n\n");
  
}

/** \fn int generer(int m[][N][2], int germe)
 *  \brief Génère une grille de Sudoku.
 *
 *  \param int grille[N][N][2] La grille de Sudoku
 *  \param int germe Le germe.
 *  \return Le nombre d'éléments placés dans le tableau.
 */

int generer(int m[][N][2], int germe)
{
	/** VARIABLES LOCALES */
	int compt=0,i,j,k=0;

	srand(germe);

  while (k < NB_CHIFFRE)
  {
    i = rand()%N;
    j = rand()%N;
    m[i][j][0] = rand()%9 + 1;
    m[i][j][1] = BLOQUE;
    compt++;
    k++;
  }
  
  return compt;
}

/** \fn  generer2(int m[][N][2], int germe)
 *  \brief Remplit de 0 la grille test.
 *
 *  \param  grille[N][N][2] La grille de Sudoku
 *  \param  germe Le germe.
 *  \return Le nombre d'éléments placés dans le tableau.
 */

int generer2(int m[][N][2], int germe)
{
	/*VARIABLES LOCALES*/
	int compt=0,i,j,k=0;

	srand(germe);

  while (k < NB_CHIFFRE)
  {
    i = rand()%N;
    j = rand()%N;
    m[i][j][0] = 0;
    m[i][j][1] = MODIF;
    compt++;
    k++;
  }
			
  return compt;
}

/* \fn int saisir(int m[][N][2], int remp)
 * \brief Place la valeur saisie dans la grille.
 *
 * \param  grille[N][N][2] La grille de sudoku.
 * \param  remp Indique le nombre de cases remplies.
 * \return Le nombre d'éléments placés dans le tableau
 */

int saisir(int m[][N][2], int remp)
{
	/** VARIABLES LOCALES */
	int i_t, j_t, v_t, verif;
	char confirm_t;

	/** Demande de saisie coordonnée i */
	verif=1;
	do
	{
		printf("Indice i ? ");
		fflush(stdout);
		scanf("%d%*c",& i_t);

		if (((i_t >= 0) && (i_t < N)))
		{
			verif=0;
		}

	} while (verif==1);
	
	verif=1;

  /** Demande de saisie coordonée j */
	do
	{
		printf("Indice j ? ");
		fflush(stdout);
		scanf("%d%*c",&j_t);
 
		if (((j_t >= 0) & (j_t < N)))
		{
			verif=0;
		}

	} while (verif==1);

  /** condition : si la case est vide */
  if ((m[i_t][j_t][1] == MODIF) && (m[i_t][j_t][0]==0))
  {

    verif = 1;
    
    /** saisie de la valeur v */
    do
    {
			printf("Indice v ? ");
			fflush(stdout);
			scanf("%d%*c",&v_t);
		
      if (((v_t >= 1) & (v_t < (N+1))))
        {
          verif=0;
        }

		} while (verif!=0);

    m[i_t][j_t][0] = v_t;
    remp++;
    
  }
 
  /** condition : si la case est occupée par une valeur modifiable */
	else if ((m[i_t][j_t][1] == MODIF) && (m[i_t][j_t][0] != 0)) 
	{
		printf("La valeur deja placee est %d\nVoulez-vous la remplacer (Y ou N) ? ", m[i_t][j_t][0]);
		fflush(stdout);
		scanf("%c%*c",&confirm_t);

		if (confirm_t=='Y')
		{
			verif=1;

			/** saisie de la valeur v */
			do
			{
				printf("Indice v ? ");
				fflush(stdout);
				scanf("%d%*c",&v_t);
		
				if (((v_t >= 1) & (v_t < (N+1))))
					{
						verif=0;
					}

			} while (verif!=0);
	
			m[i_t][j_t][0] = v_t;
			remp++;
		}
	}

  /** condition : si la case est occupée par une valeur bloquée */
  else
  {
    printf("La valeur deja placee ne peut pas etre modifiee !\n");
		fflush(stdout);
  }

	return remp;
}

/** \fn int verifierLigneColonne(int m[][N][2], int num, int sens)
 *  \brief Vérifie si les lignes ou les colonnes sont correctes.
 *
 *  \param  grille[N][N][2] La grille de sudoku. 
 *  \param  num Le numero de la ligne ou colonne à vérifier.
 *  \param  sens Le numero de sens (0:HORIZ; 1:VERT)
 *  \return r "r" vaut 0 si la grille est correct, 1 sinon.
 */

int verifierLigneColonne(int m[][N][2], int num, int sens)
{
	/** VARIABLES LOCALES */
	int v,i,verif=0,r=0;

	for(v=1; v<(N+1); v++)
	{
		verif = 0;

		/** vérification des lignes */
		if (sens==0) 
		{
			for(i=0; i<N; i++)
			{
				if (m[i][num][0] == v)
				{
					verif++;
				}
			}	
		}

		/** vérification des colonnes */
		else
		{
			for(i=0; i<N; i++)
			{
				if (m[num][i][0] == v)
				{
					verif++;
				}
			}
		}

    if (verif!=1)
		{
			r=1;
			break;
		}	
	}
  
	return r;
}

/** \fn int verifierRegion(int m[][N][2],int k, int l).
 *  \brief Vérifie si la region est correcte.
 *  \param  grille[N][N][2] La grille de sudoku.
 *  \param  k Le numero de la ligne à vérifier.
 *  \param  l Le numero de la ligne à vérifier.
 *
 *  \return r "r" vaut 0 si la grille est correct, 1 sinon.
 */

int verifierRegion(int m[][N][2],int k, int l)
{

	/** VARIABLES LOCALES */

	int v=1,i,j,verif=0,r=0;

	do
	{
		/** vérifie la région (k,l) */
		for(i=k; (i< k+3); i++)
		{
			for(j=l; j< (l+3); j++)
			{
				if (m[i][j][0] == v)
				{
					verif=verif+1;
				}
			}
		}

    if (verif!=1)
	 	{
	 		r=1;
    }

    v++;
    verif=0;

  } while (v < 10);

	return r;
}	

/** \fn int verifierGrille(int m[][N][2])
 *  \brief Vérifie si la grille est correcte.
 *
 *  \param  grille[N][N][2]
 *  \return r "r" vaut 0 si la grille est correct, 1 sinon.
 */

int verifierGrille(int m[][N][2])
{
	/** VARIABLES LOCALES */
	int i,j,r=0;

	/** vérifie les lignes et les colonnes */
	for(i=0; i<N; i++)
 	{
    if (verifierLigneColonne(m,i,HORIZ) == 1)
      {
        r=1;
      }
    if (verifierLigneColonne(m,i,VERT) == 1)
      {
        r=1;
      }
 	}


	/** verifie les régions */
	for(i=0; i<N; i+=3)
	{
		for(j=0; j<N; j+=3)
		{
			if (verifierRegion(m,i,j)==1)
			{
				r=1;
			}
		}
  }
  
	return r;
}

/** \fn main
 *  \brief  Le programme de sudoku.
 * 
 *  \brief NB : les procédures pour tester la grille générée aléatoirement et la grille
 *     test de l'exemple sont en commentaires
 *
 */

int main (int argc, char *argv[])
{
  /** VARIABLES LOCALES */
  int grille[N][N][2];
  int remplissage=0, verif=1,i,j,n=N*N,g;

  /** Affichage & Initialisation */
  printf("SODOKU\n");
  initialiser(grille);

  /** Generer grille aléatoire */
  printf("germe ? ");
  fflush(stdout);
  scanf("%d%*c",&g);
  remplissage = generer(grille,g);
  
  affiche(grille);

  /*Test de grille_test*/
  /*for(i=0;i<N;i++)
  {
    for(j=0;j<N;j++)
    {  
      grille[i][j][0] = grille_test[i][j];
    }
  }
  
  printf("germe ? ");
  fflush(stdout);
  scanf("%d%*c",&g); 
  remplissage = n - generer2(grille,g);
	affiche(grille);*/
  
  printf("Nombre de chiffre place = %d\n",remplissage);

  /** boucle du jeu */
	do
	{
    remplissage = saisir(grille,remplissage);
	  affiche(grille);  
  	printf("Nombre de chiffre place = %d\n",remplissage);
  
    if ((remplissage >= n) && (verifierGrille(grille) != 1))
    {
      verif=0;
    }
	
	} while (verif!=0);

	printf("GAGNE !\n");
	return 0;
}

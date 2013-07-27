#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TMAX 1000000
/*#define TMOTUS 16*/
#define TMOTS 6

/*Variable globale : impossibilité de transférer un tableau en variable locale*/
/*char dico[TMOTUS][TMOTS];*/


/*PROBLEME SUR LE VERIF*/
int verif(char tab[],int nbr)
{
	int i,r=0;
	
	if (strlen(tab) == TMOTS-1) 
	{
	/*	for(i=0;i<TMOTS;i++)
		{	
			if  ((tab[i]!='a') || (tab[i]!='b') || (tab[i]!='c') || (tab[i]!='d') || (tab[i]!='e') || (tab[i]!='f') || (tab[i]!='g') || (tab[i]!='h') || (tab[i]!='i') || (tab[i]!='j') || (tab[i]!='k') || (tab[i]!='l') || (tab[i]!='m') || (tab[i]!='n') || (tab[i]!='o') || (tab[i]!='p') || (tab[i]!='q') || (tab[i]!='r') || (tab[i]!='s') || (tab[i]!='t') || (tab[i]!='u') || (tab[i]!='v') || (tab[i]!='w') || (tab[i]!='x') || (tab[i]!='y') || (tab[i]!='z') || (tab[i]!='A') || (tab[i]!='B') || (tab[i]!='C') || (tab[i]!='D') || (tab[i]!='E') || (tab[i]!='F') || (tab[i]!='G') || (tab[i]!='H') || (tab[i]!='I') || (tab[i]!='J') || (tab[i]!='K') || (tab[i]!='L') || (tab[i]!='M') || (tab[i]!='N') || (tab[i]!='O') || (tab[i]!='P') || (tab[i]!='Q') || (tab[i]!='R') || (tab[i]!='S') || (tab[i]!='T') || (tab[i]!='U') || (tab[i]!='V') || (tab[i]!='W') || (tab[i]!='X') || (tab[i]!='Y') || (tab[i]!='Z'))
			{
				r=1;
			}
		}*/
	}	
  else
  {
	  r=1;
  }
	return r;
} 
			

int dictionnaire2(char dico[][TMOTS])
{

	FILE * Dictionnaire;
	char nom[50] = "/Users/Valink/c/dictionnaire.txt";
	int i=0,j=0,nbr;
	char tmp[TMAX];


	/*Ouverture du fichier et scanf du nombre de mot et des mots du dicyionnaire*/
	Dictionnaire = fopen(nom, "r");
	if (Dictionnaire == NULL)
	{
		printf("Problème d'ouverture");
	}
	else
	{
		fscanf(Dictionnaire, "%d",&nbr);
		/*printf("Il y a %d mots\n",nbr);*/

		do
		{
			fscanf(Dictionnaire,"%s",tmp);
			/*printf("%s\n",tmp);*/
			
			if (verif(tmp,nbr) == 0)
			{
				strcpy(dico[j],tmp);
				j++;
			}
		} while (!feof(Dictionnaire));

		fclose(Dictionnaire);
	
		/*for(i=0;i<j;i++)
		{
			printf("%s\n",dico[i]);
		}*/

	}
	/*printf("Fin\n");*/
	return j;
}

int dictionnaire1(char dico[][TMOTS])
{
	/*Variables locales DICTIONNAIRE*/
	FILE * listeMots;
	char nom[40] = "/Users/Valink/c/listeMots.txt";
	int nbr, i;

	/*Ouverture du fichier et scanf du nombre de mot et des mots du dicyionnaire*/
	listeMots = fopen(nom, "r");
	if (listeMots == NULL)
	{
		printf("Problème d'ouverture");
	}
	else
	{
		fscanf(listeMots,"%d",&nbr);
  	/*printf("Il y a %d mots dans le dictionnaire\n\n",nbr);*/
		
		/*Les mots du dictionnaire sont copiés dans le tableau dico*/
		for(i=0;i<=nbr;i++)
		{
			fscanf(listeMots,"%s",dico[i]);
		}

		fclose(listeMots);
	}

	/*for(i=0;i<TMOTUS;i++)
	{
		printf("%s\n",dico[i]);
	}

	for(i=0;i<TMOTUS+1;i++)
	{
		strcpy(tab[i],dico[i]);
  }*/

	return nbr;
}

int motus()
{	
	/*Variables locales MOTUS*/
  /*char tab[TMOTUS][TMOTS]={"AGENT", "AGILE", "AIDER", "AIMER", "BADGE", "BIERE", "CABLE", "CACHE", "CACAO", "GEEEK", "GRIPE", "ISIMA", "LAMPE", "LARGE", "MAGIE", "POULE"};*/
  char dico[TMAX][TMOTS];
	int r,i,nbr;
  int quota;
  int len_mot;
  int len_devine;
  char mot[TMOTS], devine[TMOTS];

  nbr = dictionnaire2(dico);

	/*Choix du mot aléatoire*/
  srand(time(0));
  r = rand()%nbr;

	strcpy(devine,dico[r]);

  /*for(i = 0;i <= TMOTS; i++)
  {
    devine[i]=dico[r][i];
  }*/

	/*Saisi du quota et du mot par le joueur*/
  len_devine = strlen(devine);
	/*printf("%s et %d\n", devine, len_devine);*/

  printf("\n   ############################\n");
	printf("   #  Bienvenue dans MOTUS !  #\n   ############################\n\nVeuillez saisir votre quota : ");
  fflush(stdout);
  scanf("%d%*c", &quota);
  printf("Veuillez saisir un mot : ");
  fflush(stdout);
  scanf("%s%*c", mot);
  len_mot = strlen(mot);
  printf("Taille de votre mot : %d\n\n", len_mot);
  
  do
  {
		
		/*Vérification du quota*/
		quota--;
		if (quota <= 0)
		{
			for(i = 0; i<101; i++)
			{
				printf("PERDU =(\nQuota épuisé ! \nLe mot était %s.",devine);
			}
			return 0;
		}

		/*Vérification de la longueur du mot*/
    else if (len_mot > len_devine)
    {
      printf("PERDU =(\nVotre mot est trop long !\n");
      return 0;
    }
    else if (len_mot < len_devine)
    {
      printf("PERDU =(\nVotre mot est trop court !\n");
      return 0;
    }

		/*Vérification des lettres du mot*/
    else if (strcmp(mot, devine) != 0)
    {
      for(i = 0;i < len_mot; i++)
      {
        if (mot[i]-devine[i] != 0)
				{
					printf("-");
        }
        else
				{	
					printf("%c", devine[i]);
        }
			}

				/*Redemande de saisi (si mot incorrect)*/
  			printf("\n\nFichtre !\nATTENTION : votre quota vaut %d.\nVeuillez saisir un mot : ",quota);
  			fflush(stdout);
  			scanf("%s%*c", mot);
  			printf("\n");
		}
	} while (strcmp(mot, devine) != 0);

	/*Fin de boucle si le mot est correct*/
	printf("MO\nMO\nMOTUS !\n\n");
	printf("   BBB  RRR  AAA  V V  OOO  !!\n   B B  R R  A A  V V  O O  !!\n   BB   RRR  AAA  V V  O O  !!\n   B B  RR   A A  V V  O O   \n   BBB  R R  A A   V   OOO  !!\n\n"); 
	printf("Le mot à deviner était bien %s.\n", devine);
  return 0;
}

int main()
{
	motus();
  return 0;
}

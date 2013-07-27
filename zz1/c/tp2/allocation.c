/*
 * allocation.c
 *
 * auteur : Valentin Laurent
 *
 */

#include <stdio.h>
#include <stdlib.h>
#define TAILLE 1000000

void allocation()
{
  /*variables locales*/
  float *t;
  int i;

  t = (float *) malloc(TAILLE*sizeof(float));

  if (t == NULL)
  {
    printf("allcation de mémoire impossible");
  }
  else
  {
    for(i=0;i<TAILLE;i++)
    {
      t[i] = i*i;
      printf("t[%d] = %f\n", i, t[i]);
    }
  }

  free(t);
}

int main()
{
  allocation();
  return 0;
}

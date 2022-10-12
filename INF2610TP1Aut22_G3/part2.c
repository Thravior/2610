/*
 * processlab - part2.c
 *
 * Ecole polytechnique de Montreal, GIGL, Automne  2022
 * Gagnon Mathias 2115246 sec.3
 * Poellhuber Antoine 1990157 sec. 3
 */
// --------------------------------------------------

#include "./libprocesslab/libprocesslab.h"

#define m 1000000
// question2 calcule la somme des m premiers nombres naturels 1+2+...+m

// nb est le nombre de threads qui vont contribuer au calcul
#define nb 4

//tableau somme est utilisé pour le calcul des sommes patielles par les threads
long somme[nb];


// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------
#include <pthread.h>
// -------------------------------------------------

// fonction exécutée par chaque thread créé
void* contribution(void* p)
{
  int i = *((int*) p); 
  somme[i] = 0;
  int base = m/nb;
  int depart = base * i;
  int fin = depart + base;
  for (int n = i * base; n<((i+1)*base); ++n){
    somme[i] += n;
  }

  pthread_exit(NULL);
  return NULL;
}


void question2( )
{

  pthread_t threads[nb];

  for (int i = 0; i< nb; ++i) {
    pthread_create(&threads[i], NULL, contribution, (void*) &i);
    pthread_join(threads[i], NULL);
  }

  long sommeT = 0;
  for(int i = 0; i < nb; ++i){
    sommeT += somme[i];
  }
  printf("Somme= %ld\n", somme[0]);
}

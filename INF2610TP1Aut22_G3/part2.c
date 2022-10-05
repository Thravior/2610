/*
 * processlab - part2.c
 *
 * Ecole polytechnique de Montreal, GIGL, Automne  2022
 * vos noms, prénoms et matricules
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

// -------------------------------------------------


// fonction exécutée par chaque thread créé
void* contribution(void*p)
{
    // TODO

  return NULL;
}


void question2( )
{
  for (int i = 0; i<= nb; ++i) {
    if(fork() ==0) {
      contribution(somme);
      _exit(0);
    }
  }
    
}


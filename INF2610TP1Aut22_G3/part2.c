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

// -------------------------------------------------


// fonction exécutée par chaque thread créé
void* contribution(int p)
{
  const int section = p;
  long sommeP = 0;
  int separation = m/nb;
  int depart = section*separation;
  for (int i = depart ; i < depart + separation ; ++i) {
    sommeP += i;
  }
  // section * m /nb +1 a section +1) m*nb
  *(somme) = sommeP;
  return NULL;
}


v{
  int i = 0;
  if(fork() == 0) {
      contribution(++i);
      exit(0);
  } else if(fork() == 0) {
      contribution(++i);
      exit(0);
  }
  while (wait(NULL) >0){}
  long sommeT = 0;
  for (int i = 0; i< nb; ++i) {
    sommeT += somme[i];
  }
  printf("Somme=%ld\n", sommeT);
}

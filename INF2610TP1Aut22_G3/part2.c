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
#include <sys/mman.h>
// -------------------------------------------------

// fonction exécutée par chaque thread créé
void* contribution(int p)
{
  somme[p] = 0;
  int base = m/nb;
  int depart = base * p;
  int fin = depart + base;
  for (int n = p* base; n<((p+1)*base); ++n){
    somme[p] += n;
  }
  printf("Somme tableau= %ld\n", somme[p]);

  return NULL;
}

off_t taille = nb*sizeof(long);
const char* nom = "test";
void question2( )
{
  int fd = shm_open(nom, O_RDWR | O_CREAT, 0666); // share tableau
  ftruncate(fd, taille);
  long* somme = (long*) mmap(somme, taille, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
  close(fd);

  for (int i = 0; i< nb; ++i) {
    if(fork() == 0) {
      contribution(i);
      munmap(somme,taille);
      _exit(0);
    }
  }

  while(( wait(NULL)) > 0 ) {
  }

  long sommeT = 0;
  for (int i = 0; i < nb; ++i){
    sommeT += somme[i];
  }
  printf("Somme= %ld\n", somme[0]);
}

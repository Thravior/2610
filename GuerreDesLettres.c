

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
//...
int* tampon;

sem_t libre;
sem_t occupe;
sem_t mutex;

int tailleTamponGlobale;

bool flag_de_fin = false; 

int sommeChiffreProduit = 0;
int sommeChiffreConsommer = 0;

int cibleProducteur;
int cibleConsommateur;

// fonction exécutée par les producteurs
void* producteur( void* pid) {
   
   //printf("Somme chiffre recuperee (consommateur) : %n\n", sommeChiffreConsommer);
   
   srand(time(NULL));
   int nombreDeChiffre = 0;
   while(1) {
      sem_wait(&libre);
      sem_wait(&mutex);

      nombreDeChiffre++;

      int chiffreAleatoire = (rand() % 9) + 1;
      sommeChiffreProduit += chiffreAleatoire;
      tampon[cibleProducteur] = chiffreAleatoire;

      cibleProducteur++;
      cibleProducteur %= tailleTamponGlobale;

      sem_post(&mutex);
      sem_post(&occupe);

      if(flag_de_fin){
         break;
      }
   }
   printf("Nombres produits - %d\n", nombreDeChiffre);
   pthread_exit((void*)nombreDeChiffre);
   return NULL;             
}
// fonction exécutée par les consommateurs

void* consommateur(void *cid) {
   // ...

   sommeChiffreConsommer = 0;

   int nombreDeChiffre = 0;
   while(1) {
      sem_wait(&occupe);
      sem_wait(&mutex);

      int valeurTampon = tampon[cibleConsommateur];
      if(valeurTampon > 0) nombreDeChiffre++;

      sommeChiffreConsommer += valeurTampon;

      cibleConsommateur++;
      cibleConsommateur %= tailleTamponGlobale;

      sem_post(&mutex);
      sem_post(&libre);
      if(valeurTampon == 0) {
         break;
      }
   }
   printf("Nombres consomme - %d\n", nombreDeChiffre);
   pthread_exit((void*)nombreDeChiffre);
  return NULL;   
  
}


void setFlag() {
   flag_de_fin = true;
}

// fonction main
int main(int argc, char* argv[]) {
   /* Les paramètres du programme sont, dans l’ordre :
      le nombre de producteurs, le nombre de consommateurs
      et la taille du tampon.*/
    
  // ..
  signal(SIGALRM, setFlag);
  int nombreProducteur = atoi(argv[1]);
  int nombreConsommateur = atoi(argv[2]);
  int tailleTampon = atoi(argv[3]);
  
  tailleTamponGlobale = tailleTampon;

  sem_init(&libre,0,tailleTampon);
  sem_init(&occupe,0,0);
  sem_init(&mutex,0,1);
  
  tampon = malloc(tailleTampon * sizeof(int));
  pthread_t *tid1 = malloc(nombreProducteur * sizeof(pthread_t));
  pthread_t *tid2 = malloc(nombreConsommateur * sizeof(pthread_t));
  for(int i = 0; i < nombreProducteur; i++){
   pthread_create(&tid1[i], NULL, producteur, (void*)i);
  }
  for(int j = 0; j < nombreConsommateur; j++){
   pthread_create(&tid2[j], NULL, consommateur, (void*)j);
  }

  alarm(1.0);

  for(int i = 0; i < nombreProducteur; i++){
   pthread_join(tid1[i], NULL );
  }
  

  for(int j = 0; j < nombreConsommateur; j++){
      int consommation = -1;
      while (consommation != 0)
      {
         sem_getvalue(&occupe, &consommation);
      }
      
      sem_wait(&libre);
      sem_wait(&mutex);
      tampon[cibleProducteur] = 0;
      cibleProducteur++;
      cibleProducteur %= tailleTamponGlobale;
      sem_post(&mutex);
      sem_post(&occupe);
  }
      printf("Somme des chiffre produit : %d \n", sommeChiffreProduit);
      printf("somme des chiffre consomme : %d \n", sommeChiffreConsommer);

    return 0;
}

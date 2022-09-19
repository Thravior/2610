/*
 * Ecole polytechnique de Montreal - GIGL
 * Automne  2022
 * Initlab - part1.c
 * 
 * ajoutez vos noms, prénoms, matricules et votre section de laboratoire
 * Gagnon Mathias 2115246 sec.3
 * Poellhuber Antoine 1990157 sec. 3
 */


// TODO
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
// -------------------------------------------------

int main () {
   int file;
   char buff[1];
   const char msg[] = "Saisissez votre texte suivi de CTRL-D :\n";
   const char msg2[] = "Appel système open a échoué\n";

   file = open("./output2.txt", O_TRUNC | O_WRONLY);

   if(file < 0)
   {
   write(STDOUT_FILENO, msg2, sizeof(msg2)-1);
      exit(1);             
   }
   write(STDOUT_FILENO, msg, sizeof(msg)-1);
   while(read(0, buff,1)){
       write(file, buff,1);
       
   }
   close(file);
    return 0;
}
    

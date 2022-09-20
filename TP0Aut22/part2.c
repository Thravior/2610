/*
 * Ecole polytechnique de Montreal - GIGL
 * Automne  2022
 * Initlab - part2.c
 *
 * ajoutez vos noms, prénoms et matricules
*/
#include <stdio.h>
#include <stdlib.h>
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------
// TODO
#include <unistd.h>
#include <fcntl.h>
extern FILE *stdout;
const char msg[] = "77dbcb01f571f1c32e196c3a7d27f62e (printed using write)\n";
const char msg2[] = "77dbcb01f571f1c32e196c3a7d27f62e (printed using fprintf)\n";
// -------------------------------------------------
void part21 ()
{
    for(int i = 0; i < 55 ; i++){
        printf("%c", msg[i]);
    }
    write(STDOUT_FILENO, msg2, sizeof(msg2)-1);
}

void part22 ()
{
    setvbuf(stdout, NULL,_IONBF,1024);
    for(int i = 0; i < 55 ; i ++){
        printf("%c", msg[i]);
    }
    write(STDOUT_FILENO, msg2, sizeof(msg2)-1);

}



int main (int argc, char* argv[])
{
    
    if (argc!=2)
    {   printf("Le programme a un seul paramètre : 1 ou 2\n");
        return 1;
    }
    switch (atoi(argv[1])) {
         case 1:        part21();
                        break;
         case 2:        part22();
                        break;
        default:        printf(" Le paramètre du programme est invalide\n");
                        return 1;
    }
    return 0;
}


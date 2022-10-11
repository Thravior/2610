/*
 * processlab - part1.c
 *
 * Ecole polytechnique de Montreal, GIGL, Automne  2022
 * Gagnon, Mathias - 2115246 sec. 3
 * Poellhuber Antoine - 1990157 sec. 3
*/

#include "libprocesslab/libprocesslab.h"

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------

// -------------------------------------------------

void question1()
{
    int process = 0;
    int count;
    int rep;
    registerProc(getpid(), getppid(), 0, 0);
    if(fork() == 0) {        //1.1
        count = 1;
        registerProc(getpid(), getppid(), 1, 1);
        if (fork() == 0){   //1.2
            registerProc(getpid(), getppid(), 2, 1);
            _exit(1);
        }
        while(( wait(&rep)) > 0 ) {
            count += WEXITSTATUS(rep);
        }
        _exit(count);
    }
    if(fork() == 0) {        //2.1
        count = 1;
        registerProc(getpid(), getppid(), 1, 2);
        if (fork() == 0){   //2.2
            registerProc(getpid(), getppid(), 2, 2);
            _exit(1);
        }
        if (fork() == 0){   //2.3
            registerProc(getpid(), getppid(), 2, 3);
            _exit(1);
        }
        while(( wait(&rep)) > 0 ) {
            count += WEXITSTATUS(rep);
        }
        _exit(count);
    }
    if(fork() == 0) {        //2.1
        count = 1;
        registerProc(getpid(), getppid(), 1, 3);
        if (fork() == 0){   //2.2
            registerProc(getpid(), getppid(), 2, 4);
            _exit(1);
        }
        if (fork() == 0){   //2.3
            registerProc(getpid(), getppid(), 2, 5);
            _exit(1);
        }
        if (fork() == 0){   //2.4
            registerProc(getpid(), getppid(), 2, 6);
            _exit(1);
        }
        while(( wait(&rep)) > 0 ) {
            count += WEXITSTATUS(rep);
        }
        _exit(count);
    }
    count = 0;
    while(( wait(&rep)) > 0 ) {
            count += WEXITSTATUS(rep);
    }
    printf("Nombre d'enfants: %d\n", count);
    printProcRegistrations();
    execlp("ls", "ls", "-l", NULL);
}

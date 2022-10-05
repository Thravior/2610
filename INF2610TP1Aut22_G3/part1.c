/*
 * processlab - part1.c
 *
 * Ecole polytechnique de Montreal, GIGL, Automne  2022
 * vos noms, prénoms et matricules
*/

#include "libprocesslab/libprocesslab.h"

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------

// -------------------------------------------------
int count = 0;
void question1()
{
    pid_t child;
    registerProc(getpid(), getppid(), 0, 0);
    if(fork() == 0) {        //1.1
        count = 1;
        registerProc(getpid(), getppid(), 1, 1);
        if (fork() == 0){   //2.1
            registerProc(getpid(), getppid(), 2, 1);
            _exit(0);
        }
        _exit(2);
    }
    if(fork() == 0) {        //1.2
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
        while( (child = wait(NULL)) > 0) {
        }
        _exit(3);
    }
    if(fork() == 0) {        //1.3
        count = 1;
        registerProc(getpid(), getppid(), 1, 3);
        if (fork() == 0){   //2.2
            registerProc(getpid(), getppid(), 2, 4);
            _exit(0);
        }
        if (fork() == 0){   //2.3
            registerProc(getpid(), getppid(), 2, 5);
            _exit(0);
        }
        if (fork() == 0){   //2.4
            registerProc(getpid(), getppid(), 2, 6);
            _exit(0);
        }
        while( (child = wait(NULL)) > 0) {
        }
        _exit(4);
    }
    while( ( = wait(&)) > 0) {
        int childCount = WEXITSTATUS(child);
        printf("exit status was %d\n", childCount);
        count += childCount;
    }
    printf("Count=%d\n", count);
    printProcRegistrations();
    _exit(0);
}


#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {    
    if (argc != 3) return 1;

    pid_t target = atoi(argv[1]);
    char *msg = argv[2];

    if (strlen(msg) > 8) return 1;
//Es1 usa una union locale come "ponte" per copiare il messaggio nella "faccia" stringa e poi assegnare la "faccia" puntatore alla struttura sigval
    union {
        char s[8];
        void *p;
    } convert;

    memset(&convert, 0, 8);
    memcpy(convert.s, msg, strlen(msg));// Copiamo il messaggio nella "faccia" stringa della nostra union

    union sigval sv;
    sv.sival_ptr = convert.p; // Assegnamo la "faccia" puntatore della nostra union

    sigqueue(target, SIGUSR1, sv);

    printf("Messaggio '%s' inviato con successo al PID %d.\n", msg, target);
    return 0;
}
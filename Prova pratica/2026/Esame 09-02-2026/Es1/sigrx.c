#define _POSIX_C_SOURCE 199309L
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


void handler(int sig, siginfo_t *info, void *context) {
    union {
        char s[8];
        void *p;
    } convert;

    convert.p = info->si_value.sival_ptr;

    printf("Messaggio ricevuto: %s\n", convert.s);
}

int main() {
    printf("PID sigrx: %d\n", getpid());


    struct sigaction sa;
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO; // Fondamentale per dire al kernel di passare il payload


    sigaction(SIGUSR1, &sa, NULL);

    
    printf("In attesa di segnali...\n");
    while (1) {
        pause(); 
    }

    return 0;
}
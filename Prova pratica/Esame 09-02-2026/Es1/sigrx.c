#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

// L'handler avanzato che cattura il segnale
void handler(int sig, siginfo_t *info, void *context) {
    // Ricreiamo la union per fare il processo inverso
    union {
        char s[8];
        void *p;
    } convert;

    // Estraiamo i 64 bit dal payload del segnale e li mettiamo nel nostro puntatore
    convert.p = info->si_value.sival_ptr;

    // Stampiamo i caratteri. 
    // Usiamo "%.8s" per dire a printf di fermarsi massimo all'ottavo carattere,
    // evitando segmentation fault qualora il messaggio di 8 char non avesse il '\0' finale.
    printf("Messaggio ricevuto: %.8s\n", convert.s);
}

int main() {
    // 1. Stampa il proprio PID
    printf("PID sigrx: %d\n", getpid());

    // 2. Prepara la struttura sigaction
    struct sigaction sa;
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO; // Fondamentale per dire al kernel di passare il payload
    sigemptyset(&sa.sa_mask); // Nessun segnale bloccato durante l'esecuzione dell'handler

    // 3. Registra l'handler per SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Errore in sigaction");
        exit(EXIT_FAILURE);
    }

    printf("In attesa di segnali...\n");

    // 4. Ciclo infinito di attesa passiva
    while (1) {
        pause(); 
    }

    return 0;
}
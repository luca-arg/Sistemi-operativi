#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t ack_received = 0;

void handle_ack(int sig) {
    ack_received = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    
    pid_t pid = atoi(argv[1]);
    char *msg = argv[2];
    int len = strlen(msg) + 1;
    


    struct sigaction sa;
    sa.sa_handler = handle_ack;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);// se il processo riceve un segnale SIGUSR1, la funzione handle_ack viene chiamata per impostare ack_received a 1, indicando che è stata ricevuta una conferma di ricezione del bit precedente
    
    sigset_t mask, oldmask;// sono array di bit che rappresentano i segnali, usati per bloccare e sbloccare i segnali durante l'invio dei bit del messaggio. In questo caso, il processo blocca il segnale SIGUSR1 durante l'invio dei bit e lo sblocca solo quando è in attesa di una conferma di ricezione (ack) dal processo destinatario.
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);// blocca il segnale SIGUSR1, salvando la vecchia maschera dei segnali in oldmask. In questo modo, il processo non riceverà il segnale SIGUSR1 durante l'invio dei bit del messaggio, evitando di interrompere il processo di invio. Quando è in attesa di una conferma di ricezione (ack), il processo utilizza sigsuspend(&oldmask) per sospendersi e attendere la ricezione del segnale SIGUSR1, che sbloccherà il processo e permetterà di continuare con l'invio dei bit successivi.
    
    for (int i = 0; i < len; i++) {
        char c = msg[i];
        for (int bit = 0; bit < 8; bit++) {
            ack_received = 0;
            
            if ((c >> bit) & 1) {
                kill(pid, SIGUSR2);
            } else {
                kill(pid, SIGUSR1);//
            }
            
            while (!ack_received) {
                sigsuspend(&oldmask);
            }
        }
    }
    
    return 0;
}
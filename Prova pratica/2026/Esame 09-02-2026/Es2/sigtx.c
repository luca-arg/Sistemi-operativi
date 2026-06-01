#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>


volatile sig_atomic_t ack_ricevuto = 0;
// Quando arriva SIGUSR2, scatta questo handler e fa scattare il semaforo a 1
void ack_handler() {
    ack_ricevuto = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    
    pid_t pid = atoi(argv[1]);
    char *msg = argv[2];
    
   
    int len = strlen(msg); 
    int inviati = 0; // Contatore dei byte già spediti
    
    // Prepariamoci a ricevere l'ACK (SIGUSR2)
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = ack_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR2, &sa, NULL);
    
    union sigval value;
    
    // Ciclo finché non abbiamo inviato tutti i byte
    while (inviati < len) {
        value.sival_ptr = NULL;
        
        int da_inviare = (len - inviati > 8) ? 8 : (len - inviati);
        
        memcpy(&value.sival_ptr, msg + inviati, da_inviare);
        
        ack_ricevuto = 0;
        sigqueue(pid, SIGUSR1, value);
        
        // Aspettiamo fermi qui finché il ricevitore non ci manda SIGUSR2
        while (ack_ricevuto == 0) {
            pause();
        }
        
        inviati = inviati + da_inviare;
    }
    
    printf("\nMessaggio inviato tutto!\n");
    return 0;
}
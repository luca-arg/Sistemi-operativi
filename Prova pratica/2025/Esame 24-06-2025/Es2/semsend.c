#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
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
    sa.sa_flags = 0;
    sa.sa_handler = handle_ack;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    
    for (int i = 0; i < len; i++) {
        char c = msg[i];
        for (int bit = 0; bit < 8; bit++) {
            ack_received = 0;
            
            usleep(10000); 
            
            if ((c >> bit) & 1) {
                kill(pid, SIGUSR2);
            } else {
                kill(pid, SIGUSR1);
            }
            
            while (!ack_received) {
                sigsuspend(&oldmask);
            }
        }
    }
    
    return 0;
}
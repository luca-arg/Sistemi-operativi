#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

volatile sig_atomic_t bit_count = 0;
volatile sig_atomic_t current_char = 0;

void handler(int sig, siginfo_t *info, void *ptr) {
    if (sig == SIGUSR2) {
        current_char |= (1 << bit_count); // 00000000  1) 00000001  2)00000001  ... 7)01000001   8)01000001
    }
    
    bit_count++;
    
    if (bit_count == 8) {
        if (current_char == '\0') {
            putchar('\n');
        } 
        else {
            putchar(current_char);
        }
        bit_count = 0;
        current_char = 0;
    }
    
    kill(info->si_pid, SIGUSR1);
}


int main() {
    printf("%d\n", getpid());

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    
    while(1) {
        pause();
    }
    
    return 0;
}
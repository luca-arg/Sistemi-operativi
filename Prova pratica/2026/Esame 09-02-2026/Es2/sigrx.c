#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void handler(int sig, siginfo_t *info, void *ucontext) {
    char msg[9];
    memset(msg, 0, 9);
    memcpy(msg, &(info->si_value.sival_ptr), 8);
    
    write(STDOUT_FILENO, msg, strlen(msg));// Stampo il messaggio appena ricevuto direttamente sullo standard output 
    
    kill(info->si_pid, SIGUSR2);

    if (strlen(msg) < 8) {
        write(STDOUT_FILENO, "\n", 1);
    }
}

int main() {
    printf("%d\n", getpid());

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO; 
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    
    sigaction(SIGUSR1, &sa, NULL);
    
    while(1) {
        pause();
    }
    return 0;
}
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void handler(int sig, siginfo_t *info, void *ptr) {
    char msg[9];
    memset(msg, 0, 9);
    memcpy(msg, &(info->si_value.sival_ptr), 8);
    printf("%s\n", msg);
}

int main() {
    printf("%d\n", getpid());

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    
    sigaction(SIGUSR1, &sa, NULL);
    
    while(1) {
        pause();
    }
    return 0;
}
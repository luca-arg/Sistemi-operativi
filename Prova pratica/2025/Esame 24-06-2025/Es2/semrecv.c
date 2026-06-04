#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define MAX_CLIENTS 64
#define MAX_MSG 1024

typedef struct {
    pid_t pid;
    int bit_count;
    char current_char;
    char buffer[MAX_MSG];
    int buf_idx;
} Client;



Client clients[MAX_CLIENTS];
int num_clients = 0;

void handler(int sig, siginfo_t *info, void *ptr) {
    pid_t sender_pid = info->si_pid;
    int idx = -1;
    
    // Cerca il sender nella lista dei sender attivi
    for (int i = 0; i < num_clients; i++) {
        if (clients[i].pid == sender_pid) {
            idx = i;
            break;
        }
    }
    
    // Se il sender non è presente, aggiungilo alla lista
    if (idx == -1) {
        if (num_clients >= MAX_CLIENTS) return;
        idx = num_clients;
        clients[idx].pid = sender_pid;
        clients[idx].bit_count = 0;
        clients[idx].current_char = 0;
        clients[idx].buf_idx = 0;
        num_clients++;
    }
    
    if (sig == SIGUSR2) {
        clients[idx].current_char |= (1 << clients[idx].bit_count);
    }
    
    clients[idx].bit_count++;
    
    if (clients[idx].bit_count == 8) {

        char c = clients[idx].current_char;
        clients[idx].buffer[clients[idx].buf_idx++] = c;
        
        if (c == '\0' || clients[idx].buf_idx == MAX_MSG - 1) {
            clients[idx].buffer[clients[idx].buf_idx] = '\0';

            printf("[%d]: %s\n", clients[idx].pid, clients[idx].buffer);
            clients[idx].buf_idx = 0;
        }
        
        clients[idx].bit_count = 0;
        clients[idx].current_char = 0;
    }
    
    kill(sender_pid, SIGUSR1);
}



int main() {
    printf("%d\n", getpid());

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
    
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    
    while(1) {
        pause();
    }
    
    return 0;
}
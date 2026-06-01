#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    
    pid_t pid = atoi(argv[1]);// il pid del processo destinatario convertito da stringa a intero
    char *msg = argv[2];// il messaggio da inviare al processo destinatario
    
    if (strlen(msg) > 8) {
        return 1;
    }
    
    union sigval value;
    value.sival_ptr = NULL;
    //Es1bis opera direttamente sull'indirizzo di sival_ptr: prima lo azzera con memset e poi ci copia il messaggio con memcpy, senza usare una union "ponte" come nell'Es1
    memset(&value.sival_ptr, 0, sizeof(value.sival_ptr));
    memcpy(&value.sival_ptr, msg, strlen(msg));// copia il messaggio nella struttura sigval
    
    sigqueue(pid, SIGUSR1, value);
    
    return 0;
}
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("--- PROCESSO ATTIVO ---\n");
    printf("Il mio PID e': %d\n", getpid());
    
    for (int i = 0; i < argc; i++) {
        printf("Argomento %d: %s\n", i, argv[i]);
    }
    
    printf("Vado a dormire per 60 secondi...\n\n");
    sleep(60);
    
    return 0;
}
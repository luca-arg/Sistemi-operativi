#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Controllo sul numero di argomenti
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <pid> <messaggio_max_8_char>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t target = atoi(argv[1]);
    char *msg = argv[2];

    // Controllo stringente sulla lunghezza massima
    if (strlen(msg) > 8) {
        fprintf(stderr, "Errore: il messaggio non puo' superare gli 8 caratteri.\n");
        exit(EXIT_FAILURE);
    }

    // La union identica a quella vista a lezione
    union {
        char s[8];
        void *p;
    } convert;

    // Puliamo la memoria della union (utile se la stringa è < 8 caratteri)
    memset(&convert, 0, sizeof(convert));
    
    // Copiamo la stringa nella nostra union
    memcpy(convert.s, msg, strlen(msg));

    // Prepariamo la struttura nativa di sistema per il payload del segnale
    union sigval sv;
    sv.sival_ptr = convert.p; // Assegnamo la "faccia" puntatore della nostra union

    // Invio del segnale SIGUSR1 accodando il valore
    if (sigqueue(target, SIGUSR1, sv) == -1) {
        perror("Errore in sigqueue");
        exit(EXIT_FAILURE);
    }

    printf("Messaggio '%s' inviato con successo al PID %d.\n", msg, target);
    return 0;
}
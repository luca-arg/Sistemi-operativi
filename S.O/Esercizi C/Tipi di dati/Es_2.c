#include<stdio.h>      // Libreria standard per input/output (printf, scanf, ecc.)
#include<stdint.h>     // Contiene tipi di dato interi con dimensione esplicita (es. int8_t, int32_t, intmax_t)
#include<inttypes.h>   // Contiene le macro per stampare tipi definiti in <stdint.h> (es. PRIdMAX)

/*
    Scrivere un programma che dichiari una variabile di tipo intmax_t
    e stampi a schermo il suo valore massimo.
    Il programma deve essere portabile e funzionare su qualsiasi piattaforma C.
*/

int main() {
    // Dichiarazione di una variabile di tipo intmax_t
    // intmax_t è il tipo intero con la maggiore capacità disponibile sulla piattaforma
    // (potrebbe essere un long long, ma dipende dall’implementazione)
    intmax_t max_value = 500000000000000;

    // Stampa del valore della variabile
    // Si usa la macro di formattazione PRIdMAX per garantire la portabilità:
    // questa macro viene sostituita dal formato corretto (es. "lld" o "jd")
    // in base al tipo di intmax_t sulla piattaforma
    printf("Valore massimo: %" PRIdMAX "\n", max_value);

    return 0;   // Termina il programma
}

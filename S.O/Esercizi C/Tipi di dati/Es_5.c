#include<stdio.h>   // Libreria standard per input/output (printf, putchar)

/*
Scrivere un programma che:
- definisca un enum con flag READ, WRITE, EXEC come maschere di bit
- combini i permessi con |
- li modifichi con & ~
- stampi il risultato in binario dopo ogni modifica
*/

// Definizione di un enum che rappresenta i permessi come maschere di bit
typedef enum {
    READ = 1 << 0,    // 1 spostato di 0 posizioni -> 00000001 (bit 0)
    WRITE = 1 << 1,   // 1 spostato di 1 posizione -> 00000010 (bit 1)
    EXECUTE = 1 << 2, // 1 spostato di 2 posizioni -> 00000100 (bit 2)
} Permission;

// Funzione che stampa un numero in binario (8 bit)
void print_bits(int n) {
    for (int i = 7; i > -1; i--) {                // Ciclo sugli 8 bit (da 7 a 0)
        // (n >> i) sposta il numero di 'i' bit a destra
        // & 1 serve per isolare l’ultimo bit (restituisce 1 se è acceso, 0 se spento)
        printf("%d", (n >> i) & 1);              
        // Ad esempio: se n = 3 (00000011)
        // i = 7 -> (3 >> 7) = 0  -> 0 & 1 = 0
        // ...
        // i = 1 -> (3 >> 1) = 1  -> 1 & 1 = 1
        // i = 0 -> (3 >> 0) = 3  -> 3 & 1 = 1
        // Stampa quindi: 00000011
    }
    putchar('\n');  // Va a capo dopo aver stampato gli 8 bit
}

int main() {
    // 1️⃣ Combino i permessi READ e WRITE con l’operatore bitwise OR (|)
    // READ = 00000001
    // WRITE = 00000010
    // READ | WRITE = 00000011
    Permission p = READ | WRITE;

    // Stampa la rappresentazione binaria del valore di p
    // Output atteso: 00000011
    print_bits(p);

    // 2️⃣ Aggiungo il permesso EXECUTE
    // EXECUTE = 00000100
    // p |= EXECUTE significa p = p | EXECUTE
    // Prima: 00000011
    // Dopo : 00000111
    p |= EXECUTE;
    print_bits(p);  // Output: 00000111 (READ + WRITE + EXECUTE)

    // 3️⃣ Rimuovo il permesso WRITE
    // WRITE = 00000010
    // ~WRITE (NOT bit a bit) = 11111101
    // p & ~WRITE azzera il bit WRITE ma lascia inalterati gli altri
    // Prima: 00000111
    // Dopo : 00000101 (rimangono READ ed EXECUTE)
    p = p & ~WRITE;
    print_bits(p);  // Output: 00000101

    return 0;  // Termina il programma
}

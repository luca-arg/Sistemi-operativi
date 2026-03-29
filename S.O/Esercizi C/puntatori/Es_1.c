#include <stdio.h>   // Libreria standard di input/output (necessaria per printf)

/*
Dichiara una variabile intera, un puntatore che la referenzia e stampa:
- il valore della variabile
- l’indirizzo della variabile
- il valore del puntatore
- il valore puntato dal puntatore
*/

// Funzione che riceve una variabile intera e un puntatore a int come parametri
// e stampa le varie informazioni richieste
void print_variables(int var, int *p) {//parametri formali: var e p
    // Stampa il valore della variabile passata come parametro
    printf("Valore della variabile: %d\n", var);

    // Stampa l'indirizzo della variabile (attenzione: qui stampa l'indirizzo
    // della COPIA 'var' creata nella funzione, non quella originale in main)
    printf("Indirizzo della variabile: %p\n", &var);

    // Stampa il valore del puntatore (cioè l'indirizzo della variabile originale)
    printf("Valore del puntatore: %p\n", p);

    // Stampa il valore contenuto all'indirizzo puntato da p
    // cioè il valore effettivo della variabile originale
    printf("Valore puntato dal puntatore: %d\n", *p);
}

int main() {
    int var = 42;     // Variabile intera con valore iniziale 42
    int *p = &var;    // Puntatore che contiene l’indirizzo di var

    // Chiamata della funzione che stampa le informazioni
    // Si passa 'var' (per valore) e 'p' (p che è il puntatore all'indirizzo di var)
    print_variables(var, p);//parametri attuali: var e p

    return 0; // Termina il programma
}

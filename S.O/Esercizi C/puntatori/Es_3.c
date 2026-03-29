#include <stdio.h>   // Libreria standard per input/output (printf, scanf)
#include <stdlib.h>  // Libreria standard per funzioni di memoria dinamica (malloc, calloc, free) e rand()

/*
Definisci la funzione int* genera_array(int n);
- Alloca dinamicamente un array di n interi
- Inizializza ogni elemento con un valore casuale
- Restituisce il puntatore all’array generato
*/

// Funzione che crea un array dinamico di n elementi
int* genera_array(int n) {
    // Alloco dinamicamente un array di n interi inizializzati a 0
    // calloc() inizializza automaticamente la memoria a zero (diversamente da malloc)
    int *array = calloc(n, sizeof(int)); 

    // Controllo se l’allocazione è avvenuta correttamente
    if (array == NULL) {
        printf("Errore di allocazione della memoria\n");
        return NULL; // se fallisce, restituisco NULL
    }

    // Ciclo per inizializzare ogni elemento dell’array con un numero casuale tra 0 e 99
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 100; // rand() genera un intero pseudocasuale
    }

    // Restituisco il puntatore all'array creato dinamicamente
    return array;
}

int main() {
    int size = 0; // variabile che conterrà la dimensione dell’array

    // Chiedo all’utente la dimensione dell’array
    printf("Inserisci la dimensione dell'array: ");
    scanf("%d", &size);

    // Controllo se la dimensione inserita è valida (> 0)
    if (size <= 0) {
        printf("Dimensione non valida\n");
        return 1; // esco con codice di errore
    }

    int *array = NULL; // dichiaro un puntatore a int e lo inizializzo a NULL per sicurezza

    // Chiamo la funzione genera_array per creare l’array dinamico
    array = genera_array(size); 

    // Se l’array è stato allocato correttamente (non è NULL)
    if (array != NULL) {

        // ✅ PRIMA STAMPA — usando la notazione con indici classica
        for (int i = 0; i < size; i++) {
            printf("array[%d]: %d\n", i, array[i]);
        }

        printf("\n"); // riga vuota per separare le due stampe

        // ✅ SECONDA STAMPA — usando l’aritmetica dei puntatori
        for (int i = 0; i < size; i++) {
            // *(array + i) significa: "vai avanti di i elementi rispetto all’indirizzo base e prendi il valore"
            // array + i calcola l’indirizzo dell’elemento i-esimo
            // * (dereferenziazione) legge il valore contenuto in quell’indirizzo
            printf("array[%d]: %d\n", i, *(array + i)); 
        }

        // Libero la memoria allocata dinamicamente per evitare memory leak
        free(array);
    }

    // Programma terminato correttamente
    return 0;
}

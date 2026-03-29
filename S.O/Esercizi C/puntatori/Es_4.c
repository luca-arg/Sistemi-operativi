#include <stdio.h>   // Libreria per input/output
#include <stdlib.h>  // Libreria per malloc(), free(), rand()
#include <time.h>    // Libreria per time(), usata da srand()


#define N 3   // Numero di righe della matrice
#define M 4   // Numero di colonne della matrice

// Prototipo della funzione di stampa
void stampaMatrice(int **matrice, int n, int m);

int main()
{
    int **matrice; // Puntatore a puntatore a int: rappresenta una matrice come array di puntatori a righe
    int i, j;

    srand(time(NULL)); // Inizializza il generatore di numeri casuali con il tempo corrente

    // ------------------------------------------------------
    // ALLOCAZIONE DINAMICA DELLA MATRICE
    // ------------------------------------------------------

    // Alloco un array di N puntatori a int (ognuno rappresenterà una riga)
    matrice = malloc(N * sizeof *matrice);
    /*
        malloc() restituisce un void*, quindi non serve il cast in C.
        Usando sizeof *matrice invece di sizeof(int*), se cambi tipo in futuro
        il codice rimane corretto automaticamente.
        matrice adesso è un array di N "righe" (che verranno allocate sotto).
    */

    // Alloco ogni singola riga con M interi
    for (i = 0; i < N; i++)
    {
        matrice[i] = malloc(M * sizeof *matrice[i]);
        /*
            matrice[i] è un int* (cioè una riga della matrice).
            Quindi sizeof *matrice[i] = sizeof(int).
            Alla fine, otteniamo una struttura logica come questa:

            matrice ─┬─> [riga 0: int int int int]
                      ├─> [riga 1: int int int int]
                      └─> [riga 2: int int int int]
        */
    }

    // ------------------------------------------------------
    // RIEMPIMENTO CON VALORI CASUALI
    // ------------------------------------------------------
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            matrice[i][j] = rand() % 100; // Valori casuali tra 0 e 99
        }
    }

    // ------------------------------------------------------
    // STAMPA DELLA MATRICE
    // ------------------------------------------------------
    stampaMatrice(matrice, N, M);

    // ------------------------------------------------------
    // DEALLOCAZIONE DELLA MEMORIA
    // ------------------------------------------------------
    for (i = 0; i < N; i++)
    {
        free(matrice[i]); // Libero ogni riga
    }
    free(matrice); // Libero l’array di puntatori alle righe

    return 0;
}


// ------------------------------------------------------
// FUNZIONE DI STAMPA DELLA MATRICE
// ------------------------------------------------------
void stampaMatrice(int **matrice, int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%4d ", matrice[i][j]); // %4d = campo di 4 spazi, per allineare le colonne
        }
        printf("\n");
    }
}


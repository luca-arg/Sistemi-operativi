#include <stdio.h>   // Libreria per input/output
#include <stdlib.h>  // Libreria per malloc(), free(), rand()
#include <time.h>    // Libreria per time(), usata da srand()

int main()
{
    int **matrice; // Puntatore a puntatore a int: rappresenta una matrice come array di puntatori a righe
    int n,m; // Dimensioni della matrice
    srand(time(NULL)); // Inizializza il generatore di numeri casuali con il tempo corrente

    printf("Inserisci il numero di righe e di colonne della matrice: ");
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        fprintf(stderr, "Errore di input.\n");
        return 1;
    } 

    matrice = malloc(n * sizeof *matrice);// Alloco un array di n puntatori a int (ognuno rappresenterà una riga)
    // perchè si fa sto calcolo? Perchè matrice è un puntatore a puntatore a int, quindi *matrice è un puntatore a int, e sizeof *matrice dà la dimensione di un puntatore a int, che è ciò che vogliamo allocare per ogni riga. 
    // In alternativa, si potrebbe scrivere: matrice = malloc(n * sizeof(int*)); ma usare sizeof *matrice è più flessibile e meno soggetto a errori se il tipo di matrice dovesse cambiare in futuro.s
    if (!matrice) {
        perror("Errore di allocazione della matrice.\n");
        return 1;
    }
    for(int i=0 ; i<n ; i++){
        matrice[i] = malloc(m * sizeof *matrice[i]);// Alloco ogni singola riga con m interi
        if (!matrice[i]) {
            perror("Errore di allocazione della matrice.\n");
            // Dealloco le righe già allocate prima di uscire
            for (int j = 0; j < i; j++) {
                free(matrice[j]);// Dealloca la riga j, ovvero array di interi di dimensione m
            }
            free(matrice);// Dealloca l'array di puntatori a righe
            return 1;
        }
    }

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<m ; j++){
            matrice[i][j] = rand() % 100; // Riempio la matrice con valori casuali tra 0 e 99
            printf("%d ", matrice[i][j]); // Stampo l'elemento corrente
        }
        printf("\n");
    }

    for(int i=0 ; i<n ; i++){
        free(matrice[i]);// Dealloca la riga i, ovvero array di interi di dimensione m
    }
    free(matrice);// Dealloca l'array di puntatori a righe
    return 0;
}
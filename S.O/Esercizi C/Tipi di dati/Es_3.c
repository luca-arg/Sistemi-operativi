#include <stdio.h>
/*Scrivere un programma che:
dichiari unsigned int u = 0; e int s = -1;,
stampi il valore di u - 1, verifichi se s < u e spieghi il risultato.*/
int main() {
    unsigned int u = 0;
    int s = -1;

    printf("Valore di u - 1: %u\n", u - 1);
    if (s < u) {
        printf("s è minore di u\n");
    } else {
        printf("s non è minore di u\n");
    }

    return 0;
}
// Spiegazione del risultato:
//Viene stampato s non è minore di u, perché s è un intero con segno e u è un intero senza segno. Quando si confrontano un intero con segno e uno senza segno, il valore dell'intero con segno viene convertito in un intero senza segno. In questo caso, -1 viene convertito in un numero molto grande (tipicamente 4294967295 su sistemi a 32 bit), che è maggiore di 0 (il valore di u). Quindi, la condizione s < u risulta falsa. 
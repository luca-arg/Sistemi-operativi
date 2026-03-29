#include<stdio.h>   // Libreria standard per input/output (printf, scanf, ecc.)
#include<limits.h>  // Contiene i limiti dei tipi interi (es. INT_MIN, INT_MAX, CHAR_MIN, CHAR_MAX)
#include<float.h>   // Contiene i limiti dei tipi a virgola mobile (es. FLT_MIN, FLT_MAX, DBL_MIN, DBL_MAX)

/*
Scrivere un programma che stampi:
- la dimensione in byte dei tipi base (char, int, unsigned int, float, double)
- il valore minimo e massimo per interi e floating point
  (usando <limits.h> e <float.h>)
*/

int main() {

    // Intestazione descrittiva
    printf("Dimensione dei tipi di dati in C:\n");

    // Tipo 'char'
    // sizeof(char) -> dimensione in byte del tipo char
    // CHAR_MIN / CHAR_MAX -> valori minimo e massimo rappresentabili
    // %zu serve per stampare valori restituiti da sizeof (di tipo size_t)
    printf("char: %zu byte, min=%d, max=%d\n", sizeof(char), CHAR_MIN, CHAR_MAX);//%d sta per decimal integer (intero decimale con segno).

    // Tipo 'int'
    // INT_MIN / INT_MAX -> costanti definite in <limits.h>
    printf("int: %zu byte, min=%d, max=%d\n", sizeof(int), INT_MIN, INT_MAX);

    // Tipo 'unsigned int'
    // Gli unsigned non hanno segno, quindi il minimo è 0
    // UINT_MAX -> valore massimo per un unsigned int
    // ⚠️ Uso di %u invece di %d per valori senza segno
    printf("unsigned int: %zu byte, min=%u, max=%u\n", sizeof(unsigned int), 0, UINT_MAX);

    // Tipo 'float'
    // FLT_MIN / FLT_MAX -> valori minimo e massimo positivi rappresentabili da un float
    // %e stampa in notazione scientifica (più leggibile per numeri molto grandi o piccoli)
    printf("float: %zu byte, min=%e, max=%e\n", sizeof(float), FLT_MIN, FLT_MAX);

    // Tipo 'double'
    // DBL_MIN / DBL_MAX -> analoghi per il tipo double
    printf("double: %zu byte, min=%e, max=%e\n", sizeof(double), DBL_MIN, DBL_MAX); // %e sta per floating point scientific notation e %f per floating point decimal notation

    // Fine del programma
    return 0;
}

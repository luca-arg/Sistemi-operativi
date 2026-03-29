#include <stdio.h>
/*Scrivi una funzione swap(int *x, int *y) che scambi i valori di due
variabili. Testa la funzione nel main con due interi.*/

void swap(int *x, int *y) {
    int temp = *x; //salvo il valore puntato da x in una variabile temporanea
    *x = *y; //assegno a x il valore puntato da y
    *y = temp; //assegno a y il valore salvato in temp
}

int main() {
    int a = 5;
    int b = 10;
    printf("a: %d, b: %d\n", a, b);
    swap(&a, &b);
    printf("a: %d, b: %d\n", a, b);
    return 0;
}
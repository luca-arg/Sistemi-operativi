#include <stdio.h>
#include <limits.h>
#include <stdint.h>


/*Scrivere un programma che:
dichiari char c = 200; signed char sc = 200; unsigned char uc =
200;,stampi i tre valori, determini a runtime se char è interpretato come
signed o unsigned sulla piattaforma.*/

int main() {
    char c = 200;
    signed char sc = 200;
    unsigned char uc = 200;

    printf("char: %d\n", c);
    printf("signed char: %d\n", sc);
    printf("unsigned char: %u\n", uc);

    if (c < 0) {
        printf("char is interpreted as signed on this platform.\n");
    } else {
        printf("char is interpreted as unsigned on this platform.\n");
    }

    return 0;
}
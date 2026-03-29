/*Definisci una union chiamata Number che possa contenere: int i, float
f, array di 4 char bytes. Scrivi un programma che:
o assegni un valore a i e mostri come cambia la rappresentazione nei
bytes;
o assegni un valore a f e osservi i bytes;*/

//le union in C è una struttura dati che può contenere diversi tipi di dati, ma solo uno alla volta. Tutti i membri della union condividono lo stesso spazio di memoria, quindi quando si assegna un valore a un membro, si sovrascrivono i dati degli altri membri. In questo esempio, la union Number può contenere un intero (i), un float (f) o un array di 4 char (bytes). Quando si assegna un valore a i o f, la rappresentazione in memoria di quel valore influenzerà anche gli altri membri della union, poiché condividono lo stesso spazio di memoria. Di conseguenza, quando si assegna un valore a i o f, è possibile osservare come cambia la rappresentazione nei bytes e viceversa.

//a differenza delle struct, le union occupano solo lo spazio necessario per il membro più grande, poiché tutti i membri condividono lo stesso spazio di memoria. In questo caso, la union Number occuperà 4 byte, che è la dimensione del membro più grande (float o int). Quindi, quando si assegna un valore a i o f, si sovrascrive lo stesso spazio di memoria, e la rappresentazione in bytes cambierà di conseguenza. è come se ci fosse un puntatore che punta allo stesso spazio di memoria, e quando si assegna un valore a i o f, si sta modificando il contenuto di quel puntatore, influenzando così la rappresentazione in bytes. Di conseguenza, quando si assegna un valore a i o f, è possibile osservare come cambia la rappresentazione nei bytes e viceversa, poiché tutti i membri della union condividono lo stesso spazio di memoria.

#include <stdio.h>
#include <stdint.h>

union Number {
    __int32_t i;
    float f;
    unsigned char bytes[4];
};

int main() {
    union Number n;

    // Assegna un valore a i
    n.i = 0x01020304;
    printf("After assigning to i:\n");
    printf("i: %d\n", (unsigned)n.i);

    printf("f: %d\n", (unsigned)n.f);
    printf("bytes: %02x %02x %02x %02x\n", n.bytes[0], n.bytes[1], n.bytes[2], n.bytes[3]);
    n.f = 3.14f;
    printf("After assigning to f:\n");
    printf("i: %d\n", (unsigned)n.i);// i cambia a causa della rappresentazione in memoria di f infatti i e f condividono lo stesso spazio di memoria, quindi quando assegni un valore a f, stai sovrascrivendo i byte che rappresentano i. Di conseguenza, il valore di i cambia in modo imprevedibile, poiché dipende dalla rappresentazione in memoria del numero in virgola mobile 3.14f.
    //quello che esce è un numero intero che rappresenta la rappresentazione in memoria di 3.14f, ma non ha un significato diretto come numero intero. La rappresentazione in memoria di un numero in virgola mobile è diversa da quella di un numero intero, quindi il valore di i non avrà un significato coerente dopo l'assegnazione a f.

    printf("f: %f\n", n.f);
    printf("bytes: %02x %02x %02x %02x\n", n.bytes[0], n.bytes[1], n.bytes[2], n.bytes[3]);// La rappresentazione in memoria di 3.14f è 0x4048f5c3, quindi i byte saranno 0xc3, 0xf5, 0x48, 0x40 (in ordine inverso a causa dell'endianness della macchina). Quindi l'output sarà:
    //bytes: c3 f5 48 40    

    return 0;
}
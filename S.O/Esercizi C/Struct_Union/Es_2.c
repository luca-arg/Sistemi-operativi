#include <stdio.h>

/*Definisci due versioni di una struct chiamata Data che contengano char a,
int b, short c in ordine diverso. 

Scrivi un programma che:
o stampi sizeof(struct Data1) e sizeof(struct Data2);
o aggiungi, direttive di packing (#pragma pack) e confronta di nuovo le
dimensioni.*/

#pragma pack(1)
struct Data1 {
    char a;
    int b;
    short c;
}Data1;

struct Data2 {
    char a;
    short c;
    int b;
}Data2;
#pragma pack(0)
    

int main(){
    printf("Size of Data1: %zu\n", sizeof(Data1));
    printf("Size of Data2: %zu\n", sizeof(Data2));

    
    return 0;
}

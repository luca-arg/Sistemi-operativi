/*Definisci una struct chiamata Rectangle che contenga due campi di tipo
Point (con due campi x e y di tipo float): top_left e bottom_right.
Scrivi un programma che:
o inizializzi un rettangolo;
o calcoli e stampi base, altezza e area.*/
#include <stdio.h>
struct Point {
    float x;
    float y;
};
struct Rectangle {
    struct Point top_left;
    struct Point bottom_right;
};
int main() {
    struct Rectangle rect;

    // Inizializza il rettangolo
    rect.top_left.x = 1.0;// Inizializza il punto in alto a sinistra
    rect.top_left.y = 4.0;// Inizializza il punto in alto a sinistra
    rect.bottom_right.x = 5.0;// Inizializza il punto in basso a destra
    rect.bottom_right.y = 1.0;// Inizializza il punto in basso a destra

    // Calcola base, altezza e area
    float base = rect.bottom_right.x - rect.top_left.x;// Calcola la base del rettangolo come differenza tra le coordinate x dei punti in basso a destra e in alto a sinistra
    float altezza = rect.top_left.y - rect.bottom_right.y;// Calcola l'altezza del rettangolo come differenza tra le coordinate y dei punti in alto a sinistra e in basso a destra
    float area = base * altezza;

    // Stampa i risultati
    printf("Base: %.2f\n", base);
    printf("Altezza: %.2f\n", altezza);
    printf("Area: %.2f\n", area);

    return 0;
}
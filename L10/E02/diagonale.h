#ifndef DIAGONALE_H
#define DIAGONALE_H

#include "elemento.h"
#include "smartlib.h"

typedef struct Diagonale {
    array Elementi;
    unsigned int Difficolta;
    float Punteggio;
} * diagonale;

float punteggioDiagonale(diagonale d);
void freeDiagonale(diagonale d);
unsigned int difficoltaDiagonale(diagonale d);
diagonale creaDiagonale();

#endif // DIAGONALE_H

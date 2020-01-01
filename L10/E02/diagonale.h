#ifndef DIAGONALE_H
#define DIAGONALE_H

#include "array.h"
#include "elemento.h"

typedef struct Diagonale {
    array Elementi;
    unsigned int Difficolta;
    float Punteggio;
} * diagonale;

unsigned int generaDiagonale(array elementi, diagonale soluzione, diagonale max, unsigned int posizione, unsigned int difficoltaDiagonale);
float calcolaPunteggioDiagonale(diagonale d);
void freeDiagonale(diagonale d);
unsigned int calcolaDifficoltaDiagonale(diagonale d);
void copiaDiagonale(diagonale DEST, diagonale SRC);
diagonale creaDiagonale();

#endif // DIAGONALE_H

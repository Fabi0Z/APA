#ifndef DIAGONALE_H
#define DIAGONALE_H

#include "array.h"
#include "elemento.h"
#include "list.h"

typedef struct Diagonale {
    array Elementi;
    unsigned int Difficolta;
    float Punteggio;
} * diagonale;

unsigned int generaDiagonali(array elementi, diagonale soluzione, link list, unsigned int posizione, unsigned int difficoltaDiagonale);
float calcolaPunteggioDiagonale(diagonale d);
void freeDiagonale(diagonale d);
unsigned int calcolaDifficoltaDiagonale(diagonale d);
void copiaDiagonale(diagonale DEST, diagonale SRC);
diagonale creaDiagonale(unsigned int NumeroElementi);

#endif // DIAGONALE_H

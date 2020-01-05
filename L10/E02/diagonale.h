#ifndef DIAGONALE_H
#define DIAGONALE_H

#include "array.h"
#include "checks.h"
#include "elemento.h"
#include "list.h"

typedef struct Diagonale {
    array Elementi;
    unsigned int Difficolta;
    float Punteggio;
} * diagonale;

bool minorEqualValore(elemento a, elemento b, unsigned int *difficoltaDiagonale);
unsigned int maxValoreConDifficolta(elemento e, unsigned int difficolta);
diagonale generaDiagonale(array elementi, unsigned int DD, unsigned int DP, checks controlli);
void generaDiagonaleR(array elementi, unsigned int difficoltaDiagonale, checks controlli, link soluzione, uint8_t elementiInseribili);
bool updateChecks(diagonale d, checks c);
unsigned int generaDiagonali(array elementi, diagonale soluzione, link list, unsigned int posizione, unsigned int difficoltaDiagonale);
void printDiagonale(diagonale d);
void freeDiagonale(diagonale d);
diagonale creaDiagonale(unsigned int NumeroElementi);
void copiaDiagonale(diagonale DEST, diagonale SRC);
float calcolaPunteggioDiagonale(diagonale d);
unsigned int calcolaDifficoltaDiagonale(diagonale d);

#endif // DIAGONALE_H

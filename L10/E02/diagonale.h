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

bool maggiorValoreConMoltiplicatore(elemento a, elemento b, unsigned int *difficoltaDiagonale);
bool maggiorValore(elemento a, elemento b, unsigned int *difficoltaDiagonale);
float maxValoreConDifficolta(elemento e, unsigned int difficolta, bool moltiplicatore);
diagonale generaDiagonale(array elementi, unsigned int DD, unsigned int DP, checks controlli);
uint8_t generaDiagonaleR(array elementi, unsigned int difficoltaDiagonale, checks controlli, link soluzione, uint8_t elementiInseribili);
bool insertCheck(elemento e, unsigned int difficoltaDiagonale, checks controlli, unsigned int elementiInseribili);
void updateChecksDiagonale(diagonale d, checks c);
bool updateChecks(elemento e, checks c);
void printDiagonale(diagonale d);
void freeDiagonale(diagonale d);
diagonale creaDiagonale(unsigned int NumeroElementi);
void copiaDiagonale(diagonale DEST, diagonale SRC);
float calcolaPunteggioDiagonale(diagonale d);
unsigned int calcolaDifficoltaDiagonale(diagonale d);

#endif // DIAGONALE_H

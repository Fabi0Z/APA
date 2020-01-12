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

bool maggiorValoreConMoltiplicatore(elemento a, elemento b, item *args);
bool maggiorValore(elemento a, elemento b, unsigned int *difficoltaDiagonale);
float maxValoreConDifficolta(elemento e, unsigned int difficolta, bool moltiplicatore, uint8_t bonus);
diagonale generaDiagonale(array elementi, unsigned int DD, checks controlli, elemento elementoMinimo);
void printDiagonale(diagonale d);
void freeDiagonale(diagonale d);
diagonale creaDiagonale(unsigned int NumeroElementi);
void copiaDiagonale(diagonale DEST, diagonale SRC);
float calcolaPunteggioTerzaDiagonale(diagonale d);
float calcolaPunteggioDiagonale(diagonale d);
unsigned int calcolaDifficoltaDiagonale(diagonale d);

#endif // DIAGONALE_H

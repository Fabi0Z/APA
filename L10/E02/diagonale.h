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
diagonale generaDiagonale(array elementi, unsigned int DD, checks controlli, unsigned int difficoltaMinima);
bool updateChecks(elemento e, checks c, unsigned int difficoltaMassima, unsigned int difficoltaMinima);
void printDiagonale(diagonale d);
void freeDiagonale(diagonale d);
diagonale creaDiagonale(unsigned int NumeroElementi);
void copiaDiagonale(diagonale DEST, diagonale SRC);
float calcolaPunteggioTerzaDiagonale(diagonale d);
float calcolaPunteggioDiagonale(diagonale d);
unsigned int calcolaDifficoltaDiagonale(diagonale d);
bool insertCheck(elemento e, unsigned int difficoltaDiagonale, checks controlli, unsigned int difficoltaMinima);

#endif // DIAGONALE_H

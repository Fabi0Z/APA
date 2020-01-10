#ifndef PROGRAMMA_H
#define PROGRAMMA_H

#include "diagonale.h"
#include "sortlib.h"

typedef struct Programma {
    diagonale *Diagonali;
    unsigned int Difficolta;
    float Punteggio;
} * programma;

bool verificaProgramma(programma p, unsigned int difficoltaProgramma);
void printProgramma(programma p);
programma generaMigliorProgramma(array elementi, unsigned int DD, unsigned int DP);
void copiaProgramma(programma DEST, programma SRC);
float calcolaPunteggioProgramma(programma p);
unsigned int calcolaDifficoltaProgramma(programma p);
void freeProgramma(programma p);
programma creaProgramma();

#endif // PROGRAMMA_H

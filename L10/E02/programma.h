#ifndef PROGRAMMA_H
#define PROGRAMMA_H

#include "diagonale.h"

typedef struct Programma {
    diagonale *Diagonali;
    unsigned int Difficolta;
    float Punteggio;
} * programma;

bool verificaProgramma(programma p, unsigned int difficoltaProgramma);
programma generaMigliorProgramma(array elementi, unsigned int DD, unsigned int DP);
void freeProgramma(programma p);
programma creaProgramma();
unsigned int calcolaDifficoltaProgramma(programma p);

#endif // PROGRAMMA_H

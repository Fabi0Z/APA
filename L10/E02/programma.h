#ifndef PROGRAMMA_H
#define PROGRAMMA_H

#include "diagonale.h"

typedef struct Programma {
    diagonale *Diagonali;
    unsigned int Difficolta;
    float Punteggio;
} * programma;

void freeProgramma(programma p);
programma creaProgramma();

#endif // PROGRAMMA_H

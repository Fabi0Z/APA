#ifndef PROGRAMMA_H
#define PROGRAMMA_H

#include "diagonale.h"

typedef struct Programma {
    diagonale *Diagonali;
    unsigned int Difficolta;
    float Punteggio;
} * programma;

programma generaMigliorProgramma(array elementi, unsigned int DD, unsigned int DP);
void freeProgramma(programma p);
programma creaProgramma();
void copiaProgramma(programma DEST, programma SRC);
bool verificaProgramma(programma p, unsigned int difficoltaProgramma);
void combinazioniRipetuteProgramma(unsigned int posizione, array valori, programma soluzione, programma max, unsigned int start, unsigned int difficoltaProgramma);
unsigned int calcolaDifficoltaProgramma(programma p);

#endif // PROGRAMMA_H

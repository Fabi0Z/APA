#ifndef ARRAYOGGETTI_H
#define ARRAYOGGETTI_H

#include "oggetto.h"
typedef struct ArrayOggetti *arrayOggetti;

void printArrayOggetti(arrayOggetti a, FILE *stream, bool indici);
void *getOggettoByName(arrayOggetti a, char *nome, bool pointer);
void *getOggettoByIndex(arrayOggetti a, unsigned int index, bool pointer);
unsigned int getNumeroOggetti(arrayOggetti a);
void copiaArrayOggetti(arrayOggetti dest, arrayOggetti src);
arrayOggetti creaArrayOggetti();
void aggiungiOggettoArray(arrayOggetti a, oggetto o);
void freeArrayOggetti(arrayOggetti a, bool elementi);
arrayOggetti allocaArrayOggetti(unsigned int items);

#endif // ARRAYOGGETTI_H

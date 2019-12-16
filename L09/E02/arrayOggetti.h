#ifndef ARRAYOGGETTI_H
#define ARRAYOGGETTI_H

#include "oggetto.h"
typedef struct ArrayOggetti *arrayOggetti;

void printArrayOggetti(arrayOggetti a, FILE *stream, bool indici);
oggetto getOggettoByName(arrayOggetti a, char *nome);
oggetto getOggettoByIndex(arrayOggetti a, unsigned int index);
unsigned int getNumeroOggetti(arrayOggetti a);
void copiaArrayOggetti(arrayOggetti dest, arrayOggetti src);
arrayOggetti creaArrayOggetti();
arrayOggetti allocaArrayOggetti(unsigned int items);
void freeArrayOggetti(arrayOggetti a, bool elementi);
void aggiungiOggettoArray(arrayOggetti a, oggetto o);

#endif // ARRAYOGGETTI_H

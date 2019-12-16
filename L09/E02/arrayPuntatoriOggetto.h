#ifndef ARRAYPUNTATORIOGGETTO_H
#define ARRAYPUNTATORIOGGETTO_H

#include "oggetto.h"
typedef struct ArrayPuntatoriOggetto *arrayPuntatoriOggetto;

bool rimuoviPuntatoreOggetto(arrayPuntatoriOggetto a, oggetto o);
void printArrayPuntatoriOggetto(arrayPuntatoriOggetto a, FILE *stream, bool indici);
unsigned int getIndexPuntatoreOggetto(arrayPuntatoriOggetto a, oggetto o);
oggetto *getPuntatoreOggettoByName(arrayPuntatoriOggetto a, char *nome);
oggetto *getPuntatoreOggettoByIndex(arrayPuntatoriOggetto a, unsigned int index);
unsigned int getNumeroPuntatori(arrayPuntatoriOggetto a);
void copiaArrayPuntatoriOggetto(arrayPuntatoriOggetto dest, arrayPuntatoriOggetto src);
arrayPuntatoriOggetto creaArrayPuntatoriOggetto();
arrayPuntatoriOggetto allocaArrayPuntatoriOggetto(unsigned int items);
void freeArrayPuntatoriOggetto(arrayPuntatoriOggetto a, bool elementi);
void aggiungiOggettoArrayPuntatori(arrayPuntatoriOggetto a, oggetto *o);

#endif // ARRAYPUNTATORIOGGETTO_H

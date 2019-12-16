#ifndef ARRAYPUNTATORIOGGETTO_H
#define ARRAYPUNTATORIOGGETTO_H

#include "oggetto.h"
typedef struct ArrayPuntatoriOggetto *arrayPuntatoriOggetto;

void printarrayPuntatoriOggetto(arrayPuntatoriOggetto a, FILE *stream, bool indici);
oggetto *getPuntatoreOggettoByName(arrayPuntatoriOggetto a, char *nome);
oggetto *getPuntatoreOggettoByIndex(arrayPuntatoriOggetto a, unsigned int index);
arrayPuntatoriOggetto creaArrayPuntatoriOggetto();
void copiaArrayPuntatoriOggetto(arrayPuntatoriOggetto dest, arrayPuntatoriOggetto src);
arrayPuntatoriOggetto allocaarrayPuntatoriOggetto(unsigned int items);
void freearrayPuntatoriOggetto(arrayPuntatoriOggetto a, bool elementi);
void aggiungiOggettoArrayPuntatori(arrayPuntatoriOggetto a, oggetto *o);

#endif // ARRAYPUNTATORIOGGETTO_H

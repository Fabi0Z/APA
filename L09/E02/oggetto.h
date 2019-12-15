#ifndef OGGETTO_H
#define OGGETTO_H

#include "statistiche.h"
typedef struct Oggetto *oggetto;
typedef struct ArrayOggetti *arrayOggetti;
typedef struct ArrayPuntatoriOggetti *arrayPuntatoriOggetti;

stats getStatisticheOggetto(oggetto o);
char *getTipoOggetto(oggetto o);
char *getNomeOggetto(oggetto o);
void aggiungiOggettoArrayPuntatori(arrayPuntatoriOggetti a, oggetto *o);
void aggiungiOggettoArray(arrayOggetti a, oggetto o);
bool leggiOggetto(char *string, oggetto o);
void copiaArrayPuntatoriOggetti(arrayPuntatoriOggetti dest, arrayPuntatoriOggetti src);
void copiaArrayOggetti(arrayOggetti dest, arrayOggetti src);
void copiaOggetto(oggetto dest, oggetto src);
arrayPuntatoriOggetti creaArrayPuntatoriOggetti(unsigned int NumeroOggetti);
arrayOggetti creaArrayOggetti(unsigned int NumeroOggetti);
oggetto creaOggetto(unsigned int nomeSize, unsigned int tipoSize);
void printArrayPuntatoriOggetti(arrayPuntatoriOggetti a, FILE *stream);
void printArrayOggetti(arrayOggetti a, FILE *stream);
void printOggetto(oggetto o, FILE *stream);
void freeArrayPuntatoriOggetti(arrayPuntatoriOggetti a, bool elementi);
void freeArrayOggetti(arrayOggetti a, bool elementi);
void freeOggetto(oggetto o);
void allocaOggetto(oggetto o, unsigned int nomeSize, unsigned int tipoSize);

#endif // OGGETTO_H

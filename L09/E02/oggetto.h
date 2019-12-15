#ifndef OGGETTO_H
#define OGGETTO_H

#include "statistiche.h"
typedef struct Oggetto *oggetto;
typedef struct ArrayOggetti *arrayOggetti;

stats getStatisticheOggetto(oggetto o);
char *getTipoOggetto(oggetto o);
char *getNomeOggetto(oggetto o);
void aggiungiOggetto(arrayOggetti a, oggetto o);
bool leggiOggetto(char *string, oggetto o);
void copiaArrayOggetti(arrayOggetti dest, arrayOggetti src);
void copiaOggetto(oggetto dest, oggetto src);
arrayOggetti creaArrayOggetti(unsigned int NumeroOggetti);
oggetto creaOggetto(unsigned int nomeSize, unsigned int tipoSize);
void printOggetto(oggetto o, FILE *stream);
void freeArrayOggetti(arrayOggetti a, bool elementi);
void freeOggetto(oggetto o);
void allocaOggetto(oggetto o, unsigned int nomeSize, unsigned int tipoSize);

#endif // OGGETTO_H

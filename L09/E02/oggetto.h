#ifndef OGGETTO_H
#define OGGETTO_H

#include "statistiche.h"
typedef struct Oggetto *oggetto;

void printOggetto(oggetto o, FILE *stream);
bool leggiOggetto(char *string, oggetto o);
char *getTipoOggetto(oggetto o);
stats getStatisticheOggetto(oggetto o);
char *getNomeOggetto(oggetto o);
void freeOggetto(oggetto o);
oggetto creaOggetto(unsigned int nomeSize, unsigned int tipoSize);
void copiaOggetto(oggetto dest, oggetto src);
void allocaOggetto(oggetto o, unsigned int nomeSize, unsigned int tipoSize);

#endif // OGGETTO_H

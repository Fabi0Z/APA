#if !defined(OGGETTO_H)
#define OGGETTO_H

#include "statistiche.h"

typedef struct Oggetto {
    char *Nome;
    char *Tipo;
    stats Statistiche;
} oggetto;

bool leggiOggetto(char *string, oggetto *o);
void copiaOggetto(oggetto *dest, oggetto *src);
oggetto *creaOggetto(unsigned int nomeSize, unsigned int tipoSize);
void printOggetto(oggetto *o, FILE *stream);
void freeOggetto(oggetto *o);
void allocaOggetto(oggetto *o, unsigned int nomeSize, unsigned int tipoSize);

#endif // OGGETTO_H

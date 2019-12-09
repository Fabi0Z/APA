#ifndef SCACCHIERA_H
#define SCACCHIERA_H

#include "tessera.h"
#include <stdbool.h>

typedef struct Cella {
    tessera *Tessera;
    bool Rotazione;
} cella;

typedef struct Scacchiera {
    unsigned int Righe;
    unsigned int Colonne;
    cella **Matrice;
} scacchiera;

void printScacchiera(scacchiera *s, FILE *stream);
void stampaRigaScacchiera(scacchiera *s, unsigned int indiceRiga, FILE *stream);
void stampaSottoriga3(scacchiera *s, unsigned int indiceRiga, FILE *stream);
void stampaSottoriga2(scacchiera *s, unsigned int indiceRiga, FILE *stream);
void stampaSottoriga1(scacchiera *s, unsigned int indiceRiga, FILE *stream);
void stampaRigaInferiore(scacchiera *s, FILE *stream);
void stampaRigaSuperiore(scacchiera *s, FILE *stream);
void printCella(cella *c, arrayTessera *a, FILE *stream);
void printTubi(tubo *orizzontale, tubo *verticale, FILE *stream);
void parseScacchiera(scacchiera *s, FILE *stream, arrayTessera *a);
void allocaScacchiera(scacchiera *s);
void parseCella(cella *c, char *string, arrayTessera *a);

#endif // SCACCHIERA_H

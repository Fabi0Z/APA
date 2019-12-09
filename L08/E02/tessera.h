#ifndef TESSERA_H
#define TESSERA_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tubo {
    char Colore;
    uint8_t Valore;
} tubo;

typedef struct Tessera {
    tubo Tubo1;
    tubo Tubo2;
} tessera;

typedef struct ArrayTessera {
    tessera **Array;
    unsigned int NumeroElementi;
} arrayTessera;

void printArrayTessera(arrayTessera *a, FILE *stream);
void printTessera(tessera *t, FILE *stream);
void printTubo(tubo *t, FILE *stream);
arrayTessera parseArrayTessera(FILE *stream, unsigned int numeroTessere);
tessera *creaTessera();
void parseTessera(tessera *t, char *string);
void parseTubo(tubo *t, char *string);

#endif // TESSERA_H

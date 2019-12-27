#ifndef ARRAYELEMENTO_H
#define ARRAYELEMENTO_H

#include "elemento.h"
#include "smartfunctions.h"

typedef struct ArrayElemento {
    elemento *Array;
    unsigned int NumeroElementi;
} * arrayElemento;

arrayElemento parseElementoFromFile(char *filename);
void freeArrayElemento(arrayElemento a);
arrayElemento creaArrayElemento();
void allocaArrayElemento(arrayElemento a, unsigned int NumeroElementi);

#endif // ARRAYELEMENTO_H

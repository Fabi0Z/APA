#ifndef ARCO_H
#define ARCO_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arco {
    char **IDElaboratori;
    char **IDRete;
    unsigned int Flusso;
} * arco;

arco parseArco(char *string);
arco newArco();
void freeArco(arco a);
void copyArco(arco DEST, arco SRC);
void allocateArco(arco a, unsigned int *sizes);

#endif // ! ARCO_H

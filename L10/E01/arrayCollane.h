#ifndef ARRAYCOLLANE_H
#define ARRAYCOLLANE_H

#include "collana.h"

typedef struct ArrayCollane {
    collana *Array;
    unsigned int NumeroElementi;
} * arrayCollane;

void printArrayCollane(arrayCollane a);
arrayCollane parseArrayCollane(FILE *stream);
arrayCollane creaArrayCollane(unsigned int NumeroElementi);
extern const unsigned int MAX_STRING;

#endif // ARRAYCOLLANE_H

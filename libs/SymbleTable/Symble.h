#ifndef SYMBLE_H
#define SYMBLE_H

#include <stdlib.h>

typedef struct Symble {
    unsigned int Index;
    char *Name;
} * symble;

void freeSymble(symble s);
symble newSymble(unsigned int NameLength);

#endif // ! SYMBLE_H

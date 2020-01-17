#ifndef SYMBLE_H
#define SYMBLE_H

#include <stdlib.h>
#include <string.h>

typedef struct Symble {
    unsigned int Index;
    char *Name;
    unsigned int __NameLength;
} * symble;

void updateSymbleName(symble s, char *NewName);
symble newSymble(unsigned int NameLength);
void freeSymble(symble s);

#endif // ! SYMBLE_H

#include "Symble.h"

// Crea un symble
symble newSymble(unsigned int NameLength) {
    symble s = malloc(sizeof(struct Symble));
    s->Name  = calloc(NameLength + 1, sizeof(char));
    return s;
}

// Elimina un symble
void freeSymble(symble s) {
    free(s->Name);
    free(s);
}
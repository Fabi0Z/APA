#include "Symble.h"

// Ridimensiona il nome correttamente
static void fixNameSize(symble s, char *NewName) {
    unsigned int Length = strlen(NewName);
    if (Length > s->__NameLength) {
        char temp[s->__NameLength];
        strcpy(s->Name, temp);
        free(s->Name);
        s->__NameLength = Length;
        s->Name         = calloc(s->__NameLength + 1, sizeof(char));
    }
}

// Elimina un symble
void freeSymble(symble s) {
    if (s == NULL) {
        return;
    }
    free(s->Name);
    free(s);
}

// Crea un symble
symble newSymble(unsigned int NameLength) {
    symble s        = malloc(sizeof(struct Symble));
    s->__NameLength = NameLength;
    s->Name         = calloc(s->__NameLength + 1, sizeof(char));
    return s;
}

// Aggiorna il nome di un Symble
void updateSymbleName(symble s, char *NewName) {
    fixNameSize(s, NewName);
    strcpy(s->Name, NewName);
}
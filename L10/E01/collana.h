#ifndef COLLANA_H
#define COLLANA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { zaffiro,
               rubino,
               topazio,
               smeraldo,
               totale,
               numeroCampi } pietra;

typedef struct Collana {
    unsigned int Pietre[numeroCampi];
    unsigned int LunghezzaMassima;
} * collana;

void printCollana(collana c);
collana parseCollana(char *string);
collana creaCollana();

#endif // COLLANA_H

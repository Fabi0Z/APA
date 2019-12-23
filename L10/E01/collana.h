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
unsigned int maxSmeraldi(unsigned int *pietre);
unsigned int maxTopazi(unsigned int *pietre);
unsigned int maxRubini(unsigned int *pietre);
unsigned int maxZaffiri(unsigned int *pietre);
unsigned int maxCollana(unsigned int *pietre);
collana creaCollana();

#endif // COLLANA_H

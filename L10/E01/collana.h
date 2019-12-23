#ifndef COLLANA_H
#define COLLANA_H

#include "pietra.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Collana {
    unsigned int Pietre[totale + 1];
    pietra *Array;
} collana;

unsigned int maxCollana(unsigned int *pietre);
unsigned int maxSmeraldi(unsigned int *pietre);
unsigned int maxTopazi(unsigned int *pietre);
unsigned int maxRubini(unsigned int *pietre);
unsigned int maxZaffiri(unsigned int *pietre);
collana parseCollana(char *string);

#endif // COLLANA_H

#ifndef ADIACENZA_H
#define ADIACENZA_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Adiacenza {
    unsigned int *Destinazione;
} * adiacenza;

adiacenza newAdiacenza(unsigned int Destinazione, unsigned int Peso);
unsigned int getPeso(adiacenza a);
void freeAdiacenza(adiacenza a);
bool adiacenzaPesataStatus();
void adiacenzaPesata(bool set);

#endif // ! ADIACENZA_H

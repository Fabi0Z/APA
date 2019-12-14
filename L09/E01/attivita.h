#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Attivita {
    uint8_t Inizio;
    uint8_t Fine;
    uint8_t Durata;
} attivita;

typedef struct ArrayAttivita {
    attivita *Array;
    uint8_t NumeroElementi;
    unsigned int Durata;
} arrayAttivita;

void printArrayAttivita(arrayAttivita *a);
void printAttivita(attivita *a);
void ordina(arrayAttivita *a);
void copiaArrayAttivita(arrayAttivita *dest, arrayAttivita *src);
void durataArrayAttivita(arrayAttivita *a);
uint8_t durataAttivita(attivita *a);
void leggiAttivita(FILE *stream, arrayAttivita *a);
attivita parseAttivita(char *string);
bool attivitaSovvrapposta(attivita *a, attivita *b);

#endif // ATTIVITA_H

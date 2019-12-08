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
uint8_t durataAttivita(attivita *a);
void durataArrayAttivita(arrayAttivita *a);
void copiaArrayAttivita(arrayAttivita *dest, arrayAttivita *src);
void ordina(arrayAttivita *a);
void ordinaRicorsivo(attivita *a, attivita *b, uint8_t inizio, uint8_t fine);
void merge(attivita *a, attivita *b, int inzio, int centro, int fine);
void leggiAttivita(FILE *stream, arrayAttivita *a);
attivita parseAttivita(char *string);
bool attivitaSovvrapposta(attivita *a, attivita *b);

#endif

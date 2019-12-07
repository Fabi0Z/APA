#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Attivita {
    uint8_t Inizio;
    uint8_t Fine;
} attivita;

void printArrayAttivita(attivita *a, uint8_t numeroAttivita);
uint8_t printAttivita(attivita *a);
uint8_t durataAttivita(attivita *a);
void ordina(attivita *a, uint8_t numeroAttivita);
void ordinaRicorsivo(attivita *a, attivita *b, uint8_t inizio, uint8_t fine);
void merge(attivita *a, attivita *b, int inzio, int centro, int fine);
void leggiAttivita(FILE *stream, attivita *a, uint8_t numeroAttivita);
attivita parseAttivita(char *string);
bool attivitaSovvrapposta(attivita *a, attivita *b);

#endif

#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

// * STRUTTURE DATI

typedef struct Attivita {
    uint8_t Inizio;
    uint8_t Fine;
} attivita;
// * -------------------------------------------------------------

// * FUNZIONI DI CONTROLLO

// Controlla se due attività sono sovvrapposte
bool attivitaSovvrapposta(attivita *a, attivita *b);
// * -------------------------------------------------------------

// * LETTURA DATI

// Effettua il parse di un'attività da stringa
attivita parseAttivita(char *string);
// Legge una serie di attività da file
void leggiAttivita(FILE *stream, attivita *a, uint8_t numeroAttivita);
// * -------------------------------------------------------------

// * STAMPA DATI

// Stampa un'attività
void printAttivita(attivita *a);
// Stampa un array di attivita
void printArrayAttivita(attivita *a, uint8_t numeroAttivita);
// * -------------------------------------------------------------

// * MANIPOLAZIONE DATI

// Ordina un array di attività tramite il Merge Sort
void ordina(attivita *a, uint8_t numeroAttivita);
// * -------------------------------------------------------------

#endif
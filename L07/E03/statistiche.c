#include "statistiche.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Crea e alloca memoria per una variabile stats
stats creaStatistiche() {
    stats s = (stats)malloc(sizeof(int16_t));
}

// Stampa delle statistiche
void printStatistiche(stats s, FILE *stream) {
    for (size_t i = 0; i < N_STATISTICHE; i++) { // Per ogni statistica
        fprintf(stream, "%" SCNd16 " ", s[i]);
    }
}

// Effettua il parse delle statistiche da stringa
bool leggiStatistiche(char *string, stats s) {
    uint8_t conteggio = 0;
    for (size_t i = 0; i < N_STATISTICHE; i++) { // Per ogni statistica
        conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &s[i], string);
    }
    return conteggio == 11;
}
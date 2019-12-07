#include "attivita.h"
#include "smartfunctions.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// * CALCOLO COMBINATORIO

// Powerset
void powerset(uint8_t posizione, attivita *a, attivita *soluzione,
              uint8_t maxLunghezza, uint8_t start) {

    if (start >= maxLunghezza) {                 // Se ho raggiunto la lunghezza massima
        printArrayAttivita(soluzione, posizione); // Stampo soluzione
        return;
    }

    for (uint8_t i = start; i < maxLunghezza; i++) { // Per ogni posizione rimanente
        soluzione[posizione] = a[i];
        powerset(posizione + 1, a, soluzione, maxLunghezza, i + 1);
    }

    powerset(posizione, a, soluzione, maxLunghezza, maxLunghezza);
}
// * -------------------------------------------------------------

int main() {
    FILE *stream = fopen("att.txt", "r");
    checkFilestream(stream);

    uint8_t numeroAttivita;
    fscanf(stream, "%" SCNd8 "\n", &numeroAttivita);
    attivita a[numeroAttivita];
    leggiAttivita(stream, a, numeroAttivita);
    ordina(a, numeroAttivita);
    printArrayAttivita(a, numeroAttivita);

    attivita b[numeroAttivita];
    powerset(0, a, b, numeroAttivita, 0);
    return 0;
}

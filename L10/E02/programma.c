#include "programma.h"

static const uint8_t NUMERO_DIAGONALI = 3;

// Crea un programma acrobatico
programma creaGruppoDiagonali() {
    programma g = calloc(NUMERO_DIAGONALI, sizeof(array));
    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) {
        g[i] = creaArray();
    }
}

// Elimina un programma acrobatico
void freeGruppoDiagonali(programma g) {
    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) {
        g[i]->free(g[i], (void *)&freeElemento);
    }
}
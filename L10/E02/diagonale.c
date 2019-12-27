#include "diagonale.h"

static const uint8_t NUMERO_DIAGONALI = 3;

// Crea un gruppo di NUMERO_DIAGONALI diagonali
gruppoDiagonali creaGruppoDiagonali() {
    gruppoDiagonali g = calloc(NUMERO_DIAGONALI, sizeof(array));
    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) {
        g[i] = creaArray();
    }
}

// Elimina un gruppo di diagonali
void freeGruppoDiagonali(gruppoDiagonali g) {
    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) {
        g[i]->free(g[i], (void *)&freeElemento);
    }
}
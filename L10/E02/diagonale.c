#include "diagonale.h"

// Crea un gruppo di 3 diagonali
gruppoDiagonali creaGruppoDiagonali() {
    gruppoDiagonali g = calloc(3, sizeof(array));
    for (uint8_t i = 0; i < 3; i++) {
        g[i] = creaArray();
    }
}

// Elimina un gruppo di diagonali
void freeGruppoDiagonali(gruppoDiagonali g) {
    for (uint8_t i = 0; i < 3; i++) {
        g[i]->free(g[i], (void *)&freeElemento);
    }
}
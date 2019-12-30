#include "diagonale.h"

static const uint8_t MAX_ELEMENTI = 5;

// Crea e alloca una diagonale
diagonale creaDiagonale() {
    diagonale d   = (diagonale)malloc(sizeof(struct Diagonale));
    d->Difficolta = 0;
    d->Punteggio  = 0;
    d->Elementi   = creaArray((void *)&freeElemento, (void *)&parseElemento, (void *)&printElemento);
    allocaArray(d->Elementi, MAX_ELEMENTI);
    return d;
}

// Calcola e restituisce la difficoltà di una diagonale
unsigned int difficoltaDiagonale(diagonale d) {
    d->Difficolta = 0;
    for (unsigned int i = 0; i < d->Elementi->ObjectsNumber; i++) {
        elemento tmp = (elemento)d->Elementi->Objects[i];
        d->Difficolta += tmp->Difficolta;
    }
    return d->Difficolta;
}

// Elimina una diagonale
void freeDiagonale(diagonale d) {
    freeArray(d->Elementi, false);
    free(d);
}

// Calcola e restituisce il punteggio di una diagonale
float punteggioDiagonale(diagonale d) {
    d->Punteggio = 0;
    for (unsigned int i = 0; i < d->Elementi->ObjectsNumber; i++) {
        elemento tmp = (elemento)d->Elementi->Objects[i];
        d->Punteggio += tmp->Valore;
    }
    return d->Punteggio;
}
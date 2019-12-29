#include "programma.h"

static const uint8_t NUMERO_DIAGONALI = 3;

/* Crea un programma acrobatico
   freeObject = funzione per eliminare il singolo oggetto
   printObject = funzione che si occupa di effettuare il parse del singolo oggetto da stringa
   parseObject = funzione che stampa il singolo oggetto */
programma creaGruppoDiagonali(void (*freeObject)(void *), void *(*parseObject)(char *), void (*printObject)(void *)) {
    programma g = calloc(NUMERO_DIAGONALI, sizeof(array));
    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) {
        g[i] = creaArray(freeObject, parseObject, printObject);
    }
}

// Elimina un programma acrobatico
void freeGruppoDiagonali(programma g) {
    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) {
        freeArray(g[i], false);
    }
}

// Genera il programma di punteggio massimo da un insieme di diagonali rispettando i limiti di difficoltà
// programma generaProgramma(array diagonali, unsigned int difficoltaDiagonale, unsigned int difficoltaProgramma) {
// }
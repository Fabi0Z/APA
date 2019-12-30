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

// Copia SRC in DEST
void copiaDiagonale(diagonale DEST, diagonale SRC) {
    DEST->Difficolta = SRC->Difficolta;
    DEST->Punteggio  = SRC->Punteggio;
    copiaArray(DEST->Elementi, SRC->Elementi);
}

// Calcola e restituisce la difficoltà di una diagonale
unsigned int calcolaDifficoltaDiagonale(diagonale d) {
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
float calcolaPunteggioDiagonale(diagonale d) {
    d->Punteggio = 0;
    for (unsigned int i = 0; i < d->Elementi->ObjectsNumber; i++) {
        elemento tmp = (elemento)d->Elementi->Objects[i];
        d->Punteggio += tmp->Valore;
    }
    return d->Punteggio;
}

// * Calcolo combinatorio

// Genera una diagonale rispettando il limite di difficoltà
unsigned int generaDiagonale(array elementi, diagonale soluzione, diagonale max, unsigned int posizione, unsigned int difficoltaDiagonale) {
    if (posizione >= MAX_ELEMENTI) { // Condizione di terminazione per eccesso di elementi
        return 1;
    }

    if (soluzione->Difficolta > difficoltaDiagonale) { // Condizione di terminazione per difficoltà massima
        return 2;
    }

    if (soluzione->Punteggio > max->Punteggio) { // Se la soluzione ha un incremento di punteggio
        copiaDiagonale(max, soluzione);
    }

    for (unsigned int i = 0; i < elementi->ObjectsNumber; i++) {        // Per ogni valore
        soluzione->Elementi->Objects[posizione] = elementi->Objects[i]; // Copio l'elemento successivo

        soluzione->Elementi->ObjectsNumber = posizione + 1;
        calcolaDifficoltaDiagonale(soluzione); // Ricalcolo la difficoltà
        calcolaPunteggioDiagonale(soluzione);  // Ricalcolo il punteggio

        generaDiagonale(elementi, soluzione, max, posizione + 1, difficoltaDiagonale);
    }

    return 0;
}
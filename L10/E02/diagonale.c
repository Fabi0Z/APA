#include "diagonale.h"

static const uint8_t MAX_ELEMENTI = 5;

/* Crea e alloca una diagonale
   Se NumeroElementi è pari a 0 il numero di elementi sarà il valore di default */
diagonale creaDiagonale(unsigned int NumeroElementi) {
    NumeroElementi = NumeroElementi == 0 ? MAX_ELEMENTI : NumeroElementi;
    diagonale d    = (diagonale)malloc(sizeof(struct Diagonale));
    d->Difficolta  = 0;
    d->Punteggio   = 0;
    d->Elementi    = creaArray((void *)&freeElemento, (void *)&parseElemento, (void *)&printElemento);
    allocaArray(d->Elementi, NumeroElementi);
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

// Genera tutte le diagonali possibili rispettando il limite di difficoltà e l'ordine di inserimento
unsigned int generaDiagonali(array elementi, diagonale soluzione, link list, unsigned int posizione, unsigned int difficoltaDiagonale) {
    unsigned int conto = 0;
    if (posizione >= MAX_ELEMENTI) { // Condizione di terminazione per eccesso di elementi
        return 0;
    }

    if (soluzione->Difficolta > difficoltaDiagonale) { // Condizione di terminazione per difficoltà massima
        return 0;
    }

    if (posizione > 0) { // Se è già presente almeno un elemento nella soluzione
        diagonale soluzioneDaSalvare = creaDiagonale(posizione - 1);

        unsigned int tempDimensione        = soluzione->Elementi->ObjectsNumber; // Salvo il numero di elementi
        soluzione->Elementi->ObjectsNumber = posizione - 1;

        copiaDiagonale(soluzioneDaSalvare, soluzione); // Copio i dati
        pushItem(list, (item)soluzioneDaSalvare);      // Salvo la soluzione

        soluzione->Elementi->ObjectsNumber = tempDimensione; // Ripristino la dimensione originale

        elemento previous = elementi->Objects[posizione - 1]; // Salvo l'elemento precedente
        if (previous->Finale) {                               // Se l'elemento non può esser seguito da altri elementi
            return 1;
        }
    }

loop:
    for (unsigned int i = 0; i < elementi->ObjectsNumber; i++) { // Per ogni valore
        elemento next = elementi->Objects[i];                    // Salvo l'elemento successivo

        if (posizione == 0) {       // Se mi trovo all'inizio di una sequenza
            if (next->Precedenza) { // Se l'elemento non può esser eseguito per primo
                i++;
                goto loop;
            }
        }

        soluzione->Elementi->Objects[posizione] = elementi->Objects[i]; // Copio l'elemento successivo

        soluzione->Elementi->ObjectsNumber = posizione + 1;
        calcolaDifficoltaDiagonale(soluzione); // Ricalcolo la difficoltà
        calcolaPunteggioDiagonale(soluzione);  // Ricalcolo il punteggio

        generaDiagonali(elementi, soluzione, list, posizione + 1, difficoltaDiagonale);
    }

    return conto;
}
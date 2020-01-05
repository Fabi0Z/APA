#include "diagonale.h"

static const uint8_t MAX_ELEMENTI = 5;

// Calcola e restituisce la difficoltà di una diagonale
unsigned int calcolaDifficoltaDiagonale(diagonale d) {
    d->Difficolta = 0;
    for (unsigned int i = 0; i < d->Elementi->ObjectsNumber; i++) {
        elemento tmp = (elemento)d->Elementi->Objects[i];
        d->Difficolta += tmp->Difficolta;
    }
    return d->Difficolta;
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

// Copia SRC in DEST
void copiaDiagonale(diagonale DEST, diagonale SRC) {
    DEST->Difficolta = SRC->Difficolta;
    DEST->Punteggio  = SRC->Punteggio;
    copyArray(DEST->Elementi, SRC->Elementi);
}

/* Crea e alloca una diagonale
   Se NumeroElementi è pari a 0 il numero di elementi sarà il valore di default */
diagonale creaDiagonale(unsigned int NumeroElementi) {
    NumeroElementi = NumeroElementi == 0 ? MAX_ELEMENTI : NumeroElementi;
    diagonale d    = (diagonale)malloc(sizeof(struct Diagonale));
    d->Difficolta  = 0;
    d->Punteggio   = 0;
    d->Elementi    = newArray((void *)&freeElemento, (void *)&parseElemento, (void *)&printElemento);
    allocateArray(d->Elementi, NumeroElementi);
    return d;
}

// Elimina una diagonale
void freeDiagonale(diagonale d) {
    freeArray(d->Elementi, false);
    free(d);
}

// Stampa una diagonale a video
void printDiagonale(diagonale d) {
    printf("Il punteggi della diagonale è %f e la sua difficoltà %u:\n", d->Punteggio, d->Difficolta);
    printArray(d->Elementi);
}

// * Calcolo combinatorio

// Genera tutte le diagonali possibili rispettando il limite di difficoltà e l'ordine di inserimento
unsigned int generaDiagonali(array elementi, diagonale soluzione, link list, unsigned int posizione, unsigned int difficoltaDiagonale) {
    unsigned int conto = 0;
    if (posizione >= soluzione->Elementi->ObjectsNumber) { // Condizione di terminazione per eccesso di elementi
        return 0;
    }

    if (soluzione->Difficolta > difficoltaDiagonale) { // Condizione di terminazione per difficoltà massima
        return 0;
    }

    if (posizione > 0) { // Se è già presente almeno un elemento nella soluzione
        diagonale soluzioneDaSalvare = creaDiagonale(posizione);

        uint8_t tempDimensione             = soluzione->Elementi->ObjectsNumber; // Salvo il numero di elementi
        soluzione->Elementi->ObjectsNumber = posizione;

        copiaDiagonale(soluzioneDaSalvare, soluzione); // Copio i dati
        pushItem(list, (item)soluzione);               // Salvo la soluzione

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

        uint8_t dimensioneTemp             = soluzione->Elementi->ObjectsNumber;
        soluzione->Elementi->ObjectsNumber = posizione + 1;
        calcolaDifficoltaDiagonale(soluzione); // Ricalcolo la difficoltà
        calcolaPunteggioDiagonale(soluzione);  // Ricalcolo il punteggio
        soluzione->Elementi->ObjectsNumber = dimensioneTemp;

        list = getHead(list);
        generaDiagonali(elementi, soluzione, list, posizione + 1, difficoltaDiagonale);
    }

    return conto;
}

// Ricalcola i controlli
bool updateChecks(diagonale d, checks c) {
    for (uint8_t i = 0; i < d->Elementi->ObjectsNumber; i++) {
        elemento temp = d->Elementi->Objects[i];
        if (temp->Ingresso == avanti) {
            c[elementoAvanti] = true;
        }
        if (temp->Ingresso == indietro) {
            c[elementoIndietro] = true;
        }
        if (i >= 1) {
            c[dueElementi] = true;
        }

        if (c[elementoAvanti] && c[elementoIndietro] && c[dueElementi]) { // Se sono tutte e tre verificate
            break;
        }
    }
    return c[elementoAvanti] && c[elementoIndietro] && c[dueElementi];
}

// Genera tutte le diagonali possibili rispettando il limite di difficoltà e l'ordine di inserimento
void generaDiagonaleR(array elementi, unsigned int difficoltaDiagonale, checks controlli, link soluzione, uint8_t elementiInseribili) {
    if (elementiInseribili == 0) { // Interruzione per limite di inserimenti
        return;
    }

    for (unsigned int i = 0; i < elementi->ObjectsNumber; i++) { // Esploro tutti gli elementi
        elemento tmp = elementi->Objects[i];
        if (tmp->Difficolta <= difficoltaDiagonale) { // Se l'elemento è inseribile
            putItem(soluzione, tmp);
            elementiInseribili--; // Riduco il numero di elementi inseribili
            // Ricorro per l'elemento successivo
            return generaDiagonaleR(elementi, (difficoltaDiagonale - tmp->Difficolta), controlli, soluzione, elementiInseribili);
        }
    }
}

// Genera la miglior diagonale in base ai limiti e ai controlli
diagonale generaDiagonale(array elementi, unsigned int DD, unsigned int DP, checks controlli) {
    diagonale maxDiagonale = creaDiagonale(0);
    generaDiagonaleR(elementi, DD, controlli, maxDiagonale, 0, 0);

    diagonale tempDiag = creaDiagonale(maxDiagonale->Elementi);
    copiaDiagonale(tempDiag, maxDiagonale);
    freeDiagonale(maxDiagonale);

    return tempDiag;
}

// Restituisce il valore massimo ottenibile come sequenza consecutiva dello stesso elemento senza superare una data diffioltà
unsigned int maxValoreConDifficolta(elemento e, unsigned int difficolta) {
    uint8_t nElementi              = 0;
    float valore                   = 0;
    unsigned int difficoltaAttuale = 0;
    while (nElementi < MAX_ELEMENTI, (difficoltaAttuale + e->Difficolta) <= difficolta) { // Sinché rientro nei limiti
        valore += e->Valore;
        difficoltaAttuale += e->Difficolta;
        nElementi++;
    }
    return valore;
}

// Restituisce true se l'elemento a è più ottimale rispetto a b
bool minorEqualValore(elemento a, elemento b, unsigned int *difficoltaDiagonale) {
    return maxValoreConDifficolta(a, *difficoltaDiagonale) <= maxValoreConDifficolta(b, *difficoltaDiagonale);
}
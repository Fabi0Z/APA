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
uint8_t generaDiagonaleR(array elementi, unsigned int difficoltaDiagonale, checks controlli, link soluzione, uint8_t elementiInseribili) {
    uint8_t elementiInseriti = 0;
    if (elementiInseribili == 0) { // Interruzione per limite di inserimenti
        return 0;
    }
    for (unsigned int i = 0; i < elementi->ObjectsNumber; i++) { // Esploro tutti gli elementi
        elemento tmp = elementi->Objects[i];
        if (tmp->Difficolta <= difficoltaDiagonale) { // Se l'elemento è inseribile
            putItem(soluzione, tmp);
            elementiInseribili--; // Riduco il numero di elementi inseribili
            elementiInseriti++;
            // Ricorro per l'elemento successivo
            elementiInseriti += generaDiagonaleR(elementi, (difficoltaDiagonale - tmp->Difficolta), controlli, soluzione, elementiInseribili);
        }
    }
    return elementiInseriti;
}

// Genera la miglior diagonale in base ai limiti e ai controlli
diagonale generaDiagonale(array elementi, unsigned int DD, unsigned int DP, checks controlli) {
    link maxDiagonale        = creaLink(NULL);
    uint8_t elementiInseriti = generaDiagonaleR(elementi, DD, controlli, maxDiagonale, MAX_ELEMENTI);

    diagonale tempDiag = creaDiagonale(elementiInseriti); // Creo la diagonale
    maxDiagonale       = getHead(maxDiagonale);           // La riporto alla head
    maxDiagonale       = maxDiagonale->Next;              // Punto sul primo elemento

    uint8_t index = 0;
    while (maxDiagonale->Next != NULL) {                           // Sinché ho elementi in lista
        tempDiag->Elementi->Objects[index++] = maxDiagonale->Item; // Inserisco l'elemento nella diagonale
    }

    // Ricalcolo i valori
    calcolaDifficoltaDiagonale(tempDiag);
    calcolaPunteggioDiagonale(tempDiag);

    freeList(maxDiagonale); // Elimino la lista

    return tempDiag;
}

// Restituisce il valore massimo ottenibile come sequenza consecutiva dello stesso elemento senza superare una data diffioltà
float maxValoreConDifficolta(elemento e, unsigned int difficolta) {
    uint8_t nElementi              = 0;
    float valore                   = 0;
    unsigned int difficoltaAttuale = 0;
    while (nElementi < MAX_ELEMENTI && (difficoltaAttuale + e->Difficolta) <= difficolta) { // Sinché rientro nei limiti
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
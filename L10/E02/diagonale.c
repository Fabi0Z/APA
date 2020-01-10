#include "diagonale.h"

// * STATIC ITEMS

static const uint8_t MAX_ELEMENTI = 5;

// Genera tutte le diagonali possibili rispettando il limite di difficoltà e l'ordine di inserimento
static uint8_t generaDiagonaleR(array elementi, unsigned int difficoltaDiagonale, checks controlli, link soluzione, unsigned int difficoltaMinima) {
    uint8_t elementiInseriti = 0;
    if (elementiInseriti == MAX_ELEMENTI) { // Interruzione per limite di inserimenti
        return 0;
    }
    if (difficoltaDiagonale == 0) { // Interruzione per limite di difficoltà
        return 0;
    }
    for (unsigned int i = 0; i < elementi->ObjectsNumber; i++) { // Esploro tutti gli elementi
        elemento tmp = elementi->Objects[i];
        if (insertCheck(tmp, difficoltaDiagonale, controlli, difficoltaMinima)) { // Se l'elemento è inseribile
            putItem(soluzione, tmp);
            elementiInseriti++;
            if (tmp->Finale) {
                return elementiInseriti;
            }
            // Ricorro per l'elemento successivo
            return elementiInseriti += generaDiagonaleR(elementi, (difficoltaDiagonale - tmp->Difficolta), controlli, soluzione, difficoltaMinima);
        }
    }
    return 0;
}

// * END OF STATIC ITEMS

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

    if (d->Elementi == NULL) {
        return d->Punteggio;
    }

    for (unsigned int i = 0; i < d->Elementi->ObjectsNumber; i++) {
        elemento tmp = (elemento)d->Elementi->Objects[i];
        d->Punteggio += tmp->Valore;
    }
    return d->Punteggio;
}

// Calcola e restituisce il punteggio della terza diagonale
float calcolaPunteggioTerzaDiagonale(diagonale d) {
    d->Punteggio = 0;

    if (d->Elementi == NULL) {
        return d->Punteggio;
    }

    bool moltiplicatore = false;
    for (unsigned int i = 0; i < d->Elementi->ObjectsNumber; i++) {
        elemento tmp   = (elemento)d->Elementi->Objects[i];
        moltiplicatore = tmp->Difficolta >= 8 ? true : moltiplicatore; // Controllo se ho almeno difficoltà 8
        d->Punteggio += tmp->Valore;
    }
    d->Punteggio *= moltiplicatore ? 1.5 : 1; // moltiplico il punteggio
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
    if (d == NULL) {
        return;
    }
    freeArray(d->Elementi, false);
    free(d);
}

// Stampa una diagonale a video
void printDiagonale(diagonale d) {
    printf("Il punteggio della diagonale è %f e la sua difficoltà %u:\n", d->Punteggio, d->Difficolta);
    printArray(d->Elementi);
}

// Ricalcola i controlli
bool updateChecks(elemento e, checks c, unsigned int difficoltaMassima, unsigned int difficoltaMinima) {
    bool valido = false;
    if (c->Richiesti[elementoAvanti]) { // Se il controllo è richiesto
        if (e->Ingresso == avanti) {
            c->Valori[elementoAvanti]    = true;
            c->Richiesti[elementoAvanti] = false; // Rimuovo la richiesta
        }
    }
    if (c->Richiesti[elementoIndietro]) { // Se il controllo è richiesto
        if (e->Ingresso == indietro) {
            c->Valori[elementoIndietro]    = true;
            c->Richiesti[elementoIndietro] = false; // Rimuovo la richiesta
        }
    }
    if (c->Richiesti[dueElementi]) {                                               // Se il controllo è richiesto
        if (difficoltaMinima <= difficoltaMassima - e->Difficolta && !e->Finale) { // Se rientro nel limite dell'elemento di difficoltà minima e se l'elemento non è un finale
            c->Valori[dueElementi]    = true;
            c->Richiesti[dueElementi] = false; // Rimuovo la richiesta
        }
    }
    return verificaChecks(c);
}

// Verifica se un elemento può esser inserito nella diagonale
bool insertCheck(elemento e, unsigned int difficoltaDiagonale, checks controlli, unsigned int difficoltaMinima) {
    if (e->Difficolta > difficoltaDiagonale) { // Interruzione per limite difficoltà
        return false;
    }
    if (!updateChecks(e, controlli, difficoltaDiagonale, difficoltaMinima)) { // Interruzione basata sui controlli
        return false;
    }
    return true;
}

// Genera la miglior diagonale in base ai limiti e ai controlli
diagonale generaDiagonale(array elementi, unsigned int DD, checks controlli, unsigned int difficoltaMinima) {
    link maxDiagonale        = creaLink(NULL);
    uint8_t elementiInseriti = generaDiagonaleR(elementi, DD, controlli, maxDiagonale, difficoltaMinima);
    diagonale tempDiag       = creaDiagonale(elementiInseriti); // Creo la diagonale

    if (elementiInseriti > 0) {
        uint8_t index = 0;
        while (maxDiagonale->Next != NULL) { // Sinché ho elementi in lista
            maxDiagonale                         = maxDiagonale->Next;
            tempDiag->Elementi->Objects[index++] = maxDiagonale->Item; // Inserisco l'elemento nella diagonale
        }

        // Ricalcolo i valori
        calcolaDifficoltaDiagonale(tempDiag);
        calcolaPunteggioDiagonale(tempDiag);

    } else {
        tempDiag->Elementi = 0;
    }

    freeList(maxDiagonale); // Elimino la lista
    return tempDiag;
}

// Restituisce il valore massimo ottenibile come sequenza consecutiva dello stesso elemento senza superare una data diffioltà
float maxValoreConDifficolta(elemento e, unsigned int difficolta, bool moltiplicatore) {
    uint8_t nElementi              = 0;
    float valore                   = 0;
    unsigned int difficoltaAttuale = 0;
    while (nElementi < MAX_ELEMENTI && (difficoltaAttuale + e->Difficolta) <= difficolta) { // Sinché rientro nei limiti
        valore += e->Valore;
        difficoltaAttuale += e->Difficolta;
        nElementi++;
        if (e->Finale) { // Se l'elemento è di tipo finale mi interrompo ad un solo inserimento
            break;
        }
    }
    valore *= difficoltaAttuale && moltiplicatore >= 8 ? 1.5 : 1; // Se il moltiplicatore è attivo incremento il punteggio
    return valore;
}

// Restituisce true se l'elemento a è più ottimale rispetto a b
bool maggiorValore(elemento a, elemento b, unsigned int *difficoltaDiagonale) {
    return maxValoreConDifficolta(a, *difficoltaDiagonale, false) > maxValoreConDifficolta(b, *difficoltaDiagonale, false);
}

// Restituisce true se l'elemento a è più ottimale rispetto a b
bool maggiorValoreConMoltiplicatore(elemento a, elemento b, unsigned int *difficoltaDiagonale) {
    return maxValoreConDifficolta(a, *difficoltaDiagonale, true) > maxValoreConDifficolta(b, *difficoltaDiagonale, true);
}
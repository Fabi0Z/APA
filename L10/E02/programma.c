#include "programma.h"

static const uint8_t NUMERO_DIAGONALI = 3;

// Calcola la difficoltà di un programma
unsigned int calcolaDifficoltaProgramma(programma p) {
    p->Difficolta = 0;
    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) {
        p->Difficolta += p->Diagonali[i]->Difficolta;
    }
    return p->Difficolta;
}

/* Funzione per generare le combinazioni ripetute
   Il limite di elementi k è dato dalla lunghezza dell'array soluzione
   Nella chiamata posizione e start devono esser pari a 0 */
void combinazioniRipetuteProgramma(unsigned int posizione, array valori, programma soluzione, programma max, unsigned int start, unsigned int difficoltaProgramma) {
    if (posizione >= NUMERO_DIAGONALI) {
        if (!verificaProgramma(soluzione, difficoltaProgramma)) { // Se il programma non è valido
            return;
        }

        if (soluzione->Punteggio > max->Punteggio) { // Se il punteggio è maggiore
            copiaProgramma(soluzione, max);          // Salvo il programma
        }
        return;
    }
    for (unsigned i = start; i < valori->ObjectsNumber; i++) {
        soluzione->Diagonali[posizione] = valori->Objects[i];
        combinazioniRipetuteRecursive(posizione + 1, valori, soluzione, max, start, difficoltaProgramma);
        start++;
    }
}

// Copia SRC in DEST
void copiaProgramma(programma DEST, programma SRC) {
    DEST->Difficolta = SRC->Difficolta;
    DEST->Punteggio  = SRC->Punteggio;
    memcpy(DEST->Diagonali, SRC->Diagonali, sizeof(diagonale) * NUMERO_DIAGONALI);
}

// Crea un programma acrobatico
programma creaProgramma() {
    programma p  = malloc(sizeof(struct Programma));                         // Creo il programma
    p->Diagonali = (diagonale *)calloc(NUMERO_DIAGONALI, sizeof(diagonale)); // Creo l'array di diagonali

    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) { // Per ogni diagonale
        p->Diagonali[i] = creaDiagonale(0);
    }

    p->Difficolta = 0;
    p->Punteggio  = 0;

    return p;
}

// Elimina un programma acrobatico
void freeProgramma(programma p) {
    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) { // Per ogni diagonale
        freeDiagonale(p->Diagonali[i]);
    }
    free(p->Diagonali);
    free(p);
}

/* Genera il miglior programma dati i limiti di difficoltà
   DD = Limite di difficoltà per la diagonale
   DP = Limite di difficolta per il programma */
programma generaMigliorProgramma(array elementi, unsigned int DD, unsigned int DP) {
    programma p               = creaProgramma();
    unsigned int maxPunteggio = 0;
}

// Verifica che un programma rispetti tutti i limiti
bool verificaProgramma(programma p, unsigned int difficoltaProgramma) {
    if (calcolaDifficoltaProgramma(p) > difficoltaProgramma) {
        return false;
    }

    bool elementoAvanti   = false;
    bool elementoIndietro = false;
    bool diagDueElementi  = false;
    uint8_t index         = 0;

    // Sinché almeno uno degli elementi è false esploro le diagonali
    while (!elementoAvanti || !elementoIndietro || !diagDueElementi && index < NUMERO_DIAGONALI) {
        array temp = p->Diagonali[index++]->Elementi->Objects;

        diagDueElementi = temp->ObjectsNumber >= 2 ? true : diagDueElementi; // Controllo se la diagonale ha almeno due elementi

        for (uint8_t i = 0; i < temp->ObjectsNumber; i++) { // Per ogni oggetto nell'array
            elemento tempElemento = temp->Objects[i];
            switch (tempElemento->Ingresso) {
                case avanti:
                    elementoAvanti = true;
                    break;

                case indietro:
                    elementoIndietro = true;
                    break;
            }
        }
    }

    return elementoAvanti && elementoIndietro && diagDueElementi;
}
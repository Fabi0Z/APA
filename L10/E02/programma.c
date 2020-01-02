#include "programma.h"

static const uint8_t NUMERO_DIAGONALI = 3;

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
    programma p                    = creaProgramma();
    unsigned int difficoltaAttuale = 0;

    // A ogni giro incremento la difficoltà massima del programma sinché non raggiungo 
    for (unsigned int i = 0; i < DP; i += NUMERO_DIAGONALI) {
        /* code */
    }
}

// Verifica che un programma rispetti tutti i limiti
bool verificaProgramma(programma p, unsigned int difficoltaDiagonale, unsigned int difficoltaProgramma) {
    bool elementoAvanti   = false;
    bool elementoIndietro = false;
    bool diagDueElementi  = false;
}
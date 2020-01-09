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

// Calcola il punteggio di un programma
float calcolaPunteggioProgramma(programma p) {
    p->Punteggio = 0;

    diagonale ultimaDiagonale   = p->Diagonali[NUMERO_DIAGONALI - 1];
    uint8_t ultimoElementoIndex = ultimaDiagonale->Elementi->ObjectsNumber - 1;
    elemento ultimoElemento     = ultimaDiagonale->Elementi->Objects[ultimoElementoIndex];
    if (ultimoElemento->Finale) {          // Se è un elemento finale
        ultimaDiagonale->Punteggio *= 1.5; // Moltiplico il punteggio
    }

    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) { // Sommo i valori delle diagonali
        p->Punteggio += p->Diagonali[i]->Punteggio;
    }
    return p->Punteggio;
}

// Copia SRC in DEST
void copiaProgramma(programma DEST, programma SRC) {
    DEST->Difficolta = SRC->Difficolta;
    DEST->Punteggio  = SRC->Punteggio;
    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) {           // Per ogni diagonale
        copiaDiagonale(DEST->Diagonali[i], SRC->Diagonali[i]); // Copio la diagonale
    }
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

// Aggiorna il limite di difficoltà
static unsigned int updateLimiteDifficolta(unsigned int difficoltaDiagonalePrecedente, unsigned int DD, unsigned int *DP) {
    *DP -= difficoltaDiagonalePrecedente;
    return *DP < DD ? *DP : DD;
}

programma generaMigliorProgramma(array elementi, unsigned int DD, unsigned int DP) {
    printArray(elementi);
    programma p         = creaProgramma();                                // Programma contenente la soluzione
    checks controlli    = newChecks();                                    // Creo i controlli
    elemento diffMinima = getMinOrMax(elementi, (void *)&minoreElemento); // Salvo l'elemento di difficoltà minima
    DP -= diffMinima->Difficolta;                                         // Imposto il limite minimo per l'ultima diagonale generata

    // Genero la terza diagonale di almeno due elementi
    mergeSort(elementi, (void *)&maggiorValoreConMoltiplicatore, &DD); // Ordino l'array
    controlli[dueElementi] = true;
    p->Diagonali[2]        = generaDiagonale(elementi, 10, updateLimiteDifficolta(0, DD, &DP), controlli);

    // Genero la prima diagonale
    mergeSort(elementi, (void *)&maggiorValore, &DD); // Ordino l'array per le restanti diagonali
    controlli[elementoIndietro] = true;               // Rimuovo la richiesta di un limite indietro
    controlli[elementoAvanti]   = false;              // Aggiungo la richiesta di un elemento in avanti
    diagonale tmpDiagonale      = p->Diagonali[2];
    p->Diagonali[0]             = generaDiagonale(elementi, updateLimiteDifficolta(tmpDiagonale->Difficolta, DD, &DP), DP, controlli);

    // Genero la seconda diagonale
    DP += diffMinima->Difficolta; // Rimuovo il limite
    controlli[elementoIndietro] = false;
    tmpDiagonale                = p->Diagonali[1];
    p->Diagonali[1]             = generaDiagonale(elementi, updateLimiteDifficolta(tmpDiagonale->Difficolta, DD, &DP), DP, controlli);

    calcolaDifficoltaProgramma(p);
    calcolaPunteggioProgramma(p);

    free(controlli);
    return p; // Restituisco il programma
}

// Stampa un programma a video
void printProgramma(programma p) {
    printf("Il punteggio del programma vale %f e la sua difficoltà è %u:\n", p->Punteggio, p->Difficolta);
    for (uint8_t i = 0; i < NUMERO_DIAGONALI; i++) {
        printDiagonale(p->Diagonali[i]);
    }
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
        array temp = p->Diagonali[index++]->Elementi;

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
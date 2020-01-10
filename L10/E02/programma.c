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
    if (p == NULL) {
        return;
    }
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

static void programmaPerTerzaDiagonale(array a, unsigned int difficoltaDiagonale) {
    mergeSort(a, (void *)&maggiorValoreConMoltiplicatore, &difficoltaDiagonale); // Eseguo l'ordinamento
    elemento miglioreDa8 = a->Objects[0];
    mergeSort(a, (void *)&maggiorValore, &difficoltaDiagonale); // Ordino l'array per convenienza
    moveItemArray(a, miglioreDa8, 0);                           // Sposto l'elemento migliore da 8 in prima posizione
}

// Genera un programma in base ai limiti dati
static programma generaProgramma(array elementi, unsigned int DD, unsigned int DP) {
    programma p         = creaProgramma();                                // Programma contenente la soluzione
    checks controlli    = newChecks();                                    // Creo i controlli
    elemento diffMinima = getMinOrMax(elementi, (void *)&minoreElemento); // Salvo l'elemento di difficoltà minima
    DP -= diffMinima->Difficolta;                                         // Imposto il limite minimo per l'ultima diagonale generata
    unsigned int DPbackup = DP;                                           // Faccio un "backup" della difficoltà
    diagonale tmpDiagonale;                                               // Creo la diagonale d'appoggio

    // Genero la terza diagonale
    programmaPerTerzaDiagonale(elementi, updateLimiteDifficolta(0, DD, &DP));                                           // Ordino l'array per la terza
    p->Diagonali[2] = generaDiagonale(elementi, updateLimiteDifficolta(0, DD, &DP), controlli, diffMinima->Difficolta); // Genero la diagonale
    tmpDiagonale    = p->Diagonali[2];

// Genero la prima diagonale
primeDueDiagonali:
    mergeSort(elementi, (void *)&maggiorValore, &DD); // Ordino l'array per le restanti diagonali
    controlli->Richiesti[elementoAvanti] = true;      // Aggiungo la richiesta di un elemento in avanti
    p->Diagonali[0]                      = generaDiagonale(elementi, updateLimiteDifficolta(tmpDiagonale->Difficolta, DD, &DP), controlli, diffMinima->Difficolta);
    tmpDiagonale                         = p->Diagonali[0];

    // Genero la seconda diagonale
    DP += diffMinima->Difficolta;                  // Rimuovo il limite
    controlli->Richiesti[elementoIndietro] = true; // Aggiungo la richiesta di un elemento indietro
    p->Diagonali[1]                        = generaDiagonale(elementi, updateLimiteDifficolta(tmpDiagonale->Difficolta, DD, &DP), controlli, diffMinima->Difficolta);
    tmpDiagonale                           = p->Diagonali[1];

    if (controlli->Valori[dueElementi]) { // Se non sono presenti due elementi in alcuna diagonale
        freeProgramma(p);                 // Elimino il programma
        freeChecks(controlli);            // Elimino i controlli
        controlli   = newChecks();        // Ricreo i controlli
        programma p = creaProgramma();    // Ricreo il programma
        DP          = DPbackup;
        DP -= diffMinima->Difficolta; // Imposto il limite minimo per l'ultima diagonale generata

        // Genero la terza diagonale
        controlli->Richiesti[dueElementi] = true;
        mergeSort(elementi, (void *)&maggiorValoreConMoltiplicatore, &DD);                                                  // Ordino l'array per la terza
        p->Diagonali[2] = generaDiagonale(elementi, updateLimiteDifficolta(0, DD, &DP), controlli, diffMinima->Difficolta); // Genero la diagonale

        goto primeDueDiagonali; // Ricreo le prime due diagonali
    }

    calcolaDifficoltaProgramma(p);
    calcolaPunteggioProgramma(p);

    free(controlli);
    return p; // Restituisco il programma
}

// Genera il programma di massima lunghezza
programma generaMigliorProgramma(array elementi, unsigned int DD, unsigned int DP) {
    programma migliore, tmp;

    // Inizializzo la prima variabile
    migliore = generaProgramma(elementi, 1, DP); // Creo il programma con DD pari a 1

    // Genero il miglior programma
    for (unsigned int i = 2; i <= DD; i++) {        // Per ogni livello di difficoltà
        tmp = generaProgramma(elementi, i, DP);     // Creo il programma con DD incrementale
        if (tmp->Punteggio > migliore->Punteggio) { // Controllo se il programma generato è migliore
            freeProgramma(migliore);
            migliore = tmp;
        } else {
            freeProgramma(tmp); // Scaro il programma appena generato
        }
    }

    return migliore;
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
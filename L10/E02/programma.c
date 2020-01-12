#include "programma.h"

// * STATIC ITEMS

static const uint8_t NUMERO_DIAGONALI = 3;
static const uint8_t DIFFICOLTA_BONUS = 8;

// Aggiorna il limite di difficoltà
static unsigned int updateLimiteDifficolta(unsigned int difficoltaDiagonalePrecedente, unsigned int DD, unsigned int *DP) {
    *DP -= difficoltaDiagonalePrecedente;
    return *DP < DD ? *DP : DD;
}

// Riordina gli elementi per la terza diagonale
static void programmaPerTerzaDiagonale(array a, unsigned int difficoltaDiagonale, elemento elementoMinimo) {
    array maggioriDiBonus = validItemsArray(a, (void *)&elementoIsMajorEqualThanBonus, (item)&DIFFICOLTA_BONUS); // Creo un array contenente solo gli elementi con difficoltà da bonus in su

    void *args[2] = {&difficoltaDiagonale, (void *)&DIFFICOLTA_BONUS};         // Creo gli argomenti per il sorting
    mergeSort(maggioriDiBonus, (void *)&maggiorValoreConMoltiplicatore, args); // Eseguo l'ordinamento

    elemento miglioreDelBonus = maggioriDiBonus->Objects[0]; // Salvo l'elemento con bonus migliore
    if (miglioreDelBonus->Precedenza) {                      // Se ha requisito di precedenza
        unsigned int tempDifficolta = difficoltaDiagonale - elementoMinimo->Difficolta;
        args[0]                     = &tempDifficolta;
        mergeSort(maggioriDiBonus, (void *)&maggiorValoreConMoltiplicatore, args); // Eseguo l'ordinamento
        miglioreDelBonus = maggioriDiBonus->Objects[0];                            // Salvo l'elemento con bonus migliore
    }

    freeArray(maggioriDiBonus, false); // Elimino l'array

    mergeSort(a, (void *)&maggiorValore, &difficoltaDiagonale); // Ordino l'array per convenienza
    moveItemArray(a, miglioreDelBonus, 0);                      // Sposto l'elemento migliore secondo il bonus in prima posizione
}

static programma generaDiagonaliPerProgramma(array elementi, unsigned int DD, unsigned int DP, checks c) {
    unsigned int DPBackup = DP;
    programma p           = creaProgramma();                                // Programma contenente la soluzione
    elemento diffMinima   = getMinOrMax(elementi, (void *)&minoreElemento); // Salvo l'elemento di difficoltà minima
    DP -= diffMinima->Difficolta;                                           // Imposto il limite minimo per l'ultima diagonale generata
    diagonale tmpDiagonale;                                                 // Creo la diagonale d'appoggio

    // Genero la terza diagonale
    if (DD >= DIFFICOLTA_BONUS) {                                                                         // Se la difficoltà per diagonale rientra nel bonus
        programmaPerTerzaDiagonale(elementi, updateLimiteDifficolta(0, DD, &DP), diffMinima); // Ordino l'array per la terza
    } else {
        mergeSort(elementi, (void *)&maggiorValore, &DD); // Ordino l'array per convenienza
    }
    p->Diagonali[2] = generaDiagonale(elementi, updateLimiteDifficolta(0, DD, &DP), c, diffMinima); // Genero la diagonale
    tmpDiagonale    = p->Diagonali[2];
    calcolaPunteggioTerzaDiagonale(tmpDiagonale);

    // Genero la prima diagonale
    if (DD >= DIFFICOLTA_BONUS) {                         // Se la difficoltà per diagonale rientra nel bonus
        mergeSort(elementi, (void *)&maggiorValore, &DD); // Ordino l'array per convenienza
    }
    c->Richiesti[elementoAvanti] = true; // Aggiungo la richiesta di un elemento in avanti
    p->Diagonali[0]              = generaDiagonale(elementi, updateLimiteDifficolta(tmpDiagonale->Difficolta, DD, &DP), c, diffMinima);
    tmpDiagonale                 = p->Diagonali[0];

    // Genero la seconda diagonale
    DP += diffMinima->Difficolta;          // Rimuovo il limite
    c->Richiesti[elementoIndietro] = true; // Aggiungo la richiesta di un elemento indietro
    p->Diagonali[1]                = generaDiagonale(elementi, updateLimiteDifficolta(tmpDiagonale->Difficolta, DD, &DP), c, diffMinima);
    tmpDiagonale                   = p->Diagonali[1];

    return p;
}

// Genera un programma in base ai limiti dati
static programma generaProgramma(array elementi, unsigned int DD, unsigned int DP) {
    checks c    = newChecks(); // Creo i controlli
    programma p = generaDiagonaliPerProgramma(elementi, DD, DP, c);

    if (!c->Valori[dueElementi]) {               // Se non sono presenti due elementi in alcuna diagonale
        freeProgramma(p);                        // Elimino il programma
        freeChecks(c);                           // Elimino i controlli
        c                         = newChecks(); // Ricreo i controlli
        c->Richiesti[dueElementi] = true;        // Aggiungo la richiesta di due elementi
        p                         = generaDiagonaliPerProgramma(elementi, DD, DP, c);
    }

    calcolaDifficoltaProgramma(p);
    calcolaPunteggioProgramma(p);
    free(c);
    return p; // Restituisco il programma
}

// * END OF STATIC ITEMS

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

// Genera il programma di massima lunghezza
programma generaMigliorProgramma(array elementi, unsigned int DD, unsigned int DP) {
    // programma migliore, tmp;

    // // Inizializzo la prima variabile
    // migliore = generaProgramma(elementi, 1, DP); // Creo il programma con DD pari a 1

    // // Genero il miglior programma
    // for (unsigned int i = 2; i <= DD; i++) {        // Per ogni livello di difficoltà
    //     tmp = generaProgramma(elementi, i, DP);     // Creo il programma con DD incrementale
    //     if (tmp->Punteggio > migliore->Punteggio) { // Controllo se il programma generato è migliore
    //         freeProgramma(migliore);
    //         migliore = tmp;
    //     } else {
    //         freeProgramma(tmp); // Scaro il programma appena generato
    //     }
    // }
    // return migliore;
    return generaProgramma(elementi, DD, DP); // Creo il programma con DD pari a 1
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
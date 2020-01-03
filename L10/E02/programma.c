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

/* Funzione per generare le combinazioni ripetute
   Il limite di elementi k è dato dalla lunghezza dell'array soluzione
   Nella chiamata posizione e start devono esser pari a 0 */
void combinazioniRipetuteProgramma(unsigned int posizione, array valori, programma soluzione, programma max, unsigned int start, unsigned int difficoltaProgramma) {
    if (posizione >= NUMERO_DIAGONALI) {
        if (!verificaProgramma(soluzione, difficoltaProgramma)) { // Se il programma non è valido
            return;
        }

        if (calcolaPunteggioProgramma(soluzione) > max->Punteggio) { // Se il punteggio è maggiore
            copiaProgramma(soluzione, max);                          // Salvo il programma
        }
        return;
    }
    for (unsigned i = start; i < valori->ObjectsNumber; i++) {
        soluzione->Diagonali[posizione] = valori->Objects[i];

        combinazioniRipetuteProgramma(posizione + 1, valori, soluzione, max, start, difficoltaProgramma);
        start++;
    }
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

/* Genera il miglior programma dati i limiti di difficoltà
   DD = Limite di difficoltà per la diagonale
   DP = Limite di difficolta per il programma */
programma generaMigliorProgramma(array elementi, unsigned int DD, unsigned int DP) {
    programma p             = creaProgramma(); // Programma contenente la soluzione
    programma tempProgramma = creaProgramma(); // Programma d'appoggio

    link listaDiagonali            = creaLink(NULL);   // Lista contenente tutto le diagonali
    diagonale tempDiag             = creaDiagonale(0); // Diagonale d'appoggio per la soluzione
    unsigned int diagonaliGenerate = generaDiagonali(elementi, tempDiag, listaDiagonali, 0, DD);
    freeDiagonale(tempDiag); // Elimino la diagonale d'appoggio

    array arrayDiagonali = creaArray((void *)&freeDiagonale, NULL, NULL); // Array contenente le diagonali generate
    allocaArray(arrayDiagonali, diagonaliGenerate);
    listaDiagonali = listaDiagonali->Next;
    unsigned i     = 0;                                       // Indice d'esplorazione dell'array
    while (listaDiagonali != NULL && i < diagonaliGenerate) { // Sinché posso esplorare
        arrayDiagonali->Objects[i++] = listaDiagonali->Item;  // Copio il dato dalla lista all'array
        listaDiagonali               = listaDiagonali->Next;  // Vado al passo successivo
    }
    freeList(listaDiagonali); // Elimino la lista

    combinazioniRipetuteProgramma(0, arrayDiagonali, tempProgramma, p, 0, DP); // Genero il programma migliore
    freeArray(arrayDiagonali, true);                                           // Elimino l'array
    return p;                                                                  // Restituisco il programma
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
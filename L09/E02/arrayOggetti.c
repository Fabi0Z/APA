#include "arrayOggetti.h"

struct ArrayOggetti {
    oggetto *Array;
    unsigned int NumeroOggetti;
};

// * Funzioni "private"

// Rialloca in maniera sicura un array di puntatori a oggetto
void arrayOggettiRealloc(arrayOggetti a, unsigned int newSize) {
    arrayOggetti new = allocaArrayOggetti(newSize);
    memcpy(new->Array, a->Array, sizeof(oggetto *) * newSize);

    // Scambio gli array
    struct ArrayOggetti temp = *a;
    *a                       = *new;
    *new                     = temp;

    freeArrayOggetti(new, false);
}

// * Funzioni per il file header

// Aggiunge un oggetto ad un array di oggetti
void aggiungiOggettoArray(arrayOggetti a, oggetto o) {
    if (a->NumeroOggetti == 0) { // Se non ho oggetti
        freeArrayOggetti(a, false);
        a           = allocaArrayOggetti(1);
        a->Array[0] = o;
        return;
    }

    arrayOggettiRealloc(a, a->NumeroOggetti + 1); // Rialloco l'array
    a->Array[a->NumeroOggetti - 1] = o;           // Inserisco il nuovo oggetto
}

// Alloca un array di oggetti di lunghezza "items"
arrayOggetti allocaArrayOggetti(unsigned int items) {
    arrayOggetti a   = creaArrayOggetti();
    a->NumeroOggetti = items;
    a->Array         = (oggetto *)calloc(items, sizeof(oggetto));
    return a;
}

// Copia gli oggetti di src in dest
void copiaArrayOggetti(arrayOggetti dest, arrayOggetti src) {
    unsigned int min = dest->NumeroOggetti < src->NumeroOggetti ? dest->NumeroOggetti : src->NumeroOggetti;
    for (unsigned int i = 0; i < min; i++) { // Per il numero minimo di oggetti
        copiaOggetto(dest->Array[i], src->Array[i]);
    }
}

// Crea un array di oggetti
arrayOggetti creaArrayOggetti() {
    arrayOggetti a   = (arrayOggetti)malloc(sizeof(struct ArrayOggetti));
    a->Array         = NULL;
    a->NumeroOggetti = 0;
    return a;
}

// Dealloca un elemento di tipo arrayOggetti, se il parametro elementi è true libera anche gli oggetti dentro l'array
void freeArrayOggetti(arrayOggetti a, bool elementi) {
    if (elementi) {
        for (unsigned int i = 0; i < a->NumeroOggetti; i++) { // Per ogni oggetto
            freeOggetto(a->Array[i]);
        }
    }
    free(a);
}

// Restituisce il numero di oggetti
unsigned int getNumeroOggetti(arrayOggetti a) {
    return a->NumeroOggetti;
}

// Restituisce l'oggetto nella posizione index dell'array
oggetto getOggettoByIndex(arrayOggetti a, unsigned int index) {
    return a->Array[index];
}

// Cerca un oggetto per nome nell'array di oggetti, se non lo trova restituisce NULL
oggetto getOggettoByName(arrayOggetti a, char *nome) {
    for (unsigned int i = 0; i < a->NumeroOggetti; i++) {     // Per ogni oggetto
        if (strcmp(nome, getNomeOggetto(a->Array[i])) == 0) { // Se il nome corrisponde
            return a->Array[i];
        }
    }
    return NULL;
}

// Stampa un array di oggetti su file
void printArrayOggetti(arrayOggetti a, FILE *stream, bool indici) {
    for (unsigned int i = 0; i < a->NumeroOggetti; i++) {
        if (indici) {
            fprintf(stream, "%d - ", i);
        }
        printOggetto(a->Array[i], stream);
    }
    printf("\n");
}

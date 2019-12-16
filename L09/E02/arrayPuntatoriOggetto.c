#include "arrayPuntatoriOggetto.h"

struct ArrayPuntatoriOggetto {
    oggetto **Array;
    unsigned int NumeroOggetti;
};

// * Funzioni "private"

// Rialloca in maniera sicura un array di puntatori a oggetto
void arrayPuntatoriOggettoRealloc(arrayPuntatoriOggetto a, unsigned int newSize) {
    arrayPuntatoriOggetto new = allocaArrayPuntatoriOggetto(newSize);
    memcpy(new->Array, a->Array, sizeof(oggetto **) * newSize);

    // Scambio gli array
    struct ArrayPuntatoriOggetto temp = *a;
    *a                                = *new;
    *new                              = temp;

    freeArrayPuntatoriOggetto(new, false);
}

// * Funzioni per il file header

// Aggiunge un puntatore a oggetto ad un array di puntatori a oggetti
void aggiungiOggettoArrayPuntatori(arrayPuntatoriOggetto a, oggetto *o) {
    if (a->NumeroOggetti == 0) { // Se non ho oggetti
        freeArrayPuntatoriOggetto(a, false);
        a           = allocaArrayPuntatoriOggetto(1);
        a->Array[0] = o;
        return;
    }

    arrayPuntatoriOggettoRealloc(a, a->NumeroOggetti + 1); // Rialloco l'array
    a->Array[a->NumeroOggetti - 1] = o;                    // Inserisco il nuovo oggetto
}

// Alloca un array di puntatori a oggetto di lunghezza "items"
arrayPuntatoriOggetto allocaArrayPuntatoriOggetto(unsigned int items) {
    arrayPuntatoriOggetto a = creaArrayPuntatoriOggetto();
    a->NumeroOggetti        = items;
    a->Array                = (oggetto **)calloc(items, sizeof(oggetto *));
    return a;
}

// Copia SRC in DEST
void copiaArrayPuntatoriOggetto(arrayPuntatoriOggetto dest, arrayPuntatoriOggetto src) {
    dest->NumeroOggetti = src->NumeroOggetti;
    memcpy(dest->Array, src->Array, sizeof(oggetto **) * src->NumeroOggetti);
}

// Crea un array di di puntatori a oggetto
arrayPuntatoriOggetto creaArrayPuntatoriOggetto() {
    arrayPuntatoriOggetto a = (arrayPuntatoriOggetto)malloc(sizeof(struct ArrayPuntatoriOggetto));
    a->Array                = NULL;
    a->NumeroOggetti        = 0;
    return a;
}

// Dealloca un elemento di tipo arrayPuntatoriOggetto, se il parametro elementi è true libera anche gli oggetti dentro l'array
void freeArrayPuntatoriOggetto(arrayPuntatoriOggetto a, bool elementi) {
    if (elementi) {
        for (unsigned int i = 0; i < a->NumeroOggetti; i++) { // Per ogni oggetto
            freeOggetto(*a->Array[i]);
        }
    }
    for (unsigned int i = 0; i < a->NumeroOggetti; i++) { // Per ogni oggetto
        free(a->Array[i]);
    }
    free(a);
}

// Restituisce il numero di puntatori
unsigned int getNumeroPuntatori(arrayPuntatoriOggetto a) {
    return a->NumeroOggetti;
}

// Ricerca e restituisce l'indice incrementato di 1 del puntatore a oggetto di un dato oggetto
unsigned int getIndexPuntatoreOggetto(arrayPuntatoriOggetto a, oggetto o) {
    for (unsigned int i = 0; i < a->NumeroOggetti; i++) { // Per ogni oggetto
        if (*a->Array[i] = o) {                           // Se l'ho trovato
            return i + 1;
        }
    }
    return 0; // Altrimenti restituisco 0
}

// Restituisce il puntatore a oggetto nella posizione index dell'array
oggetto *getPuntatoreOggettoByIndex(arrayPuntatoriOggetto a, unsigned int index) {
    return a->Array[index];
}

// Cerca un puntatore a oggetto per nome nell'array di oggetti, se non lo trova restituisce NULL
oggetto *getPuntatoreOggettoByName(arrayPuntatoriOggetto a, char *nome) {
    for (unsigned int i = 0; i < a->NumeroOggetti; i++) { // Per ogni oggetto
        oggetto temp = *a->Array[i];
        if (strcmp(nome, getNomeOggetto(temp)) == 0) { // Se il nome corrisponde
            return a->Array[i];
        }
    }
    return NULL;
}

// Stampa un oggetto su file
void printArrayPuntatoriOggetto(arrayPuntatoriOggetto a, FILE *stream, bool indici) {
    for (unsigned int i = 0; i < a->NumeroOggetti; i++) {
        if (indici) {
            fprintf(stream, "%d - ", i);
        }
        printOggetto(*a->Array[i], stream);
    }
    printf("\n");
}

// Rimuove un puntatore a oggetto, restituisce false se non rimangono puntatori nell'array
bool rimuoviPuntatoreOggetto(arrayPuntatoriOggetto a, oggetto o) {
    unsigned int index = getIndexPuntatoreOggetto(a, o);
    if (index == 0) { // Se non ho trovato l'oggetto
        return true;
    } else if (index = a->NumeroOggetti) { // Se si tratta dell'ultimo oggetto
        arrayPuntatoriOggettoRealloc(a, a->NumeroOggetti - 1);
        return true;
    }

    if (a->NumeroOggetti == 1) { // Se ho un solo oggetto
        freeArrayPuntatoriOggetto(a, false);
        return false;
    }

    index--;

    arrayPuntatoriOggetto new = allocaArrayPuntatoriOggetto(a->NumeroOggetti - 1);
    memcpy(new->Array, a->Array, sizeof(oggetto **) * index); // Copio i dati precedenti

    free(a->Array[index]);                                                                                   // Libero la memoria per il dato da eliminare
    memcpy(&new->Array[index], &a->Array[index + 1], sizeof(oggetto **) * (a->NumeroOggetti - (index + 1))); // Copio il resto dell'array

    // Scambio gli array
    oggetto **temp = a->Array;
    a->Array       = new->Array;
    new->Array     = temp;

    freeArrayPuntatoriOggetto(new, false); // Libero la memoria temporanea
    return true;
}
#include "arrayPuntatoriOggetto.h"

struct ArrayPuntatoriOggetto {
    oggetto **Array;
    unsigned int NumeroOggetti;
};

// Aggiunge un puntatore a oggetto ad un array di puntatori a oggetti
void aggiungiOggettoArrayPuntatori(arrayPuntatoriOggetto a, oggetto *o) {
    if (a->NumeroOggetti == 0) { // Se non ho oggetti
        freeArrayPuntatoriOggetto(a, false);
        a           = allocaArrayPuntatoriOggetto(1);
        a->Array[0] = o;
        return;
    }

    // Creo nuovo array oggetti
    arrayPuntatoriOggetto new = allocaArrayPuntatoriOggetto(a->NumeroOggetti + 1);
    memcpy(new->Array, a->Array, sizeof(oggetto *) * a->NumeroOggetti);

    // Inserisco il nuovo oggetto
    new->Array[a->NumeroOggetti] = o;

    // Sostituisco l'array di oggetti
    a->Array = new->Array;
    freeArrayPuntatoriOggetto(new, false);
}

// Alloca un array di puntatori a oggetto di lunghezza "items"
arrayPuntatoriOggetto allocaArrayPuntatoriOggetto(unsigned int items) {
    arrayPuntatoriOggetto a = creaArrayPuntatoriOggetto();
    a->NumeroOggetti        = items;
    a->Array                = (oggetto **)calloc(items, sizeof(oggetto *));
    return a;
}

// Copia gli oggetti di src in dest
void copiaArrayPuntatoriOggetto(arrayPuntatoriOggetto dest, arrayPuntatoriOggetto src) {
    unsigned int min = dest->NumeroOggetti < src->NumeroOggetti ? dest->NumeroOggetti : src->NumeroOggetti;
    for (unsigned int i = 0; i < min; i++) { // Per il numero minimo di oggetti
        copiaOggetto(*dest->Array[i], *src->Array[i]);
    }
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
        printf("\n");
    }
}
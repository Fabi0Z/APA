#include "array.h"

// Alloca un array
void allocateArray(array a, unsigned int ObjectsNumber) {
    a->ObjectsNumber = ObjectsNumber;
    a->Objects       = (item *)calloc(a->ObjectsNumber, sizeof(item));
}

// Copia SRC in DEST
void copyArray(array DEST, array SRC) {
    DEST->ObjectsNumber = SRC->ObjectsNumber;
    DEST->freeObject    = SRC->freeObject;
    DEST->parseObject   = SRC->parseObject;
    DEST->printObject   = SRC->printObject;

    for (unsigned int i = 0; i < SRC->ObjectsNumber; i++) {
        DEST->Objects[i] = SRC->Objects[i];
    }
}

// Restituisce il numero di elementi validi all'interno di un array secondo una funzione di validità
unsigned int countValidItemsArray(array a, bool (*valid)(item i, item args), item args) {
    unsigned int items = 0;
    for (unsigned int i = 0; i < a->ObjectsNumber; i++) {
        if ((*valid)(a->Objects[i], args)) {
            items++;
        }
    }
    return items;
}

// Restituisce una copia dell'array SRC
array cloneArray(array SRC) {
    array DEST = newArray(NULL, NULL, NULL);
    allocateArray(DEST, SRC->ObjectsNumber);
    copyArray(DEST, SRC);
    return DEST;
}

// Crea un array con solo gli elementi validi secondo una funzione di validità, se nessuno è valido restituisce NULL
array validItemsArray(array a, bool (*valid)(item i, item args), item args) {
    unsigned int items = countValidItemsArray(a, valid, args);
    if (items == 0) {
        return NULL;
    }

    array valids = newArray(a->freeObject, a->parseObject, a->printObject);
    allocateArray(valids, items); // Alloco l'array

    unsigned int validsIndex = 0;
    for (unsigned int i = 0; i < a->ObjectsNumber; i++) {
        if ((*valid)(a->Objects[i], args)) {
            valids->Objects[validsIndex++] = a->Objects[i];
        }
    }

    return valids;
}

/* Restituisce il massimo o il minimo dell'array secondo una funzione di comparazione
   compare(item a, item b) = restituisce true se a è "migliore" di b secondo la comparazione */
item getMinOrMax(array a, bool (*compare)(item a, item b)) {
    item extreme = a->Objects[0];
    for (unsigned int i = 0; i < a->ObjectsNumber; i++) {
        extreme = (*compare)(a->Objects[i], extreme) ? a->Objects[i] : extreme;
    }
    return extreme;
}

// Cerca un item i nell'array e lo sposta nella posizione indicata scambiandolo con quello già presente
void moveItemArray(array a, item i, unsigned int posizione) {
    unsigned int posizioneI = (unsigned int)-1;
    for (unsigned int j = 0; j < a->ObjectsNumber; j++) {
        if (a->Objects[j] == i) { // Se sono uguali
            posizioneI = j;
            break;
        }
    }

    if (posizioneI == (unsigned int)-1) { // Se non ho trovato l'indice mi interrompo
        return;
    }

    // Effettuo lo scambio
    item tmp               = a->Objects[posizione];
    a->Objects[posizione]  = a->Objects[posizioneI];
    a->Objects[posizioneI] = tmp;
}

/* Crea un array
   freeObject = funzione per eliminare il singolo oggetto
   printObject = funzione che si occupa di effettuare il parse del singolo oggetto da stringa
   parseObject = funzione che stampa il singolo oggetto */
array newArray(void (*freeObject)(item), item (*parseObject)(char *), void (*printObject)(item)) {
    array a        = (array)malloc(sizeof(struct Array));
    a->freeObject  = freeObject;
    a->printObject = printObject;
    a->parseObject = parseObject;
    return a;
}

/* Elimina un array
   Se il valore freeObjects è true elimina anche i dati memorizzati */
void freeArray(array a, bool freeObjects) {
    if (a == NULL) {
        return;
    }
    if (a->Objects != NULL) { // Se l'array è allocato
        if (freeObjects) {
            for (unsigned int i = 0; i < a->ObjectsNumber; i++) { // Per ogni elemento
                a->freeObject(a->Objects[i]);
            }
        }
        free(a->Objects);
    }
    free(a);
}

// Effettua il parse da file di una serie di Objects
void parseArrayFromFile(array a, char *filename, unsigned int max_string) {
    FILE *stream = smartFopen(filename, "r"); // Apro il filestream

    fscanf(stream, "%u\n", &a->ObjectsNumber); // Leggo il numero di attività
    allocateArray(a, a->ObjectsNumber);        // Alloco la memoria

    char string[max_string + 1];
    for (unsigned int i = 0; i < a->ObjectsNumber; i++) { // Per ogni elemento
        fgets(string, max_string, stream);
        a->Objects[i] = a->parseObject(string);
    }
    fclose(stream);
}

// Stampa un array
void printArray(array a) {
    if (a == NULL) {
        return;
    }

    for (unsigned int i = 0; i < a->ObjectsNumber; i++) { // Per ogni elemento
        a->printObject(a->Objects[i]);
    }
    printf("\n");
}
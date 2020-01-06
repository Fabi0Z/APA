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

// Restituisce una copia dell'array SRC
array cloneArray(array SRC) {
    array DEST = newArray(NULL, NULL, NULL);
    allocateArray(DEST, SRC->ObjectsNumber);
    copyArray(DEST, SRC);
    return DEST;
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
    allocateArray(a, a->ObjectsNumber);          // Alloco la memoria

    char string[max_string + 1];
    for (unsigned int i = 0; i < a->ObjectsNumber; i++) { // Per ogni elemento
        fgets(string, max_string, stream);
        a->Objects[i] = a->parseObject(string);
    }
    fclose(stream);
}

// Stampa un array
void printArray(array a) {
    for (unsigned int i = 0; i < a->ObjectsNumber; i++) { // Per ogni elemento
        a->printObject(a->Objects[i]);
    }
    printf("\n");
}
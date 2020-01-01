#include "array.h"

// Alloca un array
void allocaArray(array a, unsigned int ObjectsNumber) {
    a->ObjectsNumber = ObjectsNumber;
    a->Objects       = (Item *)calloc(a->ObjectsNumber, sizeof(Item));
}

// Copia SRC in DEST
void copiaArray(array DEST, array SRC) {
    DEST->ObjectsNumber = SRC->ObjectsNumber;
    DEST->freeObject    = SRC->freeObject;
    DEST->parseObject   = SRC->parseObject;
    DEST->printObject   = SRC->printObject;

    for (unsigned int i = 0; i < SRC->ObjectsNumber; i++) {
        DEST->Objects[i] = SRC->Objects[i];
    }
}

/* Crea un array
   freeObject = funzione per eliminare il singolo oggetto
   printObject = funzione che si occupa di effettuare il parse del singolo oggetto da stringa
   parseObject = funzione che stampa il singolo oggetto */
array creaArray(void (*freeObject)(Item), Item (*parseObject)(char *), void (*printObject)(Item)) {
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
    allocaArray(a, a->ObjectsNumber);          // Alloco la memoria

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
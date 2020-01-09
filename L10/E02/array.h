#ifndef ARRAY_H
#define ARRAY_H

#include "smartlib.h"

// Array generico
typedef struct Array *array;
struct Array {
    item *Objects;
    unsigned int ObjectsNumber;
    // Funzione per eliminare il singolo oggetto
    void (*freeObject)(item);
    // Funzione che si occupa di effettuare il parse del singolo oggetto da stringa
    item (*parseObject)(char *);
    // Funzione che stampa il singolo oggetto
    void (*printObject)(item);
};

void printArray(array a);
void parseArrayFromFile(array a, char *filename, unsigned int max_string);
void freeArray(array a, bool freeObjects);
void moveItemArray(array a, item i, unsigned int posizione);
item getMinOrMax(array a, bool (*compare)(item a, item b));
array newArray(void (*freeObject)(item), item (*parseObject)(char *), void (*printObject)(item));
array cloneArray(array SRC);
void copyArray(array DEST, array SRC);
void allocateArray(array a, unsigned int ObjectsNumber);

#endif // ARRAY_H

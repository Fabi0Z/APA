#ifndef ARRAY_H
#define ARRAY_H

#include "smartlib.h"

// Array generico
typedef struct Array *array;
struct Array {
    Item *Objects;
    unsigned int ObjectsNumber;
    // Funzione per eliminare il singolo oggetto
    void (*freeObject)(Item);
    // Funzione che si occupa di effettuare il parse del singolo oggetto da stringa
    Item (*parseObject)(char *);
    // Funzione che stampa il singolo oggetto
    void (*printObject)(Item);
};

void printArray(array a);
void parseArrayFromFile(array a, char *filename, unsigned int max_string);
void freeArray(array a, bool freeObjects);
array creaArray(void (*freeObject)(Item), Item (*parseObject)(char *), void (*printObject)(Item));
void copiaArray(array DEST, array SRC);
void allocaArray(array a, unsigned int ObjectsNumber);

#endif // ARRAY_H

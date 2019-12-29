#ifndef SMARTLIB_H
#define SMARTLIB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Array generico
typedef struct Array *array;
struct Array {
    void **Objects;
    unsigned int ObjectsNumber;
    // Funzione per eliminare il singolo oggetto
    void (*freeObject)(void *);
    // Funzione che si occupa di effettuare il parse del singolo oggetto da stringa
    void *(*parseObject)(char *);
    // Funzione che stampa il singolo oggetto
    void (*printObject)(void *);
};

void printArray(array a);
void premiPerContinuare();
FILE *smartFopen(char *filename, char *mode);
void parseArrayFromFile(array a, char *filename, unsigned int max_string);
void freeArray(array a);
bool checkFilestream(FILE *stream);
array creaArray(void (*freeObject)(void *), void *(*parseObject)(char *), void (*printObject)(void *));
void allocaArray(array a, unsigned int NumeroElementi);

#endif // SMARTLIB_H

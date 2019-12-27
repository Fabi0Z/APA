#ifndef SMARTFUNCTIONS_H
#define SMARTFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Array generico
typedef struct Array {
    void **Elementi;
    unsigned int NumeroElementi;
} * array;

void premiPerContinuare();
FILE *smartFopen(char *filename, char *mode);
void printArray(array a, void(*printObject(void *)));
array parseFromFile(char *filename, unsigned int max_string, void *(*parseObject)(char *));
void freeArray(array a, void (*freeItem)(void *));
bool checkFilestream(FILE *stream);
array creaArray();
void allocaArray(array a, unsigned int NumeroElementi);

#endif // SMARTFUNCTIONS_H

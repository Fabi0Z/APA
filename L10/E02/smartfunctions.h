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
array parseFromFile(char *filename, unsigned int max_string, void *(*parseObject)(char *), unsigned int sizeOf);
void freeArray(array a);
bool checkFilestream(FILE *stream);
array creaArray();
void allocaArray(array a, unsigned int NumeroElementi, unsigned int sizeOf);

#endif // SMARTFUNCTIONS_H

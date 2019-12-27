#ifndef SMARTFUNCTIONS_H
#define SMARTFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Array generico
typedef struct Array *array;
struct Array {
    void **Elementi;
    unsigned int NumeroElementi;
    void (*freeArray)(void *, void (*freeItem)(void *));
    void (*printArray)(array, void(*printObject(void *)));
};

void premiPerContinuare();
array parseFromFile(char *filename, unsigned int max_string, void *(*parseObject)(char *));
FILE *smartFopen(char *filename, char *mode);
bool checkFilestream(FILE *stream);
array creaArray();
void allocaArray(array a, unsigned int NumeroElementi);

#endif // SMARTFUNCTIONS_H

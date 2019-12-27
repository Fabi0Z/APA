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
    /* Elimina un array ed il suo contenuto
    freeItem è la funzione per eliminare il singolo elemento */
    void (*free)(array, void (*freeItem)(void *));
    /* Effettua il parse da file di una serie di elementi
   parseObject è la funzione che si occupa di effettuare il parse del singolo oggetto da string */
    void (*parse)(array, char *filename, unsigned int max_string, void *(*parseObject)(char *));
    /* Stampa un array
   printObject è la funzione che stampa il singolo oggetto */
    void (*print)(array, void(*printObject(void *)));
};

void premiPerContinuare();
FILE *smartFopen(char *filename, char *mode);
bool checkFilestream(FILE *stream);
array creaArray();
void allocaArray(array a, unsigned int NumeroElementi);

#endif // SMARTFUNCTIONS_H

#include "arrayElemento.h"

static const uint8_t MAX_STRING = 150;

// Alloca un array di elementi
void allocaArrayElemento(arrayElemento a, unsigned int NumeroElementi) {
    a->NumeroElementi = NumeroElementi;
    a->Array          = (elemento *)calloc(a->NumeroElementi, sizeof(elemento));
}

// Crea un array di elementi
arrayElemento creaArrayElemento() {
    return (arrayElemento)malloc(sizeof(struct ArrayElemento));
}

// Elimina un array ed il suo contenuto
void freeArrayElemento(arrayElemento a) {
    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni elemento
        freeElemento(a->Array[i]);
    }
    free(a);
}

// Effettua il parse da file di una serie di elementi
arrayElemento parseElementoFromFile(char *filename) {
    FILE *stream = smartFopen(filename, "r"); // Apro il filestream

    arrayElemento a = creaArrayElemento();
    fscanf(stream, "%u\n", &a->NumeroElementi); // Leggo il numero di attività
    allocaArrayElemento(a, a->NumeroElementi);  // Alloco la memoria

    char string[MAX_STRING];
    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni elemento
        fgets(string, MAX_STRING, stream);
        a->Array[i] = parseElemento(string);
    }
    fclose(stream);
    return a;
}
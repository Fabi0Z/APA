#include "arrayCollane.h"

const unsigned int MAX_STRING = 50;

// Crea e restituisce un array di collane
arrayCollane creaArrayCollane(unsigned int NumeroElementi) {
    arrayCollane a    = (arrayCollane)malloc(sizeof(struct ArrayCollane));
    a->Array          = (collana *)calloc(NumeroElementi, sizeof(collana));
    a->NumeroElementi = NumeroElementi;
    return a;
}

// Legge un array di collane
arrayCollane parseArrayCollane(FILE *stream) {
    unsigned int nTest;
    fscanf(stream, "%u\n", &nTest);
    arrayCollane a = creaArrayCollane(nTest);

    for (unsigned int i = 0; i < nTest; i++) { // Per ogni test
        char riga[MAX_STRING + 1];
        fgets(riga, MAX_STRING, stream);
        a->Array[i] = parseCollana(riga);
    }

    fclose(stream);
    return a;
}

// Stampa un array di collane
void printArrayCollane(arrayCollane a) {
    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni elemento
        printf("TEST #%u\n", i);
        printCollana(a->Array[i]);
        printf("\n");
    }
}
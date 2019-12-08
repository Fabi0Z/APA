#include "tessera.h"

// Effettua il parse di un tubo da stringa
tubo parseTubo(char *string) {
    tubo t;
    sscanf(string, "%c %d %[^\n]", &t.Colore, &t.Valore, string);
    return t;
}

// Effettua il parse di una tessera da stringa
tessera parseTessera(char *string) {
    tessera t;
    t.Tubo1 = parseTubo(string);
    t.Tubo2 = parseTubo(string);
    return t;
}

// Effettua il parse di un array di tessere da file
arrayTessera parseArrayTessera(FILE *stream, unsigned int numeroTessere) {
    arrayTessera a;
    a.NumeroElementi = numeroTessere;
    a.Array          = (tessera *)calloc(a.NumeroElementi, sizeof(tessera));

    char string[11];
    for (size_t i = 0; i < a.NumeroElementi; i++) {
        fgets(string, 10, stream);
        a.Array[i] = parseTessera(string);
    }

    return a;
}

// Stampa un tubo su file
void printTubo(tubo *t, FILE *stream) {
    fprintf(stream, "%c %" SCNd8, t->Colore, t->Valore);
}

// Stampa un tessera su file
void printTessera(tessera *t, FILE *stream) {
    fprintf(stream, "Tubo 1: ");
    printTubo(&t->Tubo1, stream);
    fprintf(stream, "\nTubo 2: ");
    printTubo(&t->Tubo2, stream);
}

// Stampa un array di tessere su file
void printArrayTessera(arrayTessera *a, FILE *stream) {
    for (unsigned int i = 0; i < a->NumeroElementi; i++) {
        fprintf(stream, "Tessera N# %d\n", i);
        printTessera(&a->Array[i], stream);
        fprintf(stream, "\n");
    }
}
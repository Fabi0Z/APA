#include "tessera.h"

// Effettua il parse di un tubo da stringa
void parseTubo(tubo *t, char *string) {
    sscanf(string, "%c %d %[^\n]", &t->Colore, &t->Valore, string);
}

// Effettua il parse di una tessera da stringa
void parseTessera(tessera *t, char *string) {
    parseTubo(&t->Tubo1, string);
    parseTubo(&t->Tubo2, string);
}

// Crea e alloca un oggetto di tipo tessera
tessera *creaTessera() {
    tessera *t = (tessera *)malloc(sizeof(tessera));
    return t;
}

// Effettua il parse di un array di tessere da file
arrayTessera parseArrayTessera(FILE *stream, unsigned int numeroTessere) {
    arrayTessera a;
    a.NumeroElementi = numeroTessere;
    a.Array          = (tessera **)calloc(a.NumeroElementi, sizeof(tessera *));

    char string[11];
    for (size_t i = 0; i < a.NumeroElementi; i++) {
        fgets(string, 10, stream);
        a.Array[i] = creaTessera();
        parseTessera(a.Array[i], string);
    }

    return a;
}

// Stampa un tubo su file
void printTubo(tubo *t, FILE *stream) {
    fprintf(stream, "%c %" SCNd8, t->Colore, t->Valore);
}

// Stampa un tessera su file
void printTessera(tessera *t, FILE *stream) {
    fprintf(stream, "- Tubo 1: ");
    printTubo(&t->Tubo1, stream);
    fprintf(stream, "\n- Tubo 2: ");
    printTubo(&t->Tubo2, stream);
}

// Stampa un array di tessere su file
void printArrayTessera(arrayTessera *a, FILE *stream) {
    for (unsigned int i = 0; i < a->NumeroElementi; i++) {
        fprintf(stream, "Tessera #%d\n", i);
        printTessera(a->Array[i], stream);
        fprintf(stream, "\n");
    }
}
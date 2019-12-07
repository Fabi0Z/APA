#include "inventario.h"

// Stampa un inventario su file
void printInventarioFile(inventario *inv, FILE *stream, bool indici) {
    if (stream != stdout) { // Se non sono sullo stdout
        fprintf(stream, "%" SCNd8 "\n", inv->NumeroOggetti);
    }

    for (size_t i = 0; i < inv->NumeroOggetti; i++) { // Per ogni oggetto
        if (indici) {
            fprintf(stream, "%zu - ", i);
        }
        printOggetto(&inv->Oggetti[i], stream);
    }

    printf("\n");
}

// Stampa un inventario a video
void printInventario(inventario *i, bool indici) {
    puts("L'inventario è composto da:");
    printInventarioFile(i, stdout, indici);
}

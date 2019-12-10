#include "inventario.h"

const uint8_t INVENTARIO_MAX_STRING = 50;

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

// Effettua il parse dell'inventario
inventario parseInventario(FILE *stream) {
    inventario inv;
    fscanf(stream, "%" SCNd8 "\n", &inv.NumeroOggetti);
    inv.Oggetti = (oggetto *)calloc(inv.NumeroOggetti, sizeof(oggetto));
    char string[(INVENTARIO_MAX_STRING * 3) + 1];
    oggetto *temp = creaOggetto(INVENTARIO_MAX_STRING, INVENTARIO_MAX_STRING);

    for (size_t i = 0; i < inv.NumeroOggetti; i++) { // Per ogni oggetto nel file
        fgets(string, INVENTARIO_MAX_STRING * 2, stream);       // Leggo la riga successiva
        leggiOggetto(string, temp);
        allocaOggetto(&inv.Oggetti[i], strlen(temp->Nome), strlen(temp->Tipo)); // Alloco la memoria necessaria
        copiaOggetto(&inv.Oggetti[i], temp);
    }
    freeOggetto(temp);

    return inv;
}
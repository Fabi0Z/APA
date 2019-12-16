#include "inventario.h"

struct Inventario {
    arrayOggetti Oggetti;
    uint8_t OggettiTrasportabili;
};

const uint8_t INVENTARIO_MAX_STRING = 50;

// Crea e restituisce un inventario
inventario creaInventario() {
    inventario i            = (inventario)malloc(sizeof(struct Inventario));
    i->OggettiTrasportabili = 0;
    i->Oggetti              = NULL;
    return i;
}

// Stampa un inventario su file
void printInventarioFile(inventario inv, FILE *stream, bool indici) {
    if (stream != stdout) { // Se non sono sullo stdout
        fprintf(stream, "%" SCNd8 "\n", inv->NumeroOggetti);
    }
    printArrayOggetti(inv->Oggetti, stream, indici);
}

// Stampa un inventario a video
void printInventario(inventario i, bool indici) {
    puts("L'inventario è composto da:");
    printInventarioFile(i, stdout, indici);
}

// Effettua il parse dell'inventario
inventario parseInventario(FILE *stream) {
    inventario inv = creaInventario();
    unsigned int oggetti;
    fscanf(stream, "%d\n", &oggetti);
    char string[(INVENTARIO_MAX_STRING * 3) + 1];
    oggetto temp = creaOggetto(INVENTARIO_MAX_STRING, INVENTARIO_MAX_STRING);

    for (size_t i = 0; i < oggetti; i++) {                // Per ogni oggetto nel file
        fgets(string, INVENTARIO_MAX_STRING * 2, stream); // Leggo la riga successiva
        leggiOggetto(string, temp);
        allocaOggetto(inv->Oggetti[i], strlen(getNomeOggetto(temp)), strlen(getTipoOggetto(temp))); // Alloco la memoria necessaria
        copiaOggetto(inv->Oggetti[i], temp);
    }
    freeOggetto(temp);

    return inv;
}

// Cerca un oggetto per nome nell'inventario, se non lo trova restituisce NULL
oggetto getOggettoInventarioByName(inventario inv, char *nome) {
    for (unsigned int i = 0; i < inv->NumeroOggetti; i++) {       // Per ogni oggetto
        if (strcmp(nome, getNomeOggetto(inv->Oggetti[i])) == 0) { // Se il nome corrisponde
            return inv->Oggetti[i];
        }
    }
    return NULL;
}

// Restituisce l'oggetto di indice "index" nell'inventario
oggetto getOggettoInventarioByIndex(inventario inv, uint8_t index) {
    return inv->Oggetti[index];
}

// Restituisce il numero di oggetti trasportabili di un inventario
uint8_t getOggettiTrasportabiliInventario(inventario i) {
    return i->OggettiTrasportabili;
}

// Restituisce il numero di oggetti presenti in un inventario
uint8_t getNumeroOggettiInventario(inventario i) {
    return i->NumeroOggetti;
}

// Aggiorna il numero di oggetti trasportabili di un inventario
void updateOggettiTrasportabiliInventario(inventario i, uint8_t OggettiTrasportabili) {
    i->OggettiTrasportabili = OggettiTrasportabili;
}
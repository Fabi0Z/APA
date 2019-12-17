#include "inventario.h"

struct Inventario {
    arrayOggetti Oggetti;
    uint8_t OggettiTrasportabili;
};

const uint8_t INVENTARIO_MAX_STRING = 50;

// Crea e restituisce un inventario
inventario creaInventario(uint8_t oggettiTrasportabili) {
    inventario i            = (inventario)malloc(sizeof(struct Inventario));
    i->OggettiTrasportabili = oggettiTrasportabili;
    i->Oggetti              = creaArrayOggetti();
    return i;
}

// Cerca un oggetto per nome nell'inventario, se non lo trova restituisce NULL
void *getOggettoInventarioByName(inventario inv, char *nome, bool pointer) {
    return getOggettoByName(inv->Oggetti, nome, pointer);
}

// Restituisce l'oggetto di indice "index" nell'inventario
void *getOggettoInventarioByIndex(inventario inv, uint8_t index, bool pointer) {
    return getOggettoByIndex(inv->Oggetti, index, pointer);
}

// Restituisce il numero di oggetti trasportabili di un inventario
uint8_t getOggettiTrasportabiliInventario(inventario i) {
    return i->OggettiTrasportabili;
}

// Restituisce il numero di oggetti presenti in un inventario
unsigned int getNumeroOggettiInventario(inventario i) {
    return getNumeroOggetti(i->Oggetti);
}

// Effettua il parse dell'inventario
inventario parseInventario(FILE *stream, uint8_t oggettiTrasportabili) {
    inventario inv = creaInventario(oggettiTrasportabili);
    unsigned int oggetti;
    fscanf(stream, "%u\n", &oggetti);
    char string[(INVENTARIO_MAX_STRING * 3) + 1];
    oggetto temp = creaOggetto(INVENTARIO_MAX_STRING, INVENTARIO_MAX_STRING);

    for (size_t i = 0; i < oggetti; i++) {                // Per ogni oggetto nel file
        fgets(string, INVENTARIO_MAX_STRING * 2, stream); // Leggo la riga successiva
        leggiOggetto(string, temp);
        oggetto resized = creaOggetto(strlen(getNomeOggetto(temp)), strlen(getTipoOggetto(temp)));
        copiaOggetto(resized, temp);
        aggiungiOggettoArray(inv->Oggetti, resized);
    }
    freeOggetto(temp);
    return inv;
}

// Stampa un inventario su file
void printInventarioFile(inventario inv, FILE *stream, bool indici) {
    if (stream != stdout) { // Se non sono sullo stdout
        fprintf(stream, "%u\n", getNumeroOggettiInventario(inv));
    }
    printArrayOggetti(inv->Oggetti, stream, indici);
}

// Stampa un inventario a video
void printInventario(inventario i, bool indici) {
    puts("L'inventario è composto da:");
    printInventarioFile(i, stdout, indici);
}

// Aggiorna il numero di oggetti trasportabili di un inventario
void updateOggettiTrasportabiliInventario(inventario i, uint8_t OggettiTrasportabili) {
    i->OggettiTrasportabili = OggettiTrasportabili;
}
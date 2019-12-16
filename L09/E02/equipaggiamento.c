#include "equipaggiamento.h"

struct Equipaggiamento {
    bool InUso;
    arrayPuntatoriOggetto Oggetti;
};

void aggiungiOggettoEquipaggiamento(equipaggiamento e, oggetto o) {
    aggiungiOggettoArrayPuntatori(e->Oggetti, &o);
}

// Crea un equipaggiamento
equipaggiamento creaEquipaggiamento() {
    equipaggiamento e = (equipaggiamento)malloc(sizeof(struct Equipaggiamento));
    e->Oggetti        = NULL;
    return e;
}

// Dealloca un equipaggiamento
void freeEquipaggiamento(equipaggiamento e) {
    freeArrayPuntatoriOggetto(e->Oggetti, false);
}

// Restituisce il numero di oggetti di un equipaggiamento
unsigned int getNumeroOggettiEquipaggiamento(equipaggiamento e) {
    return getNumeroPuntatori(e->Oggetti);
}

// Restituisce l'oggetto di indice "index" nell'equipaggiamento
oggetto *getOggettoEquipaggiamentoByIndex(equipaggiamento e, uint8_t index) {
    return getPuntatoreOggettoByIndex(e->Oggetti, index);
}

// Cerca un oggetto per nome nell'array di oggetti, se non lo trova restituisce NULL
oggetto *getOggettoEquipaggiamentoByName(equipaggiamento e, char *name) {
    return getPuntatoreOggettoByName(e->Oggetti, name);
}

// Stampa un equipaggiamento a video
void printEquipaggiamento(equipaggiamento e, bool indici) {
    puts("L'equipaggiamento è composto da:");
    printEquipaggiamentoFile(e, stdout, indici);
}

// Stampa un equipaggiamento su file
void printEquipaggiamentoFile(equipaggiamento e, FILE *stream, bool indici) {
    printArrayPuntatoriOggetto(e->Oggetti, stream, indici);
}
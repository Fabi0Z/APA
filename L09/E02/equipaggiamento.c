#include "equipaggiamento.h"

struct Equipaggiamento {
    bool InUso;
    arrayPuntatoriOggetti Oggetti;
    uint8_t NumeroOggetti;
};

// Crea un equipaggiamento
equipaggiamento creaEquipaggiamento() {
    equipaggiamento e = (equipaggiamento)malloc(sizeof(struct Equipaggiamento));
    e->Oggetti        = NULL;
    e->NumeroOggetti  = 0;
    return e;
}

// Stampa un equipaggiamento su file
void printEquipaggiamentoFile(equipaggiamento e, FILE *stream, bool indici) {
    printArrayPuntatoriOggetti(e->Oggetti, stream, indici);
}

// Stampa un equipaggiamento a video
void printEquipaggiamento(equipaggiamento e, bool indici) {
    puts("L'equipaggiamento è composto da:");
    printEquipaggiamentoFile(e, stdout, indici);
}

// Restituisce il numero di oggetti di un equipaggiamento
unsigned int getNumeroOggettiEquipaggiamento(equipaggiamento e) {
    return getNumeroPuntatori(e->Oggetti);
}

// Dealloca un equipaggiamento
void freeEquipaggiamento(equipaggiamento e) {
    freeArrayPuntatoriOggetti(e->Oggetti, false);
}

// Restituisce l'oggetto di indice "index" nell'equipaggiamento
oggetto getOggettoEquipaggiamentoByIndex(equipaggiamento e, uint8_t index) {
    return getOggettoByIndex(e->Oggetti, index);
}

oggetto *getOggettoEquipaggiamentoByName(equipaggiamento e, char *name) {
    return getPuntatoreOggettoByName(e->Oggetti, name);
}

bool aggiungiOggettoEquipaggiamento(equipaggiamento e, oggetto o) {
    aggiungiOggettoArrayPuntatori(e->Oggetti, o);
}
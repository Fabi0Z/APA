#include "equipaggiamento.h"

struct Equipaggiamento {
    bool InUso;
    arrayPuntatoriOggetto Oggetti;
};

void aggiungiOggettoEquipaggiamento(equipaggiamento e, oggetto o) {
    if (e->Oggetti == NULL) {
        e->Oggetti = creaArrayPuntatoriOggetto();
    }

    aggiungiOggettoArrayPuntatori(e->Oggetti, &o);
}

// Copia SRC in DEST
void copiaEquipaggiamento(equipaggiamento dest, equipaggiamento src) {
    dest->InUso = src->InUso;
    if (src->Oggetti != NULL) {
        copiaArrayPuntatoriOggetto(dest->Oggetti, src->Oggetti);
    }
}

// Crea un equipaggiamento
equipaggiamento creaEquipaggiamento() {
    equipaggiamento e = (equipaggiamento)malloc(sizeof(struct Equipaggiamento));
    e->Oggetti        = NULL;
    return e;
}

// Dealloca un equipaggiamento
void freeEquipaggiamento(equipaggiamento e) {
    if (e->Oggetti != NULL) {
        freeArrayPuntatoriOggetto(e->Oggetti, false);
    }
    free(e);
}

// Restituisce il numero di oggetti di un equipaggiamento
unsigned int getNumeroOggettiEquipaggiamento(equipaggiamento e) {
    if (e->Oggetti == NULL) {
        return 0;
    }
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
    if (e->Oggetti == NULL) {
        puts("Equipaggiamento vuoto\n");
        return;
    }

    printArrayPuntatoriOggetto(e->Oggetti, stream, indici);
}

// Rimuove un oggetto da un equipaggiamento, restituisce false se non rimangono oggetti nell'equipaggiamento
bool rimuoviOggettoEquipaggiamento(equipaggiamento e, oggetto o) {
    if (!rimuoviPuntatoreOggetto(e->Oggetti, o)) { // Se viene eliminato l'array
        e->Oggetti = NULL;
        return false;
    }
    return true;
}
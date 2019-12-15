#include "equipaggiamento.h"

struct Equipaggiamento {
    bool InUso;
    oggetto **Oggetti;
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
    for (size_t i = 0; i < e->NumeroOggetti; i++) { // Per ogni oggetto
        if (indici) {
            fprintf(stream, "%zu - ", i);
        }
        printOggetto(*e->Oggetti[i], stream);
    }
    printf("\n");
}

// Stampa un equipaggiamento a video
void printEquipaggiamento(equipaggiamento e, bool indici) {
    puts("L'equipaggiamento è composto da:");
    printEquipaggiamentoFile(e, stdout, indici);
}

// Copia src in dest
void copiaEquipaggiamento(equipaggiamento dest, equipaggiamento src) {
    // Se vi sono oggetti
    if (src->NumeroOggetti == 0) {
        dest->NumeroOggetti = 0;
        if (dest->Oggetti != NULL) {
            free(dest->Oggetti);
            dest->Oggetti = NULL;
        }
        return;
    }
    dest->NumeroOggetti = src->NumeroOggetti;
    memcpy(dest->Oggetti, src->Oggetti, sizeof(oggetto **) * src->NumeroOggetti);
}

// Restituisce il numero di oggetti di un equipaggiamento
uint8_t getNumeroOggettiEquipaggiamento(equipaggiamento e) {
    return e->NumeroOggetti;
}

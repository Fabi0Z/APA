#include "adiacenza.h"

static bool __ADIACENZA_PESATA = 0;

// Imposta le adiacenze come pesate o meno
void adiacenzaPesata(bool set) {
    __ADIACENZA_PESATA = set;
}

// Restituisce true se si stanno utilizzando adiacenze pesate
bool adiacenzaPesataStatus() {
    return __ADIACENZA_PESATA;
}

// Elimina un'adiacenza
void freeAdiacenza(adiacenza a) {
    free(a->Destinazione);
    free(a);
}

// Restituisce il peso di un'adiacenza
unsigned int getPeso(adiacenza a) {
    if (__ADIACENZA_PESATA) { // Se si tratta di un'adiacenza pesata
        return a->Destinazione[1];
    }
    return 0;
}

// Crea una nuova adiacenza
adiacenza newAdiacenza(unsigned int Destinazione, unsigned int Peso) {
    adiacenza a     = malloc(sizeof(struct Adiacenza));
    a->Destinazione = calloc((int)__ADIACENZA_PESATA + 1, sizeof(unsigned int)); // Alloco in base a lista pesata o meno
}

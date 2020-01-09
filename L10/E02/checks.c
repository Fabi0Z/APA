#include "checks.h"

// Crea una variabile di tipo checks
checks newChecks() {
    checks c     = (checks)malloc(sizeof(struct Checks));
    c->Valori    = (bool *)calloc(checksTotale, sizeof(bool));
    c->Richiesti = (bool *)calloc(dueElementi + 1, sizeof(bool));

    // Scrivo false in tutti gli array
    for (unsigned int i = 0; i < dueElementi + 1; i++) {
        c->Valori[i]    = false;
        c->Richiesti[i] = false;
    }
    for (unsigned int i = dueElementi + 1; i < checksTotale; i++) {
        c->Valori[i] = false;
    }

    return c;
}

// Elimina una variabile checks
void freeChecks(checks c) {
    free(c->Valori);
    free(c->Richiesti);
    free(c);
}

// Controlla che tutti i valori dei checks siano corretti
bool verificaChecks(checks c) {
    bool result = true;
    for (unsigned int i = 0; i < dueElementi + 1; i++) {
        result = c->Richiesti[i] ? result && c->Valori[i] : result;
    }
    return result;
}
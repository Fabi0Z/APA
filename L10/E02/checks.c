#include "checks.h"

// Crea una variabile di tipo checks
checks newChecks() {
    checks c = (checks)calloc(checksTotale, sizeof(bool));
    for (unsigned int i = 0; i < checksTotale; i++) {
        c[i] = false;
    }
    return c;
}

// Controlla che tutti i checks siano corretti
bool verificaChecks(checks c) {
    bool result = true;
    for (unsigned int i = 0; i < checksTotale; i++) {
        result *= c[i];
    }
    return result;
}
#ifndef CHECKS_H
#define CHECKS_H

#include "stdbool.h"
#include "stdlib.h"
typedef struct Checks {
    bool *Valori;
    bool *Richiesti;
} * checks;
enum checksType { elementoAvanti,
                  elementoIndietro,
                  dueElementi,
                  primaDiagonale,
                  checksTotale };

bool verificaChecks(checks c);
void freeChecks(checks c);
checks newChecks();

#endif // CHECKS_H

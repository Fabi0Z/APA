#ifndef CHECKS_H
#define CHECKS_H

#include "stdbool.h"
#include "stdlib.h"
typedef bool *checks;
enum checksType { elementoAvanti,
                  elementoIndietro,
                  dueElementi,
                  ultimaDiagonale,
                  checksRichiesti,
                  checksTotale };

checks newChecks();

#endif // CHECKS_H

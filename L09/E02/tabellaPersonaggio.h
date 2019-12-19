#ifndef TABELLAPERSONAGGIO_H
#define TABELLAPERSONAGGIO_H

#include "listaPersonaggio.h"

typedef struct TabellaPersonaggio *tabellaPersonaggio;

personaggioLink ricercaID(tabellaPersonaggio t, uint16_t *ID);
void parsePersonaggi(tabellaPersonaggio TABLE, FILE *stream);
personaggioLink getTableTail(tabellaPersonaggio t);
unsigned int getTableNumeroPersonaggi(tabellaPersonaggio t);
personaggioLink getTableHead(tabellaPersonaggio t);
personaggioLink ricercaIDprecedente(tabellaPersonaggio t, uint16_t *ID);
bool eliminaPersonaggioByID(tabellaPersonaggio t, uint16_t *ID);
tabellaPersonaggio creaTabellaPersonaggio();

#endif // TABELLAPERSONAGGIO_H

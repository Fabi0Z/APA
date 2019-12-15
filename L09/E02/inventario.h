#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "oggetto.h"

typedef struct Inventario *inventario;

oggetto trovaOggetto(inventario inv, char *nome);
inventario parseInventario(FILE *stream);
void printInventario(inventario i, bool indici);
void printInventarioFile(inventario inv, FILE *stream, bool indici);
inventario creaInventario();
extern const uint8_t INVENTARIO_MAX_STRING;

#endif // INVENTARIO_H

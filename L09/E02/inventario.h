#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "oggetto.h"
typedef struct Inventario *inventario;

uint8_t getNumeroOggettiInventario(inventario i);
void updateOggettiTrasportabiliInventario(inventario i, uint8_t OggettiTrasportabili);
uint8_t getOggettiTrasportabiliInventario(inventario i);
oggetto getOggettoByName(inventario inv, char *nome);
oggetto getOggettoByIndex(inventario inv, uint8_t index);
inventario parseInventario(FILE *stream);
void printInventario(inventario i, bool indici);
void printInventarioFile(inventario inv, FILE *stream, bool indici);
inventario creaInventario();
extern const uint8_t INVENTARIO_MAX_STRING;

#endif // INVENTARIO_H

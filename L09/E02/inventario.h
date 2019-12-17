#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "arrayOggetti.h"
typedef struct Inventario *inventario;

void updateOggettiTrasportabiliInventario(inventario i, uint8_t OggettiTrasportabili);
void printInventario(inventario i, bool indici);
void printInventarioFile(inventario inv, FILE *stream, bool indici);
inventario parseInventario(FILE *stream, uint8_t oggettiTrasportabili);
uint8_t getNumeroOggettiInventario(inventario i);
uint8_t getOggettiTrasportabiliInventario(inventario i);
void *getOggettoInventarioByIndex(inventario inv, uint8_t index, bool pointer);
void *getOggettoInventarioByName(inventario inv, char *nome, bool pointer);
inventario creaInventario(uint8_t oggettiTrasportabili);
extern const uint8_t INVENTARIO_MAX_STRING;

#endif // INVENTARIO_H

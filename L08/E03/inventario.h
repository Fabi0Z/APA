#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "oggetto.h"

typedef struct Inventario {
    oggetto *Oggetti;
    uint8_t NumeroOggetti;
    uint8_t OggettiTrasportabili;
} inventario;

oggetto *trovaOggetto(inventario *inv, char *nome);
inventario parseInventario(FILE *stream);
void printInventario(inventario *i, bool indici);
void printInventarioFile(inventario *inv, FILE *stream, bool indici);
extern const uint8_t INVENTARIO_MAX_STRING;

#endif // INVENTARIO_H

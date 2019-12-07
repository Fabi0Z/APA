#if !defined(INVENTARIO_H)
#define INVENTARIO_H

#include "oggetto.h"

typedef struct Inventario {
    oggetto *Oggetti;
    uint8_t NumeroOggetti;
    uint8_t OggettiTrasportabili;
} inventario;

void printInventario(inventario *i, bool indici);
void printInventarioFile(inventario *inv, FILE *stream, bool indici);

#endif // INVENTARIO_H

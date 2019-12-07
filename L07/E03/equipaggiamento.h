#if !defined(EQUIPAGGIAMENTO_H)
#define EQUIPAGGIAMENTO_H

#include "oggetto.h"

typedef struct Equipaggiamento {
    bool InUso;
    oggetto **Oggetti;
    uint8_t NumeroOggetti;
} equipaggiamento;

void copiaEquipaggiamento(equipaggiamento *dest, equipaggiamento *src);
void printEquipaggiamento(equipaggiamento *e, bool indici);
void printEquipaggiamentoFile(equipaggiamento *e, FILE *stream, bool indici);

#endif // EQUIPAGGIAMENTO_H

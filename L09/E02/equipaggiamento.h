#ifndef EQUIPAGGIAMENTO_H
#define EQUIPAGGIAMENTO_H

#include "oggetto.h"
typedef struct Equipaggiamento *equipaggiamento;

uint8_t getNumeroOggettiEquipaggiamento(equipaggiamento e);
void copiaEquipaggiamento(equipaggiamento dest, equipaggiamento src);
void printEquipaggiamento(equipaggiamento e, bool indici);
void printEquipaggiamentoFile(equipaggiamento e, FILE *stream, bool indici);
equipaggiamento creaEquipaggiamento();

#endif // EQUIPAGGIAMENTO_H

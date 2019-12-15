#ifndef EQUIPAGGIAMENTO_H
#define EQUIPAGGIAMENTO_H

#include "oggetto.h"
typedef struct Equipaggiamento *equipaggiamento;

bool aggiungiOggettoEquipaggiamento(equipaggiamento e, oggetto o);
oggetto *getOggettoEquipaggiamentoByName(equipaggiamento e, char *name);
oggetto getOggettoEquipaggiamentoByIndex(equipaggiamento e, uint8_t index);
void freeEquipaggiamento(equipaggiamento e);
unsigned int getNumeroOggettiEquipaggiamento(equipaggiamento e);
void printEquipaggiamento(equipaggiamento e, bool indici);
void printEquipaggiamentoFile(equipaggiamento e, FILE *stream, bool indici);
equipaggiamento creaEquipaggiamento();

#endif // EQUIPAGGIAMENTO_H

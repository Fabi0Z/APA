#ifndef EQUIPAGGIAMENTO_H
#define EQUIPAGGIAMENTO_H

#include "arrayPuntatoriOggetto.h"
typedef struct Equipaggiamento *equipaggiamento;

void printEquipaggiamentoFile(equipaggiamento e, FILE *stream, bool indici);
void printEquipaggiamento(equipaggiamento e, bool indici);
oggetto *getOggettoEquipaggiamentoByName(equipaggiamento e, char *name);
oggetto *getOggettoEquipaggiamentoByIndex(equipaggiamento e, uint8_t index);
unsigned int getNumeroOggettiEquipaggiamento(equipaggiamento e);
void freeEquipaggiamento(equipaggiamento e);
equipaggiamento creaEquipaggiamento();
void aggiungiOggettoEquipaggiamento(equipaggiamento e, oggetto o);

#endif // EQUIPAGGIAMENTO_H

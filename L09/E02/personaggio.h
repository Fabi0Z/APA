#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H

#include "equipaggiamento.h"
#include "inventario.h"

typedef struct Personaggio {
    uint16_t ID;
    char *Nome;
    char *Classe;
    equipaggiamento Equipaggiamento;
    stats Statistiche;
} * personaggio;

bool rimuoviEquipaggiamento(personaggio p, oggetto o);
void printPersonaggio(personaggio p, FILE *stream);
bool leggiPersonaggio(char *string, personaggio p);
personaggio getResizedPersonaggio(personaggio temp);
void freePersonaggio(personaggio p);
personaggio creaPersonaggio(unsigned int nomeSize, unsigned int classeSize);
void copiaPersonaggio(personaggio dest, personaggio src);
void calcolaStatistiche(personaggio p, stats s);
void aggiungiEquipaggiamento(personaggio p, oggetto *o);
void allocaPersonaggio(personaggio p, unsigned int nomeSize, unsigned int classeSize);

#endif // PERSONAGGIO_H

#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H

#include "equipaggiamento.h"
#include "inventario.h"

typedef struct Personaggio {
    uint16_t ID;
    char *Nome;
    char *Classe;
    equipaggiamento *Equipaggiamento;
    stats Statistiche;
} personaggio;

typedef struct PersonaggioLink personaggioLink;
typedef struct PersonaggioLink {
    personaggio *Personaggio;
    personaggioLink *Next;
} personaggioLink;

typedef struct TabellaPersonaggio {
    personaggioLink *HEAD;
    personaggioLink *TAIL;
    unsigned int NumeroPersonaggi;
} tabellaPersonaggio;

void eliminaAndPrint(personaggioLink *previous);
personaggioLink *estraiNext(personaggioLink *previous);
personaggioLink *ricercaID(personaggioLink *HEAD, uint16_t *ID);
personaggioLink *ricercaIDprecedente(personaggioLink *HEAD, uint16_t *ID);
void addNext(personaggioLink *l, personaggioLink *next);
bool leggiPersonaggio(char *string, personaggio *p);
personaggio *getResizedPersonaggio(personaggio *temp);
void copiaPersonaggio(personaggio *dest, personaggio *src);
personaggioLink *creaPersonaggioLink(personaggio *p);
personaggio *creaPersonaggio(unsigned int nomeSize, unsigned int classeSize);
personaggioLink *creaLista(personaggio *p);
personaggioLink *getNextItem(personaggioLink *item);
void printPersonaggioLink(personaggioLink *l);
void printPersonaggioLinkFile(personaggioLink *l, FILE *stream);
void printPersonaggio(personaggio *p, FILE *stream);
void rimuoviEquipaggiamento(personaggio *p, uint8_t indiceOggetto);
bool aggiungiEquipaggiamento(personaggio *p, oggetto *o);
void calcolaStatistiche(personaggio *p, stats s);
void freePersonaggioLink(personaggioLink *l);
void freePersonaggio(personaggio *p);
void allocaPersonaggio(personaggio *p, unsigned int nomeSize, unsigned int classeSize);

#endif // PERSONAGGIO_H

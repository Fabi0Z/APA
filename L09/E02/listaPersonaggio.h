#ifndef LISTAPERSONAGGIO_H
#define LISTAPERSONAGGIO_H

#include "personaggio.h"

typedef struct PersonaggioLink *personaggioLink;
typedef struct TabellaPersonaggio *tabellaPersonaggio;

personaggioLink ricercaIDprecedente(personaggioLink HEAD, uint16_t *ID);
personaggioLink ricercaID(personaggioLink HEAD, uint16_t *ID);
void printPersonaggioLinkFile(personaggioLink l, FILE *stream);
void printPersonaggioLink(personaggioLink l);
void parsePersonaggi(tabellaPersonaggio *TABLE, FILE *stream);
personaggio getTableTail(tabellaPersonaggio t);
unsigned int getTableNumeroPersonaggi(tabellaPersonaggio t);
personaggio getTableHead(tabellaPersonaggio t);
personaggio getPersonaggio(personaggioLink l);
personaggioLink getNextItem(personaggioLink item);
void freePersonaggioLink(personaggioLink l);
personaggioLink estraiNext(personaggioLink previous);
void eliminaAndPrint(personaggioLink previous);
tabellaPersonaggio creaTabellaPersonaggio();
personaggioLink creaPersonaggioLink(personaggio p);
personaggioLink creaElementoLista(personaggio p);
void addNext(personaggioLink l, personaggioLink next);
extern const uint8_t PERSONAGGIO_MAX_STRING;

#endif // LISTAPERSONAGGIO_H

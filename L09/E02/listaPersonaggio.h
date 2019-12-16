#ifndef LISTAPERSONAGGIO_H
#define LISTAPERSONAGGIO_H

#include "personaggio.h"

typedef struct PersonaggioLink *personaggioLink;
typedef struct TabellaPersonaggio {
    personaggioLink HEAD;
    personaggioLink TAIL;
    unsigned int NumeroPersonaggi;
} tabellaPersonaggio;

void printPersonaggioLink(personaggioLink l);
void eliminaAndPrint(personaggioLink previous);
personaggioLink estraiNext(personaggioLink previous);
personaggioLink ricercaID(personaggioLink HEAD, uint16_t *ID);
personaggioLink ricercaIDprecedente(personaggioLink HEAD, uint16_t *ID);
void addNext(personaggioLink l, personaggioLink next);
personaggioLink creaPersonaggioLink(personaggio *p);
void parsePersonaggi(tabellaPersonaggio *TABLE, FILE *stream);
personaggioLink creaLista(personaggio *p);
personaggioLink getNextItem(personaggioLink item);
void printPersonaggioLinkFile(personaggioLink l, FILE *stream);
void freePersonaggioLink(personaggioLink l);
extern const uint8_t PERSONAGGIO_MAX_STRING;

#endif // LISTAPERSONAGGIO_H

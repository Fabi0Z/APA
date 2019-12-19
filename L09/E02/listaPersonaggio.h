#ifndef LISTAPERSONAGGIO_H
#define LISTAPERSONAGGIO_H

#include "personaggio.h"

typedef struct PersonaggioLink *personaggioLink;

personaggioLink ricercaIDprecedenteR(personaggioLink next, uint16_t *ID);
void printPersonaggioLinkFile(personaggioLink l, FILE *stream);
void printPersonaggioLink(personaggioLink l);
personaggio getPersonaggio(personaggioLink l);
personaggioLink getNextItem(personaggioLink item);
void freePersonaggioLink(personaggioLink l);
personaggioLink estraiNext(personaggioLink previous);
void eliminaAndPrint(personaggioLink previous);
personaggioLink creaPersonaggioLink(personaggio p);
void addNext(personaggioLink l, personaggioLink next);
extern const uint8_t PERSONAGGIO_MAX_STRING;

#endif // LISTAPERSONAGGIO_H

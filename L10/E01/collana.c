#include "collana.h"

// Allora e restituisce una collana
collana creaCollana() {
    return (collana)malloc(sizeof(struct Collana));
}

// Effettua il parse di una collana da stringa e svuota la stringa
collana parseCollana(char *string) {
    collana c = creaCollana();
    sscanf(string, "%u %[^\n]", &c->Pietre[zaffiro], string);
    sscanf(string, "%u %[^\n]", &c->Pietre[rubino], string);
    sscanf(string, "%u %[^\n]", &c->Pietre[topazio], string);
    sscanf(string, "%u", &c->Pietre[smeraldo]);

    c->Pietre[totale] = c->Pietre[zaffiro] + c->Pietre[smeraldo] + c->Pietre[rubino] + c->Pietre[topazio];

    return c;
}

// Stampa le informazioni di una collana
void printCollana(collana c) {
    printf("Zaffiri = %u, ", c->Pietre[zaffiro]);
    printf("Rubini = %u, ", c->Pietre[rubino]);
    printf("Topazi = %u, ", c->Pietre[topazio]);
    printf("Smeraldi = %u, ", c->Pietre[smeraldo]);
    printf("Totale = %u\n", c->Pietre[totale]);
    printf("Lunghezza massima: %u\n", c->LunghezzaMassima);
}


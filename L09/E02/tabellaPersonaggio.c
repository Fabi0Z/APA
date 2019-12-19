#include "tabellaPersonaggio.h"

struct TabellaPersonaggio {
    personaggioLink HEAD;
    personaggioLink TAIL;
    unsigned int NumeroPersonaggi;
};

// Crea una tabellaPersonaggio
tabellaPersonaggio creaTabellaPersonaggio() {
    tabellaPersonaggio t = (tabellaPersonaggio)malloc(sizeof(struct TabellaPersonaggio));
    t->HEAD              = creaPersonaggioLink(NULL);
    t->TAIL              = t->HEAD;
    t->NumeroPersonaggi  = 0;
    return t;
}

// Elimina un personaggio indicato per ID, restituisce false se il personaggio non esiste
bool eliminaPersonaggioByID(tabellaPersonaggio t, uint16_t *ID) {
    personaggioLink precedente = ricercaIDprecedente(t, ID); // Trovo l'elemento precedente
    if (precedente != NULL) {                                // Se ho trovato l'ID
        if (getNextItem(precedente) == t->TAIL) {            // Se è l'ultimo elemento
            t->TAIL = precedente;                            // Aggiorno la TAIL
        }
        eliminaAndPrint(precedente);
        return true;
    }
    return false;
};

// Restituisce la HEAD di una tabellaPersonaggio
personaggioLink getTableHead(tabellaPersonaggio t) {
    return t->HEAD;
}

// Restituisce il numero di personaggi di una tabellaPersonaggio
unsigned int getTableNumeroPersonaggi(tabellaPersonaggio t) {
    return t->NumeroPersonaggi;
}

// Restituisce la TAIL di una tabellaPersonaggio
personaggioLink getTableTail(tabellaPersonaggio t) {
    return t->TAIL;
}

// Legge i personaggi da file e li salva in una lista
void parsePersonaggi(tabellaPersonaggio TABLE, FILE *stream) {
    personaggio temp = creaPersonaggio(PERSONAGGIO_MAX_STRING, PERSONAGGIO_MAX_STRING);
    personaggioLink tempList;

    // Creo stringa di appoggio
    char string[(PERSONAGGIO_MAX_STRING * 3) + 1];
    fgets(string, PERSONAGGIO_MAX_STRING * 3, stream); // Leggo la prima riga del file

    while (leggiPersonaggio(string, temp)) { // Sinché leggo correttamente i personaggi
        personaggio p = getResizedPersonaggio(temp);
        copiaPersonaggio(p, temp);
        tempList = creaPersonaggioLink(p);
        addNext(TABLE->TAIL, tempList);
        TABLE->NumeroPersonaggi++;
        TABLE->TAIL = tempList;
        fgets(string, PERSONAGGIO_MAX_STRING * 3, stream); // Leggo la riga successiva
    }

    freePersonaggio(temp);
}

// Stampa una tabellaPersonaggio
void printTabellaPersonaggio(tabellaPersonaggio t) {
    printPersonaggioLink(t->HEAD);
}

// Ricerca e restituisce un personaggio tramite ID
personaggioLink ricercaID(tabellaPersonaggio t, uint16_t *ID) {
    personaggioLink precedente = ricercaIDprecedente(t, ID);
    return precedente == NULL ? NULL : getNextItem(precedente);
}

// Ricerca e restituisce l'elemento precedete a quello indicato tramite ID
personaggioLink ricercaIDprecedente(tabellaPersonaggio t, uint16_t *ID) {
    return ricercaIDprecedenteR(getTableHead(t), ID);
}
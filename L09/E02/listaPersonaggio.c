#include "listaPersonaggio.h"

struct PersonaggioLink {
    personaggio Personaggio;
    personaggioLink Next;
};

struct TabellaPersonaggio {
    personaggioLink HEAD;
    personaggioLink TAIL;
    unsigned int NumeroPersonaggi;
};

const uint8_t PERSONAGGIO_MAX_STRING = 50;

// * Funzioni "private"

// Componente ricorsiva di ricercaIDPrecedente
personaggioLink ricercaIDprecedenteR(personaggioLink next, uint16_t *ID) {
    personaggioLink pointer = getNextItem(next);
    if (pointer == NULL) { // Condizione di terminazione (lista vuota)
        return NULL;
    }

    if (pointer->Next == NULL) { // Condizione di terminazione (lista di un elemento)
        return pointer->Personaggio->ID == *ID ? next : NULL;
    }

    if (pointer->Personaggio->ID == *ID) { // Se ho trovato la corrispondenza
        return next;
    }

    return ricercaIDprecedenteR(next, ID); // Ricerco sull'elemento successivo
}

// * Funzioni pubbliche

// Aggiunge un elemento next subito dopo un elemento l in una lista
void addNext(personaggioLink l, personaggioLink next) {
    if (l->Next == NULL) { // Se si tratta dell'ultimo elemento
        l->Next    = next;
        next->Next = NULL;
        return;
    }

    personaggioLink temp = l->Next;
    next->Next           = temp;
    l->Next              = next;
    return;
}

// Salva un personaggio in un elemento di tipo personaggioLink
personaggioLink creaPersonaggioLink(personaggio p) {
    personaggioLink l = (personaggioLink)malloc(sizeof(struct PersonaggioLink));
    l->Personaggio    = p;
    return l;
}

tabellaPersonaggio creaTabellaPersonaggio() {
    tabellaPersonaggio t = (tabellaPersonaggio)malloc(sizeof(struct TabellaPersonaggio));
    t->HEAD              = creaPersonaggioLink(NULL);
    t->TAIL              = t->HEAD;
    t->NumeroPersonaggi  = 0;
    return t;
}

// Estrare l'elemento successivo a quello dato da una lista, lo stampa e libera la memoria
void eliminaAndPrint(personaggioLink previous) {
    previous = estraiNext(previous);
    printf("L'elemento eliminato è ---> ");
    printPersonaggio(previous->Personaggio, stdout);
    freePersonaggioLink(previous);
}

// Estrae l'elemento successivo in lista
personaggioLink estraiNext(personaggioLink previous) {
    personaggioLink elemento = previous->Next;
    previous->Next           = elemento->Next;
    return elemento;
}

// Dealloca la memoria di una lista ed il suo contenuto
void freePersonaggioLink(personaggioLink l) {
    if (l->Personaggio != NULL) { // Se non sono sulla HEAD
        freePersonaggio(l->Personaggio);
    }
    free(l);
}

// Restituisce l'elemento successivo nella lista
personaggioLink getNextItem(personaggioLink item) {
    return item->Next == NULL ? NULL : item->Next;
}

// Restituisce il personaggio relativo ad un elemento di tipo lista
personaggio getPersonaggio(personaggioLink l) {
    return l->Personaggio;
}

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

// Stampa una lista di personaggi a video
void printPersonaggioLink(personaggioLink l) {
    printPersonaggioLinkFile(l, stdout);
}

// Stampa una lista di personaggi su file
void printPersonaggioLinkFile(personaggioLink l, FILE *stream) {
    puts("I personaggi presenti sono:");
    personaggioLink temp = l;
    while (temp->Next != NULL) {                           // Sinché esiste un elemento successivo
        printPersonaggio(temp->Next->Personaggio, stream); // Stampo l'elemento
        temp = temp->Next;                                 // Passo all'elemento successivo in lista
    }
    printf("\n");
}

// Ricerca e restituisce un personaggio tramite ID
personaggioLink ricercaID(tabellaPersonaggio t, uint16_t *ID) {
    personaggioLink precedente = ricercaIDprecedente(t, ID);
    return precedente == NULL ? NULL : precedente->Next;
}

// Ricerca e restituisce l'elemento precedete a quello indicato tramite ID
personaggioLink ricercaIDprecedente(tabellaPersonaggio t, uint16_t *ID) {
    return ricercaIDprecedenteR(t->HEAD, ID);
}

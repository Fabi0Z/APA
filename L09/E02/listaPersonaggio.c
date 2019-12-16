#include "listaPersonaggio.h"

struct PersonaggioLink {
    personaggio Personaggio;
    personaggioLink Next;
};

const uint8_t PERSONAGGIO_MAX_STRING = 50;

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

// Crea, alloca e restituisce un puntatore a personaggioLink
personaggioLink creaLista(personaggio p) {
    personaggioLink l = (personaggioLink)malloc(sizeof(personaggioLink));
    l->Personaggio    = p;
    return l;
}

// Salva un personaggio in un elemento di tipo personaggioLink
personaggioLink creaPersonaggioLink(personaggio p) {
    personaggioLink l = (personaggioLink)malloc(sizeof(struct PersonaggioLink));
    l->Personaggio    = p;
    return l;
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

// Legge i personaggi da file e li salva in una lista
void parsePersonaggi(tabellaPersonaggio *TABLE, FILE *stream) {
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
personaggioLink ricercaID(personaggioLink HEAD, uint16_t *ID) {
    personaggioLink precedente = ricercaIDprecedente(HEAD, ID);
    return precedente == NULL ? NULL : precedente->Next;
}

// Ricerca ricorsiva che restituisce l'elemento precedete a quello trovato
personaggioLink ricercaIDprecedente(personaggioLink HEAD, uint16_t *ID) {
    personaggioLink pointer = getNextItem(HEAD);
    if (pointer == NULL) { // Condizione di terminazione (lista vuota)
        return NULL;
    }

    if (pointer->Next == NULL) { // Condizione di terminazione (lista di un elemento)
        return pointer->Personaggio->ID == *ID ? HEAD : NULL;
    }

    if (pointer->Personaggio->ID == *ID) { // Se ho trovato la corrispondenza
        return HEAD;
    }

    return ricercaIDprecedente(pointer, ID); // Ricerco sull'elemento successivo
}

#include "personaggio.h"

// Alloca memoria per un oggetto di tipo personaggio
void allocaPersonaggio(personaggio *p, unsigned int nomeSize, unsigned int classeSize) {
    p->Nome   = (char *)calloc(nomeSize, sizeof(char)); // Alloco la memoria
    p->Classe = (char *)calloc(classeSize, sizeof(char));
}
void freePersonaggio(personaggio *p) {         // Dealloca la memoria di un personaggio
    if (p->Equipaggiamento->Oggetti != NULL) { // Se è presente un equipaggiamento
        free(p->Equipaggiamento->Oggetti);
    }
    free(p->Nome);
    free(p->Classe);
    free(p);
}

// Dealloca la memoria di una lista ed il suo contenuto
void freePersonaggioLink(personaggioLink *l) {
    if (l->Personaggio != NULL) { // Se non sono sulla HEAD
        freePersonaggio(l->Personaggio);
    }
    free(l);
}

// Calcola e restituisce le statistiche di un personaggio
void calcolaStatistiche(personaggio *p, stats s) {
    copiaStatistiche(s, p->Statistiche); // Scrivo i valori del personaggio

    if (p->Equipaggiamento->NumeroOggetti == 0) { // Se non ci sono oggetti nell'equipaggiamento mi interrompo
        return;
    }

    oggetto *o;
    for (size_t i = 0; i < N_STATISTICHE; i++) {                         // Per ogni statistica
        for (size_t j = 0; j < p->Equipaggiamento->NumeroOggetti; j++) { // Per ogni oggetto dell'equipaggiamento
            o = p->Equipaggiamento->Oggetti[j];
            s[i] += o->Statistiche[i];
        }

        if (s[i] < 1) {
            s[i] = 1;
        }
        memcpy(p->Statistiche, s, sizeof(int16_t) * N_STATISTICHE);
    }
}

// Aggiunge un oggetto all'equipaggiamento di un personaggio
bool aggiungiEquipaggiamento(personaggio *p, oggetto *o) {
    if (p->Equipaggiamento->NumeroOggetti == 0) { // Se non ho oggetti
        p->Equipaggiamento->NumeroOggetti++;
        p->Equipaggiamento->Oggetti    = (oggetto **)calloc(p->Equipaggiamento->NumeroOggetti, sizeof(oggetto *));
        p->Equipaggiamento->Oggetti[0] = o;
        return true;
    }

    // Creo nuovo array oggetti
    oggetto **new = (oggetto **)calloc(p->Equipaggiamento->NumeroOggetti + 1, sizeof(oggetto *));
    memcpy(new, p->Equipaggiamento->Oggetti, sizeof(oggetto *) * p->Equipaggiamento->NumeroOggetti); // Copio i dati

    // Metto il link all'oggetto
    new[p->Equipaggiamento->NumeroOggetti] = o;
    p->Equipaggiamento->NumeroOggetti++; // Incremento gli oggetti disponibili

    // Sostituisco l'array di oggetti
    free(p->Equipaggiamento->Oggetti);
    p->Equipaggiamento->Oggetti = new;
    return true;
}

// Rimuove un oggetto dall'equipaggiamento di un personaggio
void rimuoviEquipaggiamento(personaggio *p, uint8_t indiceOggetto) {
    p->Equipaggiamento->NumeroOggetti--;
    if (p->Equipaggiamento->NumeroOggetti == 0) { // Se ho 0 oggetti
        free(p->Equipaggiamento->Oggetti);
        p->Equipaggiamento->Oggetti = NULL;
        return;
    }

    oggetto **o = (oggetto **)calloc(p->Equipaggiamento->NumeroOggetti, sizeof(oggetto *));

    for (uint8_t i = 0; i < indiceOggetto; i++) { // Per ogni oggetto precedente a quello da eliminare
        o[i] = p->Equipaggiamento->Oggetti[i];
    }

    for (uint8_t i = indiceOggetto; i < p->Equipaggiamento->NumeroOggetti; i++) { // Per ogni oggetto successivo
        o[i] = p->Equipaggiamento->Oggetti[i + 1];
    }

    free(p->Equipaggiamento->Oggetti);
    p->Equipaggiamento->Oggetti = o;
}

// Stampa un personaggio
void printPersonaggio(personaggio *p, FILE *stream) {
    fprintf(stream, "PG%04" SCNd16, p->ID);
    fprintf(stream, " %s %s ", p->Nome, p->Classe);
    printStatistiche(p->Statistiche, stream);
    fprintf(stream, "\n");
}

// Stampa una lista di personaggi su file
void printPersonaggioLinkFile(personaggioLink *l, FILE *stream) {
    puts("I personaggi presenti sono:");
    personaggioLink temp = *l;
    while (temp.Next != NULL) {                           // Sinché esiste un elemento successivo
        printPersonaggio(temp.Next->Personaggio, stream); // Stampo l'elemento
        temp = *temp.Next;                                // Passo all'elemento successivo in lista
    }
    printf("\n");
}

// Stampa una lista di personaggi a video
void printPersonaggioLink(personaggioLink *l) {
    printPersonaggioLinkFile(l, stdout);
}

// Restituisce l'elemento successivo nella lista
personaggioLink *getNextItem(personaggioLink *item) {
    return item->Next == NULL ? NULL : item->Next;
}

// Crea, alloca e restituisce un puntatore a personaggioLink
personaggioLink *creaLista(personaggio *p) {
    personaggioLink *l = (personaggioLink *)malloc(sizeof(personaggioLink));
    l->Personaggio     = p;
    return l;
}

// Crea, alloca e restituisce un personaggio senza equipaggiamento
personaggio *creaPersonaggio(unsigned int nomeSize, unsigned int classeSize) {
    personaggio *temp                    = (personaggio *)malloc(sizeof(personaggio));
    temp->Equipaggiamento                = creaEquipaggiamento();
    temp->Equipaggiamento->Oggetti       = NULL;
    temp->Equipaggiamento->NumeroOggetti = 0;
    allocaPersonaggio(temp, nomeSize, classeSize);
    return temp;
}

// Salva un personaggio in un elemento di tipo personaggioLink
personaggioLink *creaPersonaggioLink(personaggio *p) {
    personaggioLink *l = (personaggioLink *)malloc(sizeof(personaggioLink));
    l->Personaggio     = p;
    return l;
}

// Copia src in dest
void copiaPersonaggio(personaggio *dest, personaggio *src) {
    // Copio i dati diretti
    dest->ID = src->ID;

    // Copio i dati per puntatore
    strcpy(dest->Nome, src->Nome);
    strcpy(dest->Classe, src->Classe);
    copiaStatistiche(dest, src);
    copiaEquipaggiamento(dest->Equipaggiamento, src->Equipaggiamento);
}

// Alloca memoria per realizzare una copia ridimensionata del personaggio
personaggio *getResizedPersonaggio(personaggio *temp) {
    personaggio *p = creaPersonaggio(strlen(temp->Nome), strlen(temp->Classe));
    return p;
}

// Effettua il parse di un personaggio da stringa, restituisce se la lettura è andata a buon fine o meno
bool leggiPersonaggio(char *string, personaggio *p) {
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "PG%" SCNd16 "%[^\n]", &p->ID, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Nome, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Classe, string);

    stats s;
    if (!leggiStatistiche(string, s)) { // Se la lettura delle statistiche fallisce
        return false;
    }
    copiaStatistiche(p->Statistiche, s);
    return conteggio == 6;
}

// Aggiunge un elemento next subito dopo un elemento l in una lista
void addNext(personaggioLink *l, personaggioLink *next) {
    if (l->Next == NULL) { // Se si tratta dell'ultimo elemento
        l->Next    = next;
        next->Next = NULL;
        return;
    }

    personaggioLink *temp = l->Next;
    next->Next            = temp;
    l->Next               = next;
    return;
}

// Ricerca ricorsiva che restituisce l'elemento precedete a quello trovato
personaggioLink *ricercaID(personaggioLink *HEAD, uint16_t *ID) {
    personaggioLink *pointer = getNextItem(HEAD);
    if (pointer == NULL) { // Condizione di terminazione (lista vuota)
        return NULL;
    }

    if (pointer->Next == NULL) { // Condizione di terminazione (lista di un elemento)
        return pointer->Personaggio->ID == *ID ? HEAD : NULL;
    }

    if (pointer->Personaggio->ID == *ID) { // Se ho trovato la corrispondenza
        return HEAD;
    }

    return ricercaID(pointer, ID); // Ricerco sull'elemento successivo
}

// Estrae l'elemento successivo in lista
personaggioLink *estraiNext(personaggioLink *previous) {
    personaggioLink *elemento = previous->Next;
    previous->Next            = elemento->Next;
    return elemento;
}

// Estrare l'elemento successivo a quello dato da una lista, lo stampa e libera la memoria
void eliminaAndPrint(personaggioLink *previous) {
    previous = estraiNext(previous);
    printf("L'elemento eliminato è ---> ");
    printPersonaggio(previous->Personaggio, stdout);
    freePersonaggioLink(previous);
}
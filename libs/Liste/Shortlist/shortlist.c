#include "shortlist.h"

// Conta gli elementi in una lista
unsigned int countItemsList(shortLink HEAD) {
    if (HEAD == NULL) { // Interruzione per lista non valida
        return 0;
    }
    unsigned int count = 0;
    while (getNext(&HEAD)) { // Sinché ho l'elemento successivo
        count++;
    }
    return count;
}

// Conta gli elementi in una lista
unsigned int countValidItemsList(shortLink HEAD, bool (*valid)(item i, item args), item args) {
    if (HEAD == NULL) { // Interruzione per lista non valida
        return 0;
    }
    unsigned int count = 0;
    while (getNext(&HEAD)) {              // Sinché ho l'elemento successivo
        if ((*valid)(HEAD->Item, args)) { // Se l'elemento è valido
            count++;
        }
    }
    return count;
}

// Elimina ogni nodo di una lista a partire dalla head
void freeList(shortLink HEAD) {
    if (HEAD->Next != NULL) {
        freeList(HEAD->Next);
    }
    free(HEAD);
}

// Aggiorna il shortLink con l'elemento successivo in lista, se sono sull'ultimo elemento restituisce false
bool getNext(shortLink *l) {
    shortLink list = *l;
    if (list == NULL) { // In caso di elemento nullo
        return false;
    }
    if (list->Next == NULL) { // In caso di elemento inesistente
        return false;
    }
    *l = list->Next; // Aggiorno l'elemento
    return true;
}

// Restituisce l'elemento prima della coda di una lista, se è l'unico elemento restituisce se stesso
shortLink getPreTail(shortLink l) {
    if (l->Next == NULL) { // Se ho l'ultimo elemento
        return l;
    }
    if (l->Next->Next == NULL) { // Se ho il penultimo elemento
        return l;
    }
    return getPreTail(l->Next);
}

// Restituisce l'elemento in coda alla lista
shortLink getTail(shortLink l) {
    shortLink pretail = getPreTail(l);
    return pretail->Next == NULL ? pretail : pretail->Next;
}

// Crea un nodo di lista
shortLink newLink(item i) {
    shortLink l = (shortLink)malloc(sizeof(struct ShortList));
    l->Item     = i;
    l->Next     = NULL;
    return l;
}

// Estrae e restituisce l'ultimo item da una lista
item popItem(shortLink list) {
    // Salvo i dati necessari
    shortLink newTail  = getPreTail(list);
    shortLink toDelete = newTail->Next;
    item temp          = toDelete->Item;
    // Estraggo la coda
    newTail->Next = NULL;
    free(toDelete);
    return temp;
}

// Estrae e restituisce l'ultimo shortLink da una lista
item popLink(shortLink list) {
    // Salvo i dati necessari
    shortLink newTail = getPreTail(list);
    shortLink tail    = newTail->Next;
    // Estraggo la coda
    newTail->Next = NULL;
    return tail;
}

// Estrae e restituisce l'item in cima alla lista
item pullItem(shortLink HEAD) {
    // Salvo i dati necessari
    shortLink realLink = HEAD->Next;
    item temp          = realLink->Item;
    // Rimpiazzo la testa
    HEAD->Next = realLink->Next;
    free(realLink);
    return temp;
}

// Estrae e restituisce il shortLink in cima alla lista
item pullLink(shortLink HEAD) {
    // Salvo i dati necessari
    shortLink realLink = HEAD->Next;
    // Rimpiazzo la testa
    HEAD->Next = realLink->Next;
    return realLink;
}

// Aggiunge un shortLink in cima alla lista
void pushLink(shortLink HEAD, shortLink l) {
    shortLink tmp = HEAD->Next;
    HEAD->Next    = l;
    l->Next       = tmp;
}

// Aggiunge un item a fine lista
void pushItem(shortLink list, item i) {
    shortLink l = newLink(i);
    pushLink(list, l);
}

// Aggiunge un shortLink a fine lista
void putLink(shortLink list, shortLink l) {
    shortLink tail = getTail(list);
    tail->Next     = l;
    l->Next        = NULL;
}

// Aggiunge un item a fine lista
void putItem(shortLink list, item i) {
    shortLink l = newLink(i);
    putLink(list, l);
}

/* Ricerca un item tramite un campo identificativo ed una funzione di match partendo dal shortLink sino alla tail, restitusice NULL se non è stato trovato
   matchID = Funzione che restituisce true se l'elemento corretto combacia con l'identificativo */
item searchByID(shortLink HEAD, void *ID, bool(*matchID(item, void *))) {
    if (HEAD->Next == NULL) { // Se mi trovo sull'ultimo elemento
        return (*matchID)(HEAD->Item, ID) ? HEAD->Item : NULL;
    }
    return (*matchID)(HEAD->Item, ID) ? HEAD->Item : (*matchID)(HEAD->Next, ID);
}

// Restituisce una lista con solo gli elementi validi
shortLink validItemsList(shortLink HEAD, bool (*valid)(item i, item args), item args) {
    if (HEAD == NULL) { // Interruzione per lista non valida
        return NULL;
    }
    shortLink newList = newLink(NULL);
    while (getNext(&HEAD)) {              // Sinché ho l'elemento successivo
        if ((*valid)(HEAD->Item, args)) { // Se l'elemento è valido
            putItem(newList, HEAD->Item);
        }
    }
    return newList;
}

// Restituisce una lista con solo gli elementi validi
shortLink validItemsListWithCount(shortLink HEAD, bool (*valid)(item i, item args), item args, unsigned int *numberOfItems) {
    if (HEAD == NULL) { // Interruzione per lista non valida
        return NULL;
    }
    shortLink newList = newLink(NULL);

    if (numberOfItems == NULL) {
        while (getNext(&HEAD)) {              // Sinché ho l'elemento successivo
            if ((*valid)(HEAD->Item, args)) { // Se l'elemento è valido
                putItem(newList, HEAD->Item);
            }
        }
    } else {
        *numberOfItems = 0;
        while (getNext(&HEAD)) {              // Sinché ho l'elemento successivo
            if ((*valid)(HEAD->Item, args)) { // Se l'elemento è valido
                putItem(newList, HEAD->Item);
                *numberOfItems++;
            }
        }
    }

    return newList;
}
#include "shortlist.h"

// Conta gli elementi in una lista
unsigned int countItemsList(shortLink list) {
    if (list == NULL) { // Interruzione per lista non valida
        return 0;
    }

    list               = getHead(list); // trovo la head
    unsigned int count = 0;
    while (getNext(&list)) { // Sinché ho l'elemento successivo
        count++;
    }
    return count;
}

// Conta gli elementi in una lista
unsigned int countValidItemsList(shortLink list, bool (*valid)(item i, item args), item args) {
    if (list == NULL) { // Interruzione per lista non valida
        return 0;
    }
    list               = getHead(list); // trovo la head
    unsigned int count = 0;
    while (getNext(&list)) {              // Sinché ho l'elemento successivo
        if ((*valid)(list->Item, args)) { // Se l'elemento è valido
            count++;
        }
    }
    return count;
}

// Elimina ogni nodo di una lista a partire dalla head
void freeListFromHead(shortLink list) {
    if (list->Next != NULL) {
        freeListFromHead(list->Next);
    }
    free(list);
}

// Elimina ogni nodo di una lista a partire dalla tail
void freeListFromTail(shortLink list) {
    if (list->Previous != NULL) {
        freeListFromTail(list->Previous);
    }
    free(list);
}

// Elimina ogni nodo della lista dalla memoria
void freeList(shortLink list) {
    shortLink next = list->Next;
    freeListFromTail(list);
    if (next != NULL) {
        freeListFromHead(next);
    }
}

// Restituisce la testa di una lista
shortLink getHead(shortLink l) {
    if (l->Previous == NULL) {
        return l;
    }
    return getHead(l->Previous);
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

// Aggiorna il shortLink con l'elemento precedente in lista, se sono sul primo elemento restituisce false
bool getPrevious(shortLink *l) {
    shortLink list = *l;
    if (list == NULL) { // In caso di elemento nullo
        return false;
    }
    if (list->Previous == NULL) { // In caso di elemento inesistente
        return false;
    }
    *l = list->Previous; // Aggiorno l'elemento
    return true;
}

// Restituisce la coda di una lista
shortLink getTail(shortLink l) {
    if (l->Next == NULL) {
        return l;
    }
    return getTail(l->Next);
}

// Crea un nodo di lista
shortLink newLink(item i) {
    shortLink l = (shortLink)malloc(sizeof(struct ShortList));
    l->Item     = i;
    l->Previous = NULL;
    l->Next     = NULL;
    return l;
}

// Estrae e restituisce l'ultimo item da una lista
item popItem(shortLink list) {
    // Salvo i dati necessari
    shortLink tail    = getTail(list);
    item temp         = tail->Item;
    shortLink newTail = tail->Previous;

    // Rimpiazzo la coda
    newTail->Next = NULL;
    free(tail);

    return temp;
}

// Estrae e restituisce l'ultimo shortLink da una lista
item popLink(shortLink list) {
    // Salvo i dati necessari
    shortLink tail    = getTail(list);
    item temp         = tail->Item;
    shortLink newTail = tail->Previous;

    // Rimpiazzo la coda
    newTail->Next = NULL;

    return tail;
}

// Estrae e restituisce l'item in cima alla lista
item pullItem(shortLink list) {
    // Salvo i dati necessari
    shortLink head    = getHead(list);
    item temp         = head->Item;
    shortLink newHead = head->Next;

    // Rimpiazzo la testa
    newHead->Previous = NULL;
    free(head);

    return temp;
}

// Estrae e restituisce il shortLink in cima alla lista
item pullLink(shortLink list) {
    // Salvo i dati necessari
    shortLink head    = getHead(list);
    item temp         = head->Item;
    shortLink newHead = head->Next;

    // Rimpiazzo la testa
    newHead->Previous = NULL;

    return head;
}

// Aggiunge un shortLink in cima alla lista
void pushLink(shortLink list, shortLink l) {
    shortLink head = getHead(list);
    head->Previous = l;
    l->Next        = head;
}

// Aggiunge un item a fine lista
void pushItem(shortLink list, item i) {
    shortLink l = newLink(i);
    pushLink(list, l);
}

// Aggiunge un shortLink a fine lista
void putLink(shortLink list, shortLink l) {
    shortLink tail = getTail(list);
    l->Previous    = tail;
    tail->Next     = l;
}

// Aggiunge un item a fine lista
void putItem(shortLink list, item i) {
    shortLink l = newLink(i);
    putLink(list, l);
}

/* Ricerca un item tramite un campo identificativo ed una funzione di match partendo dal shortLink sino alla tail, restitusice NULL se non è stato trovato
   matchID = Funzione che restituisce true se l'elemento corretto combacia con l'identificativo */
item searchByIDfromHead(shortLink list, void *ID, bool(*matchID(item, void *))) {
    if (list->Next == NULL) { // Se mi trovo sull'ultimo elemento
        return (*matchID)(list->Item, ID) ? list->Item : NULL;
    }
    return (*matchID)(list->Item, ID) ? list->Item : (*matchID)(list->Next, ID);
}

/* Ricerca un item tramite un campo identificativo ed una funzione di match partendo dal shortLink sino alla head, restitusice NULL se non è stato trovato
   matchID = Funzione che restituisce true se l'elemento corretto combacia con l'identificativo */
item searchByIDfromTail(shortLink list, void *ID, bool(*matchID(item, void *))) {
    if (list->Previous == NULL) { // Se mi trovo sul primo elemento
        return (*matchID)(list->Item, ID) ? list->Item : NULL;
    }
    return (*matchID)(list->Item, ID) ? list->Item : (*matchID)(list->Previous, ID);
}

/* Ricerca un item tramite un campo identificativo ed una funzione di match, restitusice NULL se non è stato trovato
   matchID = Funzione che restituisce true se l'elemento corretto combacia con l'identificativo */
item searchByID(shortLink list, void *ID, bool(*matchID(item, void *))) {
    shortLink top = searchByIDfromTail(list, ID, matchID);
    return top == NULL ? searchByIDfromHead(list, ID, matchID) : top;
}

// Restituisce una lista con solo gli elementi validi
shortLink validItemsList(shortLink list, bool (*valid)(item i, item args), item args) {
    if (list == NULL) { // Interruzione per lista non valida
        return NULL;
    }
    list              = getHead(list); // trovo la head
    shortLink newList = newLink(NULL);
    while (getNext(&list)) {              // Sinché ho l'elemento successivo
        if ((*valid)(list->Item, args)) { // Se l'elemento è valido
            putItem(newList, list->Item);
        }
    }
    return newList;
}

// Restituisce una lista con solo gli elementi validi
shortLink validItemsListWithCount(shortLink list, bool (*valid)(item i, item args), item args, unsigned int *numberOfItems) {
    if (list == NULL) { // Interruzione per lista non valida
        return NULL;
    }
    list              = getHead(list); // trovo la head
    shortLink newList = newLink(NULL);

    if (numberOfItems == NULL) {
        while (getNext(&list)) {              // Sinché ho l'elemento successivo
            if ((*valid)(list->Item, args)) { // Se l'elemento è valido
                putItem(newList, list->Item);
            }
        }
    } else {
        *numberOfItems = 0;
        while (getNext(&list)) {              // Sinché ho l'elemento successivo
            if ((*valid)(list->Item, args)) { // Se l'elemento è valido
                putItem(newList, list->Item);
                *numberOfItems++;
            }
        }
    }

    return newList;
}
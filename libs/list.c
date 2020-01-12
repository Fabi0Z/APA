#include "list.h"

// Conta gli elementi in una lista
unsigned int countItemsList(link list) {
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
unsigned int countValidItemsList(link list, bool (*valid)(item i, item args), item args) {
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
void freeListFromHead(link list) {
    if (list->Next != NULL) {
        freeListFromHead(list->Next);
    }
    free(list);
}

// Elimina ogni nodo di una lista a partire dalla tail
void freeListFromTail(link list) {
    if (list->Previous != NULL) {
        freeListFromTail(list->Previous);
    }
    free(list);
}

// Elimina ogni nodo della lista dalla memoria
void freeList(link list) {
    link next = list->Next;
    freeListFromTail(list);
    if (next != NULL) {
        freeListFromHead(next);
    }
}

// Restituisce la testa di una lista
link getHead(link l) {
    if (l->Previous == NULL) {
        return l;
    }
    return getHead(l->Previous);
}

// Aggiorna il link con l'elemento successivo in lista, se sono sull'ultimo elemento restituisce false
bool getNext(link *l) {
    link list = *l;
    if (list == NULL) { // In caso di elemento nullo
        return false;
    }
    if (list->Next == NULL) { // In caso di elemento inesistente
        return false;
    }
    *l = list->Next; // Aggiorno l'elemento
    return true;
}

// Aggiorna il link con l'elemento precedente in lista, se sono sul primo elemento restituisce false
bool getPrevious(link *l) {
    link list = *l;
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
link getTail(link l) {
    if (l->Next == NULL) {
        return l;
    }
    return getTail(l->Next);
}

// Crea un nodo di lista
link newLink(item i) {
    link l      = (link)malloc(sizeof(struct List));
    l->Item     = i;
    l->Previous = NULL;
    l->Next     = NULL;
    return l;
}

// Estrae e restituisce l'ultimo item da una lista
item popItem(link list) {
    // Salvo i dati necessari
    link tail    = getTail(list);
    item temp    = tail->Item;
    link newTail = tail->Previous;

    // Rimpiazzo la coda
    newTail->Next = NULL;
    free(tail);

    return temp;
}

// Estrae e restituisce l'ultimo link da una lista
item popLink(link list) {
    // Salvo i dati necessari
    link tail    = getTail(list);
    item temp    = tail->Item;
    link newTail = tail->Previous;

    // Rimpiazzo la coda
    newTail->Next = NULL;

    return tail;
}

// Estrae e restituisce l'item in cima alla lista
item pullItem(link list) {
    // Salvo i dati necessari
    link head    = getHead(list);
    item temp    = head->Item;
    link newHead = head->Next;

    // Rimpiazzo la testa
    newHead->Previous = NULL;
    free(head);

    return temp;
}

// Estrae e restituisce il link in cima alla lista
item pullLink(link list) {
    // Salvo i dati necessari
    link head    = getHead(list);
    item temp    = head->Item;
    link newHead = head->Next;

    // Rimpiazzo la testa
    newHead->Previous = NULL;

    return head;
}

// Aggiunge un link in cima alla lista
void pushLink(link list, link l) {
    link head      = getHead(list);
    head->Previous = l;
    l->Next        = head;
}

// Aggiunge un item a fine lista
void pushItem(link list, item i) {
    link l = newLink(i);
    pushLink(list, l);
}

// Aggiunge un link a fine lista
void putLink(link list, link l) {
    link tail   = getTail(list);
    l->Previous = tail;
    tail->Next  = l;
}

// Aggiunge un item a fine lista
void putItem(link list, item i) {
    link l = newLink(i);
    putLink(list, l);
}

/* Ricerca un item tramite un campo identificativo ed una funzione di match partendo dal link sino alla tail, restitusice NULL se non è stato trovato
   matchID = Funzione che restituisce true se l'elemento corretto combacia con l'identificativo */
item searchByIDfromHead(link list, void *ID, bool(*matchID(item, void *))) {
    if (list->Next == NULL) { // Se mi trovo sull'ultimo elemento
        return (*matchID)(list->Item, ID) ? list->Item : NULL;
    }
    return (*matchID)(list->Item, ID) ? list->Item : (*matchID)(list->Next, ID);
}

/* Ricerca un item tramite un campo identificativo ed una funzione di match partendo dal link sino alla head, restitusice NULL se non è stato trovato
   matchID = Funzione che restituisce true se l'elemento corretto combacia con l'identificativo */
item searchByIDfromTail(link list, void *ID, bool(*matchID(item, void *))) {
    if (list->Previous == NULL) { // Se mi trovo sul primo elemento
        return (*matchID)(list->Item, ID) ? list->Item : NULL;
    }
    return (*matchID)(list->Item, ID) ? list->Item : (*matchID)(list->Previous, ID);
}

/* Ricerca un item tramite un campo identificativo ed una funzione di match, restitusice NULL se non è stato trovato
   matchID = Funzione che restituisce true se l'elemento corretto combacia con l'identificativo */
item searchByID(link list, void *ID, bool(*matchID(item, void *))) {
    link top = searchByIDfromTail(list, ID, matchID);
    return top == NULL ? searchByIDfromHead(list, ID, matchID) : top;
}

// Restituisce una lista con solo gli elementi validi
link validItemsList(link list, bool (*valid)(item i, item args), item args, unsigned int *numberOfItems) {
    if (list == NULL) { // Interruzione per lista non valida
        return NULL;
    }
    list         = getHead(list); // trovo la head
    link newList = newLink(NULL);

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
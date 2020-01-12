#include "list.h"

// Crea un nodo di lista
link creaLink(item i) {
    link l      = (link)malloc(sizeof(struct List));
    l->Item     = i;
    l->Previous = NULL;
    l->Next     = NULL;
    return l;
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

// Aggiorna il link nell'elemento successivo in lista, se non esiste restituisce false
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

// Restituisce il numero di elementi presenti in una lista
unsigned int getNumberOfItems(link l) {
    l = getHead(l); // Risalgo alla head

    if (getNext(&l)) { // Se non c'è nemmeno un elemento successivo
        return 0;
    }

    unsigned int count = 0;
    do {
        count++;
    } while (getNext(&l)); // Sinché esiste l'elemento successivo

    return count;
}

// Restituisce la coda di una lista
link getTail(link l) {
    if (l->Next == NULL) {
        return l;
    }
    return getTail(l->Next);
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
    link l = creaLink(i);
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
    link l = creaLink(i);
    putLink(list, l);
}

/* Ricerca un item tramite un campo identificativo ed una funzione di match partendo dal link sino alla tail, restitusice NULL se non è stato trovato
   matchID = Funzione che restituisce true se l'elemento corretto combacia con l'identificativo */
item searchByIDfromHead(link list, void *ID, bool(*matchID(item, void *))) {
    if (list->Next == NULL) {
        return (*matchID)(list->Item, ID) ? list->Item : NULL;
    }
    return (*matchID)(list->Item, ID) ? list->Item : (*matchID)(list->Next, ID);
}

/* Ricerca un item tramite un campo identificativo ed una funzione di match partendo dal link sino alla head, restitusice NULL se non è stato trovato
   matchID = Funzione che restituisce true se l'elemento corretto combacia con l'identificativo */
item searchByIDfromTail(link list, void *ID, bool(*matchID(item, void *))) {
    if (list->Previous == NULL) {
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
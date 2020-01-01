#include "list.h"

// Crea un nodo di lista
link creaLink(item i) {
    link l      = (link)malloc(sizeof(struct List));
    l->Item     = i;
    l->Previous = NULL;
    l->Next     = NULL;
    return l;
}

// Restituisce la testa di una lista
link getHead(link l) {
    if (l->Previous == NULL) {
        return l;
    }
    return getTail(l->Previous);
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
    link tail      = getTail(list);
    tail->Previous = l;
}

// Aggiunge un item a fine lista
void putItem(link list, item i) {
    link l = creaLink(i);
    putLink(list, l);
}
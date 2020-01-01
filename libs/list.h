#ifndef LIST_H
#define LIST_H

#include "smartlib.h"

typedef struct List *link;
struct List {
    item Item;
    link Previous;
    link Next;
};

item searchByID(link list, void *ID, bool(*matchID(item, void *)));
item searchByIDfromTail(link list, void *ID, bool(*matchID(item, void *)));
item searchByIDfromHead(link list, void *ID, bool(*matchID(item, void *)));
void putItem(link list, item i);
void putLink(link list, link l);
void pushItem(link list, item i);
void pushLink(link list, link l);
item pullLink(link list);
item pullItem(link list);
item popLink(link list);
item popItem(link list);
link getTail(link l);
link getHead(link l);
void freeList(link list);
void freeListFromTail(link list);
void freeListFromHead(link list);
link creaLink(item i);

#endif // LIST_H

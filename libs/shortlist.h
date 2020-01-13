#ifndef SHORTLIST_H
#define SHORTLIST_H

#include "smartlib.h"

typedef struct ShortList *shortLink;
struct ShortList {
    item Item;
    shortLink Previous;
    shortLink Next;
};

shortLink validItemsListWithCount(shortLink list, bool (*valid)(item i, item args), item args, unsigned int *numberOfItems);
shortLink validItemsList(shortLink list, bool (*valid)(item i, item args), item args);
item searchByID(shortLink list, void *ID, bool(*matchID(item, void *)));
item searchByIDfromTail(shortLink list, void *ID, bool(*matchID(item, void *)));
item searchByIDfromHead(shortLink list, void *ID, bool(*matchID(item, void *)));
void putItem(shortLink list, item i);
void putLink(shortLink list, shortLink l);
void pushItem(shortLink list, item i);
void pushLink(shortLink list, shortLink l);
item pullLink(shortLink list);
item pullItem(shortLink list);
item popLink(shortLink list);
item popItem(shortLink list);
shortLink newLink(item i);
shortLink getTail(shortLink l);
bool getPrevious(shortLink *l);
void freeList(shortLink list);
void freeListFromTail(shortLink list);
void freeListFromHead(shortLink list);
unsigned int countValidItemsList(shortLink list, bool (*valid)(item i, item args), item args);
bool getNext(shortLink *l);
shortLink getHead(shortLink l);
unsigned int countItemsList(shortLink list);

#endif // ! SHORTLIST_H

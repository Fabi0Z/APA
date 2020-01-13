#ifndef SHORTLIST_H
#define SHORTLIST_H

#include "smartlib.h"

typedef struct ShortList *shortLink;
struct ShortList {
    item Item;
    shortLink Next;
};

shortLink validItemsListWithCount(shortLink HEAD, bool (*valid)(item i, item args), item args, unsigned int *numberOfItems);
shortLink validItemsList(shortLink HEAD, bool (*valid)(item i, item args), item args);
item searchByID(shortLink HEAD, void *ID, bool(*matchID(item, void *)));
void putItem(shortLink list, item i);
void putLink(shortLink list, shortLink l);
void pushItem(shortLink list, item i);
void pushLink(shortLink HEAD, shortLink l);
item pullLink(shortLink HEAD);
item pullItem(shortLink HEAD);
item popLink(shortLink list);
item popItem(shortLink list);
shortLink newLink(item i);
shortLink getTail(shortLink l);
shortLink getPreTail(shortLink l);
void freeList(shortLink HEAD);
unsigned int countValidItemsList(shortLink HEAD, bool (*valid)(item i, item args), item args);
bool getNext(shortLink *l);
unsigned int countItemsList(shortLink HEAD);

#endif // ! SHORTLIST_H

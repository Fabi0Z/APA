#ifndef DATASTRUCTLIB_H
#define DATASTRUCTLIB_H

#include "array.h"
#include "list.h"

link validItemsListFromArray(array a, bool (*valid)(item i, item args), item args, unsigned int *numberOfItems);
array validItemsArrayFromList(link l, bool (*valid)(item i, item args), item args);
array listToArrayOfGivenSize(link HEAD, unsigned int elementiLista);
array listToArray(link HEAD);
link arrayToList(array a);

#endif // DATASTRUCTLIB_H

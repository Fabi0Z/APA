#ifndef SORTLIB_H
#define SORTLIB_H

#include "array.h"

void mergeSort(array a, bool (*minorEqual)(item a, item b, item args), item args);

#endif // SORTLIB_H

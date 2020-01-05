#ifndef SORTLIB_H
#define SORTLIB_H

#include "array.h"

void mergeSort(array a, bool (*minorEqual)(item a, item b, item extraArgs), item extraArgs);

#endif // SORTLIB_H

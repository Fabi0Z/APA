#include "datastructlib.h"

// Converte un array in una lista
link arrayToList(array a) {
    link HEAD = creaLink(NULL);
    for (size_t i = 0; i < a->ObjectsNumber; i++) {
        putItem(HEAD, a->Objects[i]);
    }
    return HEAD;
}

// Converte una lista in un array senza funzioni integrate, restituisce NULL per lista vuota
array listToArray(link HEAD) {
    unsigned int elementiLista = getNumberOfItems(HEAD);
    if (elementiLista == 0) { // Se non ho elementi
        return NULL;
    }

    array a = newArray(NULL, NULL, NULL);
    allocateArray(a, elementiLista);

    unsigned int index = 0;
    while (getNext(&HEAD)) {
        a->Objects[index++] = HEAD->Item;
    }

    return a;
}
#include "datastructlib.h"

// Converte un array in una lista
link arrayToList(array a) {
    link HEAD = newLink(NULL);
    for (size_t i = 0; i < a->ObjectsNumber; i++) {
        putItem(HEAD, a->Objects[i]);
    }
    return HEAD;
}

// Converte una lista in un array senza funzioni integrate, restituisce NULL per lista vuota
array listToArray(link HEAD) {
    HEAD                       = getHead(HEAD);
    unsigned int elementiLista = countItemsList(HEAD);
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

// Converte una lista in un array senza funzioni integrate, restituisce NULL per lista vuota
array listToArrayOfGivenSize(link HEAD, unsigned int elementiLista) {
    HEAD = getHead(HEAD);
    if (elementiLista == 0) { // Se non ho elementi
        return NULL;
    }
    array a = newArray(NULL, NULL, NULL);
    allocateArray(a, elementiLista);
    for (unsigned int i = 0; i < a->ObjectsNumber; i++) { // Per ogni elemento
        getNext(&HEAD);
        a->Objects[i] = HEAD->Item;
    }
    return a;
}

// Crea un array con solo gli elementi validi secondo una funzione di validità, se nessuno è valido restituisce NULL
array validItemsArrayFromList(link l, bool (*valid)(item i, item args), item args) {
    unsigned int elementi;
    link listaValida = validItemsListWithCount(l, valid, args, &elementi); // Creo la lista di elementi validi
    array a          = listToArrayOfGivenSize(l, elementi);
    freeList(listaValida);
    return a;
}

// Restituisce una lista di elementi validi a parte da un array
link validItemsListFromArray(array a, bool (*valid)(item i, item args), item args, unsigned int *numberOfItems) {
    if (a == NULL) { // Interruzione per array nullo
        return NULL;
    }

    if (numberOfItems != NULL) {
        *numberOfItems = 0;
    }

    link list = newLink(NULL);  // Creo la lista
    if (a->ObjectsNumber = 0) { // Interruzione per array di 0 elementi
        return list;
    }

    if (numberOfItems == NULL) {
        for (unsigned int i = 0; i < a->ObjectsNumber; i++) { // Per ogni elemento
            if ((*valid)(list->Item, args)) {                 // Se l'elemento è valido
                putItem(list, a->Objects[i]);
            }
        }

    } else {
        for (unsigned int i = 0; i < a->ObjectsNumber; i++) { // Per ogni elemento
            if ((*valid)(list->Item, args)) {                 // Se l'elemento è valido
                putItem(list, a->Objects[i]);
                *numberOfItems++;
            }
        }
    }
    return list;
}
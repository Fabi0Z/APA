#include "ListaAdicenze.h"

// Aggiunge un'adiacenza alla lista
bool addAdiacenza(listaAdicenze l, unsigned int Index, unsigned int Destinazione, unsigned int Peso) {
    if (Index >= l->Indici->ObjectsNumber) {
        return false;
    }

    adiacenza tmpAdiacenza = newAdiacenza(Destinazione, Peso);
    if (l->Indici->Objects[Index] == NULL) { // Se la lista non è ancora stata creata
        l->Indici->Objects[Index] = newLink(tmpAdiacenza);
        return true;
    }
    link tmpLink = l->Indici->Objects[Index];
    putItem(tmpLink, tmpAdiacenza);
    return true;
}

// Crea una lista adiacenza
listaAdicenze newListaAdiacenze(unsigned int NumeroVertici) {
    listaAdicenze l = malloc(sizeof(struct ListaAdicenze));
    l->Indici       = newArray((void *)&freeList, NULL, NULL);
    allocateArray(l->Indici, NumeroVertici);
    for (unsigned int i = 0; i < l->Indici->ObjectsNumber; i++) { // Per ogni Vertice
        l->Indici->Objects[i] = NULL;
    }
    return l;
}

// Elimina una lista adiacenza
void freeListaAdiacenza(listaAdicenze l) {
    for (unsigned int i = 0; i < l->Indici->ObjectsNumber; i++) {
        if (l->Indici->Objects[i] != NULL) { // Se la lista esiste
            link nextItem = l->Indici->Objects[i];
            while (getNext(&nextItem)) {
                freeAdiacenza(nextItem->Item); // Elimino l'adiacenza
            }
        }
    }
    freeArray(l->Indici, true); // Elimino l'array e le liste associate
    free(l);                    // Elimino la lista adiacenza
}
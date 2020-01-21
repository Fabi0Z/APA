#include "ListaAdicenze.h"

// Aggiunge un'adiacenza alla lista
bool addAdiacenza(listaAdicenze l, unsigned int Index, unsigned int Destinazione, unsigned int Peso) {
    if (Index >= l->Indici->ObjectsNumber) {
        return false;
    }
    link tmpLink           = l->Indici->Objects[Index];
    adiacenza tmpAdiacenza = newAdiacenza(Destinazione, Peso);
    putItem(tmpLink, tmpAdiacenza);
    return true;
}

// Crea una lista adiacenza
listaAdicenze newListaAdiacenze(unsigned int NumeroVertici) {
    bool tmpPeso    = adiacenzaPesataStatus(); // Salvo il valore di default
    listaAdicenze l = malloc(sizeof(struct ListaAdicenze));
    l->Indici       = newArray((void *)&freeList, NULL, NULL);
    for (unsigned int i = 0; i < l->Indici->ObjectsNumber; i++) { // Per ogni Vertice
        l->Indici->Objects[i] = newLink(NULL);                    // Creo la HEAD;
        link tmpLink          = l->Indici->Objects[i];
        tmpLink->Item         = newAdiacenza(i, 0);
    }
    adiacenzaPesata(tmpPeso); // Reimposto il valore di default
}

// Elimina una lista adiacenza
void freeListaAdiacenza(listaAdicenze l) {
    for (unsigned int i = 0; i < l->Indici->ObjectsNumber; i++) {
        link nextItem = l->Indici->Objects[i];
        while (getNext(&nextItem)) {
            freeAdiacenza(nextItem->Item); // Elimino l'adiacenza
        }
    }
    freeArray(l->Indici, true); // Elimino l'array e le liste associate
    free(l);                    // Elimino la lista adiacenza
}
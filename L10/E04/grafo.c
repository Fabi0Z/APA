#include "grafo.h"

struct Grafo {
    array ListaAdiacenze;
    matriceAdiacenze Matrice;
    unsigned int NumeroVertici;
    unsigned int NumeroArchi;
};

grafo creaGrafo(unsigned int NumeroVertici, unsigned int NumeroArchi) {
    grafo g          = malloc(sizeof(struct Grafo));
    g->NumeroArchi   = NumeroArchi;
    g->NumeroVertici = NumeroVertici;
}

void creaListaAdiacenze(grafo g) {
    // Alloco la lista adiacenze
    g->ListaAdiacenze = newArray(&freeList, NULL, NULL);
    allocateArray(g->ListaAdiacenze, g->NumeroVertici);
}
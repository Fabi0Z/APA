#include "grafo.h"

struct Grafo {
    array ListaAdiacenze;
    matriceAdiacenze Matrice;
    symbleTable Corrispondenze;
    unsigned int NumeroVertici;
    unsigned int NumeroArchi;
};

// Crea un grafo
grafo creaGrafo(unsigned int NumeroVertici, unsigned int NumeroArchi) {
    grafo g           = malloc(sizeof(struct Grafo));
    g->NumeroArchi    = NumeroArchi;
    g->NumeroVertici  = NumeroVertici;
    g->Corrispondenze = newSymbleTable(NumeroArchi);
}

void creaListaAdiacenze(grafo g) {
    // Alloco la lista adiacenze
    g->ListaAdiacenze = newArray((void *)&freeList, NULL, NULL);
    allocateArray(g->ListaAdiacenze, g->NumeroVertici);
}

void creaMatriceAdiacenze(grafo g) {
    g->Matrice = creaMatrice(g->NumeroArchi);
}

void parseGrafo(grafo g, char *filename) {

}
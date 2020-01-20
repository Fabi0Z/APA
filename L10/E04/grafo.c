#include "grafo.h"

struct Grafo {
    listaAdicenze ListaAdiacenze;
    matriceAdiacenze Matrice;
    symbleTable Corrispondenze;
    unsigned int NumeroVertici;
    unsigned int NumeroArchi;
};

// Aggiunge un arco alla tabella di simboli
static void addArcoToSymbleTable(grafo g, arco a) {
    g->NumeroVertici += addSymble(g->Corrispondenze, a->IDElaboratori[0]) ? 1 : 0; // Se l'elaboratore è già stato considerato non incremento il numero di nodi
    g->NumeroVertici += addSymble(g->Corrispondenze, a->IDElaboratori[1]) ? 1 : 0; // Se l'elaboratore è già stato considerato non incremento il numero di nodi
}

// Aggiungo un arco alla matrice di adiacenza
static void addArcoToMatrice(grafo g, arco a) {
    // Leggo gli indici
    unsigned int elab0 = getSymbleIndex(g->Corrispondenze, a->IDElaboratori[0]);
    unsigned int elab1 = getSymbleIndex(g->Corrispondenze, a->IDElaboratori[1]);

    g->Matrice->Matrix[elab0][elab1] = a->Flusso; // Salvo il valore del flusso
}

// Crea un grafo
grafo creaGrafo(unsigned int NumeroVertici, unsigned int NumeroArchi) {
    grafo g           = malloc(sizeof(struct Grafo));
    g->NumeroArchi    = NumeroArchi;
    g->NumeroVertici  = NumeroVertici;
    g->Corrispondenze = newSymbleTable(NumeroArchi);
    return g;
}

// Crea la lista di adiacenze del grafo
void creaListaAdiacenze(grafo g) {
    g->ListaAdiacenze = newListaAdiacenze(g->NumeroVertici); // Creo la lista

    // Esploro la matrice
    unsigned int **Matrix = g->Matrice->Matrix;
    for (unsigned int i = 0; i < g->Matrice->Size; i++) {
        for (unsigned int j = 0; j < g->Matrice->Size; j++) {
            if (Matrix[i][j] != 0) { // Se il collegamento esiste
                addAdiacenza(g->ListaAdiacenze, i, j, Matrix[i][j]);
            }
        }
    }
}

grafo parseGrafo(char *filename) {
    unsigned int numeroArchi = countNumberOfLines(filename);
    grafo g                  = creaGrafo(0, numeroArchi);
    unsigned int max_string  = 250;
    FILE *stream             = smartFopen(filename, "r");

    link HEAD = newLink(NULL); // Creo la head della lista di archi

    char string[max_string + 1];
    for (unsigned int i = 0; i < g->NumeroArchi; i++) { // Per ogni elemento
        fgets(string, max_string, stream);
        arco tmp = parseArco(string); // Leggo l'arco
        putItem(HEAD, tmp);           // Aggiungo l'arco alla lista
        addArcoToSymbleTable(g, tmp); // Aggiungo l'arco alla symble table
    }

    g->Matrice    = creaMatrice(g->NumeroVertici); // Creo la matrice di adiacenze
    link nextItem = HEAD;
    while (getNext(&nextItem)) {
        addArcoToMatrice(g, nextItem->Item); // Aggiungo l'arco alla matrice
        freeArco(nextItem->Item);            // Elimino l'arco
    }
    freeList(HEAD); // Elimino la lista
    fclose(stream); // Chiudo il filestream
    return g;
}
#include "grafo.h"

struct Grafo {
    listaAdicenze ListaAdiacenze;
    matriceAdiacenze Matrice;
    symbleTable Corrispondenze;
    unsigned int NumeroVertici;
    unsigned int NumeroArchi;
};

static uint8_t MAX_NAME = 50;

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

// Stampa un arco di un grafo
static void printArcoGrafo(grafo g, unsigned int Nodo0, unsigned int Nodo1) {
    printf("%s %s %u\n", getSymbleName(g->Corrispondenze, Nodo0), getSymbleName(g->Corrispondenze, Nodo1), g->Matrice->Matrix[Nodo0][Nodo1]); // Stampo l'arco
}

// Stampa un arco di un grafo
static void printArcoGrafoLista(grafo g, link nodo, unsigned int nodoPartenza) {
    adiacenza a = nodo->Item;
    printf("%s %s %u\n", getSymbleName(g->Corrispondenze, nodoPartenza), getSymbleName(g->Corrispondenze, a->Destinazione[0]), getPeso(a)); // Stampo l'arco
}

// Stampa il grafo a partire dalla matrice di adiacenze
static void printGrafoMatriceAdiacenze(grafo g) {
    // Esploro la matrice
    unsigned int **Matrix = g->Matrice->Matrix;
    for (unsigned int i = 0; i < g->Matrice->Size; i++) {
        for (unsigned int j = 0; j < g->Matrice->Size; j++) {
            if (Matrix[i][j] != 0) { // Se il collegamento esiste
                printArcoGrafo(g, i, j);
            }
        }
    }
}

// Crea un grafo
grafo creaGrafo(unsigned int NumeroVertici, unsigned int NumeroArchi) {
    grafo g           = malloc(sizeof(struct Grafo));
    g->NumeroArchi    = NumeroArchi;
    g->NumeroVertici  = NumeroVertici;
    g->Corrispondenze = newSymbleTable(NumeroArchi);
    g->ListaAdiacenze = NULL;
    return g;
}

// Crea la lista di adiacenze del grafo
void creaListaAdiacenze(grafo g) {
    adiacenzaPesata(true);                                   // Imposto la lista come pesata
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
    unsigned int max_string  = MAX_NAME * 5 + 1;
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

// Stampa un grafo
void printGrafo(grafo g) {
    if (g->ListaAdiacenze == NULL) {
        return printGrafoMatriceAdiacenze(g);
    }

    for (unsigned int i = 0; i < g->ListaAdiacenze->Indici->ObjectsNumber; i++) { // Per ogni vertice
        if (g->ListaAdiacenze->Indici->Objects[i] != NULL) {                      // Se la lista esiste
            link nextItem = g->ListaAdiacenze->Indici->Objects[i];
            printArcoGrafoLista(g, nextItem, i);     // Stampo il primo arco
            while (getNext(&nextItem)) {             // Sinché la lista è esplorabile
                printArcoGrafoLista(g, nextItem, i); // Stampo l'arco
            }
        }
    }
}

// * PARTE DI RIORDINAMENTO

// Restituisce true se il nome del vertice di partenza dell'adiacenza a è prima in ordine alfabetico rispetto a quello di b
bool minorUgualeNomeVertice(unsigned int *a, unsigned int *b, grafo g) {
    char *nomeA = getSymbleName(g->Corrispondenze, *a);
    char *nomeB = getSymbleName(g->Corrispondenze, *b);
    return ordineAlfabetico(nomeA, nomeB);
}

// Riordina i vertici di una lista adiacenze in un arco per nome
void reorderVertexByName(grafo g) {
    unsigned int indici[g->ListaAdiacenze->Indici->ObjectsNumber];        // Array di interi contenente gli indici
    array indiciArray = newArray(NULL, NULL, NULL);                       // Creo modello di array
    allocateArray(indiciArray, g->ListaAdiacenze->Indici->ObjectsNumber); // Alloco l'array

    for (unsigned int i = 0; i < indiciArray->ObjectsNumber; i++) { // Scrivo i valori degli indici
        indici[i]               = i;                                // Scrivo il numero
        indiciArray->Objects[i] = &indici[i];                       // Copio il puntatore
    }

    mergeSort(indiciArray, (void *)&minorUgualeNomeVertice, g); // Applico il merge sort

    for (unsigned int i = 0; i < indiciArray->ObjectsNumber; i++) {
        unsigned int *value = indiciArray->Objects[i]; // Salvo il numero
        if (i != *value) {                             // Se il numero è diverso dall'indice
            // Scambio le liste
            link tmp                                   = g->ListaAdiacenze->Indici->Objects[i];
            link tmp2                                  = g->ListaAdiacenze->Indici->Objects[*value];
            g->ListaAdiacenze->Indici->Objects[i]      = tmp2;
            g->ListaAdiacenze->Indici->Objects[*value] = tmp;

            if (/* condition */) {
                /* code */
            }
            while (/* condition */) {
                /* code */
            }

            updateSymbleTableItemIndex(g->Corrispondenze, i, *value); // Sostituisco l'indice
        }
    }

    freeArray(indiciArray, false); // Elimino l'array
}
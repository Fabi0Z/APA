#include <error.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const unsigned int MAX_FILENAME = 30;

typedef struct ListaNodi listaNodi;

typedef struct ListaNodi { // Lista di nodi
    unsigned int Destinazione;
    listaNodi *Successivo;
} listaNodi;

typedef struct Lista { // Oggetto lista contenente la head
    listaNodi *Head;
} lista;

typedef struct Grafo { // Struttura per rappresentare un grafo
    unsigned int NumeroVertici;
    lista *Vertici; // Array di liste (uno per nodo)
} grafo;

void addElementAtEnd(lista head, unsigned int nodo) { // Aggiunge un nodo in coda ad una lista
    while (head.Head->Successivo != NULL) {           // Sinchè è presente un elemento successivo
        head.Head = head.Head->Successivo;
    }
    // Ora temp rappresenta l'ultimo elemento della lista
    listaNodi *elemento    = (listaNodi *)malloc(sizeof(listaNodi)); // Creo il nuovo elemento
    elemento->Destinazione = nodo;

    head.Head->Successivo = elemento; // Aggiungo l'elemento in coda
}

grafo parseGrafo(FILE *stream) { // Legge un Grafo da file
    grafo g;
    unsigned int NumeroArchi;
    fscanf(stream, "%d %d", &g.NumeroVertici, &NumeroArchi); // Leggo il numero di Vertici e di Archi

    g.Vertici = (unsigned int *)calloc(sizeof(unsigned int), g.NumeroVertici); // Alloco la memoria necessaria

    for (size_t i = 0; i < g.NumeroVertici; i++) {                                // Per ogni lista
        g.Vertici[i].Head               = (listaNodi *)malloc(sizeof(listaNodi)); // Alloco memoria per la HEAD
        g.Vertici[i].Head->Destinazione = NULL;                                   // Inserisco NULL nella destinazione della HEAD
    }

    for (size_t i = 0; i < NumeroArchi; i++) { // Per ogni arco
        unsigned int partenza, arrivo;
        fscanf(stream, "%d %d", &partenza, &arrivo);
        addElementAtEnd(g.Vertici[partenza], arrivo); // Aggiungo il collegamento al nodo d'origine
    }

    return g;
}

void printLista(lista l) { // Stampa una lista di nodi
    l.Head = l.Head->Successivo; // Parto dal secondo elemento (senza stampare la head)
    while (l.Head != NULL) { // Sinché l'elemento esiste
        printf("-->%d", l.Head->Destinazione);
        l.Head = l.Head->Successivo; // Passo all'elemento successivo
    }
    printf("\n");
}

void printGrafo(grafo g) { // Stampa i collegamenti in un grafo
    for (size_t i = 0; i < g.NumeroVertici; i++) {
        printf("Vertice (%zu)", i);
        printLista(g.Vertici[i]);
    }
    printf("\n");
}

bool checkFilestream(FILE *stream) { // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return false;
}

void promptMenu(char *filename) {
    printf("Inserisci il nome del file (massimo %d caratteri): ", MAX_FILENAME);
    scanf("%s", filename);
}

int main() {
    char filename[MAX_FILENAME];
    promptMenu(filename);
    FILE *stream = fopen(filename, "r");
    checkFilestream(stream);
    grafo Grafo = parseGrafo(stream);
    printGrafo(Grafo);
    return 0;
}

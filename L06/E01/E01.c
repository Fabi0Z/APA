#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned int MAX_FILENAME = 40;

typedef struct Arco {
    unsigned int Partenza;
    unsigned int Destinazione;
} arco;

typedef struct Grafo {
    unsigned int NumeroVertici;
    unsigned int NumeroArchi;
    arco *Archi;
} grafo;

typedef struct GruppoVertici {
    unsigned int NumeroElementi;
    unsigned int *Array;
} gVertici;

grafo parseGrafo(FILE *stream) { // Restituisce un grafo letto da file
    grafo g;
    fscanf(stream, "%d %d", &g.NumeroVertici, &g.NumeroArchi);
    g.Archi = (arco *)calloc(sizeof(arco), g.NumeroArchi); // Alloco la memoria necessaria

    for (size_t i = 0; i < g.NumeroArchi; i++) {                                 // Per ogni arco
        fscanf(stream, "%d %d", &g.Archi[i].Partenza, &g.Archi[i].Destinazione); // Salvo i valori degli archi
    }
    return g;
}

void printArco(arco a) { // Stampa un arco
    printf("%d-->%d\n", a.Partenza, a.Destinazione);
}

void printGrafo(grafo g) { // Stampa un grafo
    printf("Ci sono %d vertici e %d archi:\n", g.NumeroVertici, g.NumeroArchi);
    for (size_t i = 0; i < g.NumeroArchi; i++) { // Per ogni arco
        printf("Arco (%zu): ", i);
        printArco(g.Archi[i]);
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

bool verificaVertexCover(gVertici *vertici, grafo *g) { // Ricevuto un array di nodi verifica che essi rappresentino un Vertex Cover
    bool arcoPresente = false;
    for (size_t i = 0; i < g->NumeroArchi; i++) { // Per ogni arco
        arcoPresente = false;
        for (size_t j = 0; j < vertici->NumeroElementi; j++) {                                                // Per ogni vertice
            if (g->Archi[i].Partenza == vertici->Array[j] || g->Archi[i].Destinazione == vertici->Array[j]) { // Se almeno un nodo è connesso ad almeno un capo dell'arco la condizione è verificata
                arcoPresente = true;
                break;
            }
        }
        if (arcoPresente == false) { // Se anche un solo arco non è presente l'insieme non è un Vertex Cover
            return false;
        }
    }
    return arcoPresente;
}

void printGroup(gVertici *group) { // Stampa un gruppo di vertici
    printf("{ %d", group->Array[0]);
    for (size_t i = 1; i < group->NumeroElementi; i++) { // Stampo il vertex cover
        printf(", %d", group->Array[i]);
    }
    printf(" }\n");
}

unsigned int powersetR(grafo *g, gVertici *Vertici, gVertici *Soluzione, unsigned int posizione, unsigned int start) { // Algoritmo per generare un powerset
    unsigned int count = 0;
    if (start >= Vertici->NumeroElementi) { // Se non ci sono più elementi
        Soluzione->NumeroElementi = posizione;
        if (verificaVertexCover(Soluzione, g)) { // Se la soluzione è un vertex cover
            printGroup(Soluzione);
            return 1;
        }
        return 0;
    }

    for (size_t i = start; i < Vertici->NumeroElementi; i++) { // Per ogni vertice rimanente
        Soluzione->Array[posizione] = Vertici->Array[i];
        count += powersetR(g, Vertici, Soluzione, posizione + 1, i + 1); // Ricorro incrementando il valore di start
    }

    count += powersetR(g, Vertici, Soluzione, posizione, Vertici->NumeroElementi); // Ricorro sull'ultimo elemento
    return count;
}

unsigned int generaVertexCover(grafo *g) { // Genera, tramite l'algoritmo di Er, un powerset dei nodi e stampa solo i gruppi verificati come vertex cover, restituisce il numero di vertex cover
    gVertici Vertici;
    gVertici Soluzione;
    Vertici.NumeroElementi   = g->NumeroVertici;
    Soluzione.NumeroElementi = 0;
    Vertici.Array            = (unsigned int *)calloc(Vertici.NumeroElementi, sizeof(unsigned int)); // Alloco la memoria per gli array
    Soluzione.Array          = (unsigned int *)calloc(Vertici.NumeroElementi, sizeof(unsigned int));

    for (size_t i = 0; i < g->NumeroVertici; i++) { // Per ogni vertice
        Vertici.Array[i] = i;                       // Scrivo il valore sull'array
    }
    return powersetR(g, &Vertici, &Soluzione, 0, 0);
}

int main() {
    char filename[MAX_FILENAME];
    promptMenu(filename);
    FILE *stream = fopen(filename, "r");
    checkFilestream(stream);
    grafo g = parseGrafo(stream);
    printGrafo(g);

    unsigned int nVertexCovers = generaVertexCover(&g);
    printf("Sono presenti %d Vertex Cover\n", nVertexCovers);
    return 0;
}

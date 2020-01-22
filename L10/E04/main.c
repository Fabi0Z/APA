#include "grafo.h"

char filename[] = "grafo.txt";

int main() {
    grafo g = parseGrafo(filename);
    creaListaAdiacenze(g);
    printGrafo(g);
    reorderVertexByName(g);
    puts("\n Ristampo il grafo riordinato\n");
    printGrafo(g);
    return 0;
}

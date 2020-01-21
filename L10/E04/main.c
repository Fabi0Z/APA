#include "grafo.h"

char filename[] = "grafo.txt";

int main() {
    grafo g = parseGrafo(filename);
    printGrafo(g);
    puts("\nCreo lista adiacenza\n");
    creaListaAdiacenze(g);
    printGrafo(g);
    return 0;
}

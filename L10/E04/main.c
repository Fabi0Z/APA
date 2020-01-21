#include "grafo.h"

char filename[] = "grafo.txt";

int main() {
    grafo g = parseGrafo(filename);
    printGrafo(g);
    return 0;
}

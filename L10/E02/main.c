#include "programma.h"
#include "sortlib.h"

// Restituisce true se l'elemento a ha valore minore o uguale al b
bool minorEqualValore(elemento a, elemento b) {
    return a->Valore <= b->Valore;
}

const uint8_t MAX_STRING = 150;

int main() {
    char filename[] = "elementi.txt";
    array elementi  = newArray((void *)&freeElemento, (void *)&parseElemento, (void *)&printElemento);
    parseArrayFromFile(elementi, filename, MAX_STRING);
    mergeSort(elementi, (void *)&minorEqualValore); // Ordino l'array
    printArray(elementi);

    programma p = generaMigliorProgramma(elementi, 10, 30);
    printProgramma(p);

    freeArray(elementi, true);
    return 0;
}

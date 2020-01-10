#include "programma.h"

const uint8_t MAX_STRING = 150;

bool max2(elemento a, elemento b, item unused) {
    return a->Valore <= b->Valore;
}

int main() {
    char filename[] = "elementi.txt";
    array elementi  = newArray((void *)&freeElemento, (void *)&parseElemento, (void *)&printElemento);
    parseArrayFromFile(elementi, filename, MAX_STRING);

    programma p = generaMigliorProgramma(elementi, 15, 30);
    printProgramma(p);

    freeProgramma(p);
    freeArray(elementi, true);
    return 0;
}

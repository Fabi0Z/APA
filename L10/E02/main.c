#include "programma.h"

const uint8_t MAX_STRING = 150;

int main() {
    char filename[] = "elementi.txt";
    array elementi  = creaArray((void *)&freeElemento, (void *)&parseElemento, (void *)&printElemento);
    parseArrayFromFile(elementi, filename, MAX_STRING);
    printArray(elementi);

    programma soluzione = creaProgramma();
    link head           = creaLink(NULL);

    generaDiagonale(elementi, soluzione->Diagonali[0], head, 0, 25);

    freeProgramma(soluzione);
    freeArray(elementi, true);
    return 0;
}

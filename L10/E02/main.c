#include "programma.h"

const uint8_t MAX_STRING = 150;

int main() {
    char filename[] = "elementi.txt";
    array elementi  = creaArray((void *)&freeElemento, (void *)&parseElemento, (void *)&printElemento);
    parseArrayFromFile(elementi, filename, MAX_STRING);
    printArray(elementi);

    programma soluzione = creaProgramma();
    diagonale massimo   = creaDiagonale();
    generaDiagonale(elementi, soluzione->Diagonali[0], massimo, 0, 25);
    printArray(massimo->Elementi);

    freeProgramma(soluzione);
    freeArray(elementi, true);
    return 0;
}

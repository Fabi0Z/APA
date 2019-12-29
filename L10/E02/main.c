#include "calcoloCombinatorio.h"
#include "programma.h"

const uint8_t MAX_STRING = 150;

int main() {
    char filename[] = "elementi.txt";
    array elementi  = creaArray((void *)&freeElemento, (void *)&parseElemento, (void *)&printElemento);
    parseArrayFromFile(elementi, filename, MAX_STRING);
    array soluzione = creaArray((void *)&freeElemento, (void *)&parseElemento, (void *)&printElemento);
    allocaArray(soluzione, elementi->ObjectsNumber);
    diposizioniRipetuteDefault(elementi, soluzione);
    freeArray(soluzione, false);
    freeArray(elementi, true);
    return 0;
}

#include "elemento.h"
#include "smartfunctions.h"

const uint8_t MAX_STRING = 150;

int main() {
    char filename[] = "elementi.txt";
    // arrayElemento elementi = parseElementoFromFile(filename);
    // printElemento(elementi->Array[0]);
    array elementi = parseFromFile(filename, MAX_STRING, (void *)&parseElemento);
    elementi->printArray(elementi, &printElemento);
    elementi->freeArray(elementi, &freeElemento);
    return 0;
}

#include "programma.h"

const uint8_t MAX_STRING = 150;

int main() {
    char filename[] = "elementi.txt";
    array elementi  = creaArray();
    elementi->parse(elementi, filename, MAX_STRING, (void *)&parseElemento);
    elementi->print(elementi, (void *)&printElemento);
    elementi->free(elementi, (void *)&freeElemento);
    return 0;
}

#include "smartfunctions.h"
#include "tessera.h"

int main(int argc, char const *argv[]) {
    FILE *tilesStream = smartFopen("data/tiles.txt", "r");
    unsigned int numeroTessere;
    fscanf(tilesStream, "%d\n", &numeroTessere);

    arrayTessera a = parseArrayTessera(tilesStream, numeroTessere);
    printArrayTessera(&a, stdout);
    return 0;
}

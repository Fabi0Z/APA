#include "scacchiera.h"
#include "smartfunctions.h"

int main(int argc, char const *argv[]) {
    FILE *tilesStream = smartFopen("data/tiles.txt", "r");
    unsigned int numeroTessere;
    fscanf(tilesStream, "%d\n", &numeroTessere);

    arrayTessera a = parseArrayTessera(tilesStream, numeroTessere);
    printArrayTessera(&a, stdout);

    FILE *boardStream = smartFopen("data/board.txt", "r");
    scacchiera s;
    parseScacchiera(&s, boardStream, &a);
    printCella(&s.Matrice[0][0], &a, stdout);
    return 0;
}

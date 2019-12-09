#include "scacchiera.h"
#include "smartfunctions.h"

int main(int argc, char const *argv[]) {
    FILE *tilesStream = smartFopen("data/tiles.txt", "r");
    unsigned int numeroTessere;
    fscanf(tilesStream, "%d\n", &numeroTessere);

    puts("Le tessere presenti sono:");
    arrayTessera a = parseArrayTessera(tilesStream, numeroTessere);
    printArrayTessera(&a, stdout);

    puts("\nLa scacchiera è:");
    FILE *boardStream = smartFopen("data/board.txt", "r");
    scacchiera s;
    parseScacchiera(&s, boardStream, &a);
    printScacchiera(&s, &a, stdout);
    return 0;
}

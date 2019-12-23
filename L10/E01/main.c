#include "collana.h"
#include "smartfunctions.h"
#include <inttypes.h>

const uint8_t MAX_FILENAME = 51;

void parseFromFile(char *filename) { // Esegue i vari test presenti in un file
    FILE *stream = smartFopen(filename, "r");
    unsigned int nTest, massima;
    fscanf(stream, "%u\n", &nTest);
    for (unsigned int i = 0; i < nTest; i++) { // Per ogni test
        char riga[MAX_FILENAME];
        fgets(riga, MAX_FILENAME - 1, stream);
        collana c = parseCollana(riga);
        printf("TEST #%d\n", i + 1);
        unsigned int lunghezza = maxCollana(c->Pietre);
        printf("Lunghezza massima: %d\n", lunghezza);
    }
    fclose(stream);
}

int main() {
    // char filename[MAX_FILENAME];
    // puts("Inserisci il nome del file:");
    // printf("==> ");
    char filename[51] = "e1_easy_test_set.txt";
    // fgets(filename, (MAX_FILENAME - 1), stdin);
    // sscanf(filename, "%s", filename);
    parseFromFile(filename);
    return 0;
}

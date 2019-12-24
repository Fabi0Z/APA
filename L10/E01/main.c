#include "memoizationMatrix.h"
#include "smartfunctions.h"

const uint8_t MAX_FILENAME = 51;

// Calcola le lunghezze delle collane in un array
void calcolaLunghezze(arrayCollane a) {
    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni collana
        a->Array[i]->LunghezzaMassima = maxCollana(a->Array[i]);
    }
}

int main() {
    char filename[MAX_FILENAME];
    puts("Inserisci il nome del file:");
    printf("==> ");
    fgets(filename, (MAX_FILENAME - 1), stdin);
    sscanf(filename, "%s", filename);
    FILE *stream = smartFopen(filename, "r");

    arrayCollane array = parseArrayCollane(stream); // Leggo le collane
    calcolaLunghezze(array);                        // Calcolo le lunghezze
    printArrayCollane(array);                       // Stampo le collane
    return 0;
}

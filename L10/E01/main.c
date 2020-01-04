#include "array.h"
#include "memoizationMatrix.h"

const unsigned int MAX_STRING = 50;

// Calcola le lunghezze delle collane in un array
void calcolaLunghezze(array a) {
    for (unsigned int i = 0; i < a->ObjectsNumber; i++) { // Per ogni collana
        collana tmp           = a->Objects[i];
        tmp->LunghezzaMassima = maxCollana(a->Objects[i]);
    }
}

int main() {
    char filename[MAX_STRING + 1];
    puts("Inserisci il nome del file:");
    printf("==> ");
    fgets(filename, MAX_STRING, stdin);
    sscanf(filename, "%s", filename);

    array collane = creaArray(NULL, (void *)&parseCollana, (void *)&printCollana);
    parseArrayFromFile(collane, filename, MAX_STRING);
    calcolaLunghezze(collane); // Calcolo le lunghezze
    printArray(collane);
    return 0;
}

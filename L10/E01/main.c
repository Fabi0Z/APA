#include "memoizationMatrix.h"
#include "smartfunctions.h"
#include <inttypes.h>

const uint8_t MAX_FILENAME = 51;

// Calcola le lunghezze delle collane in un array
void calcolaLunghezze(arrayCollane a) {
    // Creo le matrice di memoizzazione
    memoizationMatrix matrici[totale];    
    for (uint8_t i = 0; i < totale; i++) { // Per ogni tipo di pietra
        matrici[i] = creaMemoizationMatrix();
        calcolaDimensioniMatrice(a, matrici[i]);
        allocaMemoizationMatrix(matrici[i]);
    }

    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni collana
        a->Array[i]->LunghezzaMassima = maxCollana(a->Array[i]->Pietre, matrici);
    }
}

int main() {
    // char filename[MAX_FILENAME];
    // puts("Inserisci il nome del file:");
    // printf("==> ");
    char filename[51] = "e1_easy_test_set.txt";
    // fgets(filename, (MAX_FILENAME - 1), stdin);
    // sscanf(filename, "%s", filename);
    FILE *stream = smartFopen(filename, "r");

    arrayCollane array = parseArrayCollane(stream); // Leggo le collane
    calcolaLunghezze(array);                        // Calcolo le lunghezze
    printArrayCollane(array);                       // Stampo le collane
    return 0;
}

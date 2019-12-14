#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Array {
    unsigned int *array;
    unsigned int elementi;
} array;

void printLIS(array *valori, array *posizioni, unsigned int index) {
    if (index == 0) {
        printf("\n");
        return;
    }

    printf("%d ", valori->array[index - 1]);
    index = posizioni->array[index - 1];
    printLIS(valori, posizioni, index);
}

unsigned int LISS(array *valori, array *posizioni, array *LIS) {
    unsigned int precedente      = 0;
    unsigned int precedenteIndex = 0;
    unsigned int LISAttuale      = 1;
    for (unsigned int i = 0; i < valori->elementi; i++) { // Per ogni elemento
        if (valori->array[i] <= precedente) {    // Se il valore interrompe la sequenza
            // Inserisco i valori di interruzione
            posizioni->array[i] = 0;
            LIS->array[i]       = 1;
        } else {
            // Proseguo l'incremento della LIS
            posizioni->array[i] = precedenteIndex;
            precedenteIndex     = i + 1;
            LIS->array[i]       = LISAttuale++;
        }
        precedente = valori->array[i];
    }

    return precedenteIndex; // Restituisco l'ultimo valore della LIS
}

unsigned int main() {
    array valori;
    valori.elementi = 7;
    unsigned int temp[]      = {6, 3, 5, 2, 7, 8, 1};
    valori.array    = temp;

    array LIS, posizioni;
    LIS.elementi       = valori.elementi;
    posizioni.elementi = valori.elementi;
    LIS.array          = (unsigned int *)calloc(valori.elementi, sizeof(unsigned int));
    posizioni.array    = (unsigned int *)calloc(valori.elementi, sizeof(unsigned int));

    unsigned int indice = LISS(&valori, &posizioni, &LIS);
    printLIS(&valori, &posizioni, indice);
    return 0;
}

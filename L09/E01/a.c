#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Array {
    int *array;
    int elementi;
} array;

void printLIS(array *valori, array *posizioni, int index) {
    if (index == -1) {
        printf("\n");
        return;
    }

    printf("%d ", valori->array[index]);
    index = posizioni->array[index];
    printLIS(valori, posizioni, index);
}

int LISS(array *valori, array *posizioni, array *LIS) {
    int precedente      = INT_MIN;
    int precedenteIndex = -1;
    int LISAttuale      = 1;
    for (int i = 0; i < valori->elementi; i++) { // Per ogni elemento
        if (valori->array[i] <= precedente) {    // Se il valore interrompe la sequenza
            // Inserisco i valori di interruzione
            posizioni->array[i] = -1;
            LIS->array[i]       = 1;
        } else {
            // Proseguo l'incremento della LIS
            posizioni->array[i] = precedenteIndex;
            precedenteIndex     = i;
            LIS->array[i]       = LISAttuale++;
        }
        precedente = valori->array[i];
    }

    return precedenteIndex; // Restituisco l'ultimo valore della LIS
}

int main() {
    array valori;
    valori.elementi = 7;
    int temp[]      = {6, 3, 5, 2, 7, 8, 1};
    valori.array    = temp;

    array LIS, posizioni;
    LIS.elementi       = valori.elementi;
    posizioni.elementi = valori.elementi;
    LIS.array          = (int *)calloc(valori.elementi, sizeof(int));
    posizioni.array    = (int *)calloc(valori.elementi, sizeof(int));

    int indice = LISS(&valori, &posizioni, &LIS);
    printLIS(&valori, &posizioni, indice);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_NUMBERS = 30;

int readArray(int V[MAX_NUMBERS]) { // Leggi un array come input da tastiera e ne restituisce l'effettiva lunghezza
    int maxString = 6*MAX_NUMBERS + MAX_NUMBERS;
    char input[maxString];
    fgets(input, maxString, stdin);

    int i = 0;
    int result;
    char temp[maxString];
    do {
        result = sscanf(input, "%d %[^\n]", &V[i], &temp);
        memset(input, 0, maxString*sizeof(char));
        strcpy(input, temp);
        i++;
    } while (result == 2);

    return i;
}

void stampaVettore(int length, int array[length]) { // Stampa il vettore dato di dimensione length
    for (size_t i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int ruotaVettore(int length, int V[length], int posizioni) {
    int spostamenti = abs(posizioni)%length;
    if (spostamenti == 0) {
        return spostamenti;
    }
    
    int direzione, tempArray[length];
    direzione = posizioni > 0 ? 1 : -1;

    /*  Se la rotazione è positiva (verso destra) lo spostamento rimane invariato,
        altrimenti esso diventa lunghezza-posizioni ovvero l'equivalente in spostamenti
        a destra degli spostamenti a sinistra   */
    spostamenti = direzione > 0 ? spostamenti : length + (spostamenti*direzione);

    // Rotazione del vettore a destra
    size_t i = 0;
    for (i; i + spostamenti < length; i++) {
        tempArray[i + spostamenti] = V[i];
    }
    for (size_t j = 0; j < spostamenti; j++) {
        tempArray[j] = V[j + (length - spostamenti)];
    }
    
    memcpy(V, tempArray, length*sizeof(int));
    return spostamenti;
}

int main() {
    int V[MAX_NUMBERS];
    memset(V, 0, MAX_NUMBERS*sizeof(int));

    printf("Scrivi il vettore (max 30 cifre): ");
    int lunghezza = readArray(V);
    int array[lunghezza];
    memcpy(array, V, lunghezza*sizeof(int)); // Copio in un vettore con N celle esatte
    

    printf("Il vettore è lungo %d cifre\n", lunghezza);
    printf("Il vettore è: ");
    stampaVettore(lunghezza, array);

    int rotazioni = 0;
    do {
        printf("Di quante posizioni vorresti ruotare il vettore?: ");
        scanf("%d", &rotazioni);
        ruotaVettore(lunghezza, array, rotazioni);
        printf("Il nuovo vettore è: ");
        stampaVettore(lunghezza, array);
    } while (rotazioni != 0);
    printf("\n");
}
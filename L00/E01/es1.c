#include <stdio.h>
#include <string.h>
#include <error.h>

const int MAX_NUMBERS = 30;

int readArray(int *V) {
    int maxString = 6*MAX_NUMBERS;
    char input[maxString];
    fgets(input, maxString, stdin);

    int length = 0;
    int result;
    char temp[maxString];
    do {
        result = sscanf(input, "%d %[^\n]", &V[length], &temp);
        memset(input, 0, maxString*sizeof(char));
        strcpy(input, temp);
        length++;
    } while (result == 2);

    return length; // restituisci il numero di dati inseriti
}

int findMaxPosition(int zeros, int zeroArray[zeros], int maxIndex[zeros], int *maxFounds) { // Trova i sottoarray di dimensione massima e ne salva gli indici
    memset(maxIndex, -1, zeros*sizeof(int));
    int compareIndex, max = 0;
    for (size_t i = 0; i < zeros; i++) {
        int length = zeroArray[i] - compareIndex;
        max = length > max ? length : max;
        compareIndex = zeroArray[i] + 1;
    }

    int maxIndexFound = 0;
    compareIndex = 0;
    for (size_t i = 0; i < zeros; i++) {
        int length = zeroArray[i] - compareIndex;
        max = length > max ? length : max;
        if (length == max) {
            maxIndex[maxIndexFound] = compareIndex;
            maxIndexFound++;
        }
        compareIndex = zeroArray[i] + 1;
    }
    
    *maxFounds = maxIndexFound;
    return max;    
}

void findZero(int numberOfZeros, int size, int V[size], int zeros[numberOfZeros]) { // Trova gli indici degli zeri e li mette in un array apposito
    int zerosFound = 0;
    for (size_t i = 0; i < size; i++) {
        if (V[i] == 0) {
            zeros[zerosFound] = i;
            zerosFound++;
        }
    }
}

int countValue(int size, int V[size], int value) { // Conta quanti zeri sono presenti in un array
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        count += V[i] == value ? 1 : 0;
    }
    return count;
}

int main() {
    int tempV[MAX_NUMBERS]; // array temporaneo per leggere il vettore da tastiera
    puts("Inserisci il vettore:");
    int numbers = readArray(tempV); // Salvo quanti numeri son stati digitati
    int array[numbers]; // Dichiaro l'array reale digitato
    memcpy(array, tempV, numbers*sizeof(int)); // Copio i dati nell'array reale
    int zeros = countValue(numbers, array, 0); // Conto quanti zeri sono presenti all'interno
    int nonZero = numbers - zeros; // Calcolo quante cifre non sono 0
    int zeroArray[zeros]; // Creo l'array contenente gli indici dei vari zeri
    findZero(zeros, numbers, array, zeroArray); // Trovo gli indici degli zeri

    int maxIndex[zeros];
    int subArrayFounds;
    int maxValue = findMaxPosition(zeros, zeroArray, maxIndex, &subArrayFounds); // Trovo gli indici degli array di dimensione massima

    if (zeros > 0) {
        printf("Il vettore è lungo %d caratteri\nSono stati trovati %d zeri agli indici:", numbers, zeros);
        for (size_t i = 0; i < zeros; i++) {
            printf(" %d", zeroArray[i]);
        }
        printf("\n");
    } else {
        puts("Non è stato trovato alcuno zero, l'array inserito è quello di dimensione massima");
        exit(0);
    }

    printf("Sono stati trovati %d array di dimensione massima (%d) agli indici:", subArrayFounds, maxValue);
    for (size_t i = 0; i < subArrayFounds; i++) {
        printf(" %d", maxIndex[i]);
    }
    printf("\n");
    puts("Gli array di dimensione massima sono:");
    for (size_t i = 0; i < subArrayFounds; i++) {
        for (size_t j = 0; j < maxValue; j++) {
            printf("%d ", array[maxIndex[i] + j]);
        }
        printf("\n");
    }
    
    
    return 0;
}
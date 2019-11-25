#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

const int MAX_ARRAY_length = 20;

void readNumber(FILE *stream, int *righe, int *colonne) { // Leggi quante parole sono presenti all'interno del file
    fscanf(stream, "%d %d", righe, colonne);
}

int checkFilestream(FILE *stream) {  // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return 0;
}

void getMatrice(FILE *stream, int righe, int colonne, int matrice[righe][colonne]) {
    for (size_t i = 0; i < righe; i++) {
        for (size_t j = 0; j < colonne; j++) {
            fscanf(stream, "%d", &matrice[i][j]);
        }
    }
}

void printMatrice(int righe, int colonne, int matrice[righe][colonne]) {
    for (size_t i = 0; i < righe; i++) {
        for (size_t j = 0; j < colonne; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}

int sommaMatrice(int size, int matrice[size][size]) {
    int conto = 0;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            conto += matrice[i][j];
        } 
    }
    return conto;
}

void printSubmatrix(int righe, int colonne, int quadrata, int matrice[righe][colonne]) {
    int maxIndex[2] = {0, 0};
    int max = INT_MIN;
    for (size_t i = 0; i <= (righe - quadrata); i++) {
        for (size_t j = 0; j <= (colonne - quadrata); j++) {
            int tempMatrix[quadrata][quadrata];
            for (size_t i2 = 0; i2 < quadrata; i2++) {
                for (size_t j2 = 0; j2 < quadrata; j2++) {
                    tempMatrix[i2][j2] = matrice[i+i2][j+j2];
                }
            }
            
            int somma = sommaMatrice(quadrata, tempMatrix);
            if (somma > max) {
                maxIndex[0] = i;
                maxIndex[1] = j;
                max = somma;
            }

            printf("Sottomatrice (%d,%d) con sommatoria %d:\n", i, j, somma);
            printMatrice(quadrata, quadrata, tempMatrix);
        }
    }

    printf("La sottomatrice di dimensione massima ha sommatoria %d ed è quella di posizione (%d,%d):\n", max, maxIndex[0], maxIndex[1]);
    for (size_t i = 0; i < quadrata; i++) {
        for (size_t j = 0; j < quadrata; j++) {
            printf("%d ", matrice[maxIndex[0]+i][maxIndex[1]+j]);
        }
        printf("\n");
    }
}

int getSubmatrix(int min) {
    printf("Inserisci un valore compreso tra 1 e %d: ", min);
    int submatrixSize;
    scanf("%d", &submatrixSize);
    if (submatrixSize > min || submatrixSize < 1) {
        exit(0);
    }
    
    return submatrixSize;
}

int main() {
    // Leggo il nome del file
    printf("Scrivi il nome del file: ");
    char filename[MAX_ARRAY_length];
    scanf("%s", &filename);  

    
    FILE *f = fopen(filename, "r");
    checkFilestream(f);
    int righe, colonne;
    readNumber(f, &righe, &colonne);

    int matrix[righe][colonne];
    memset(matrix, 0, righe*colonne*sizeof(int)); // Creo la matrice delle dimensioni corrette
    getMatrice(f, righe, colonne, matrix);

    printf("La matrice ha dimensioni %dx%d ed è:\n", righe, colonne);
    printMatrice(righe, colonne, matrix);

    while (1) {
        int min = righe > colonne ? righe : colonne;
        int submatrixSize = getSubmatrix(min);
        printf("Le sottomatrici sono:\n");
        printSubmatrix(righe, colonne, submatrixSize, matrix);
    }
}
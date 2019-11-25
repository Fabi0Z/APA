#include <error.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { bianco,
               nero } colore; // Dichiaro il tipo colore

bool checkFilestreamErrors(FILE *stream) { // Check if a FileStream it's NULL, if it's NULL print
                                           // a error message and exit, otherwise return false
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return false;
}

int **malloc2dR(size_t *righe, size_t *colonne) { // Effettua il parse della matrice e ne restituisce il puntatore
    FILE *stream = fopen("mat.txt", "r");         // Apro il file
    checkFilestreamErrors(stream);                // Controllo che l'apertura sia andata a buon fine
    fscanf(stream, "%zu %zu", righe, colonne);    // Leggo il numero di righe e di colonne

    int **matrix = (int **)malloc(sizeof(int) * (*righe));   // Alloco la memoria per le righe
    for (size_t i = 0; i < *righe; i++) {                    // Per ogni riga
        matrix[i] = (int *)malloc(sizeof(int) * (*colonne)); // Alloco memoria per le colonne
        for (size_t j = 0; j < *colonne; j++) {              // Per ogni colonna
            fscanf(stream, "%d", &matrix[i][j]);             // Scrivo i dati sulla cella
        }
    }

    fclose(stream); // Chiudo il filestream
    return matrix;
}

size_t elementiMassimi(size_t elementi) { // Restituisce il numero massimo di elementi dello stesso colore in un array di lunghezza n
    return (elementi / 2) + (elementi % 2);
}

void separa(int **matrice, size_t righe, size_t colonne, int ***bianchiOut, int ***neriOut) {
    int **bianchi, **neri;                          // Dichiaro le variabili puntatori
    bianchi = (int **)calloc(sizeof(int *), righe); // Alloco memoria per le righe
    neri    = (int **)calloc(sizeof(int *), righe);

    size_t dimensioneMassima = elementiMassimi(colonne); // La lunghezza massima nel caso di elementi dispari
    colore inizioRiga        = bianco;                   // Variabile che tiene conto del colore a inizio riga

    for (size_t i = 0; i < righe; i++) { // Per ogni riga
        colore cella = inizioRiga;       // Variabile che tiene conto del colore della prima cella

        size_t colonneBianche = inizioRiga == bianco ? dimensioneMassima : dimensioneMassima - 1; // Se la riga inizia per una cella bianca il numero di elementi nella colonna la dimensione massima
        size_t colonneNere    = colonne - colonneBianche;                                         // I restanti elementi sono la quantità di elementi neri nella colonna

        size_t bianchiC = 0; // Contatori per gli indici delle matrici bianche e nere
        size_t neriC    = 0;

        bianchi[i] = (int *)calloc(sizeof(int), colonneBianche); // Alloco memoria per le colonne bianche
        neri[i]    = (int *)calloc(sizeof(int), colonneNere);    // Alloco memoria per le colonne nere

        for (size_t j = 0; j < colonne; j++) {        // Per ogni colonna
            if (cella == bianco) {                    // Se la cella è bianca
                bianchi[i][bianchiC] = matrice[i][j]; // Assegno il valore alla matrice bianca
                bianchiC++;
            } else {                            // Se la cella è nera
                neri[i][neriC] = matrice[i][j]; // Assegno il valore alla matrice bianca
                neriC++;
            }
            cella = cella == bianco ? nero : bianco; // Scambio il colore
        }
        inizioRiga = inizioRiga == bianco ? nero : bianco; // Scambio il colore
    }

    *bianchiOut = bianchi;
    *neriOut    = neri;
}

void printSottoScacchiera(int **matrice, size_t righe, size_t colonne, colore coloreScacchiera) {
    /* Disegna una scacchiera di soli bianchi o soli neri a partire dalle dimensioni originali
       della scacchiera e da una matrice contenente solo i bianchi o solo i neri
       infine dealloca le matrici dei singoli colori */

    size_t colonneMassime = elementiMassimi(colonne); // Scrivo il numero di colonne massime

    for (size_t i = 0; i < righe; i++) { // Per ogni riga
        // Se stiamo iniziando da una cella bianca indico il numero di colonne corrispettivo
        size_t nColonne = coloreScacchiera == bianco ? colonneMassime : colonneMassime - 1;

        if (coloreScacchiera == nero) { // Se inizio su una cella nera stampo lo spaziatore prima
            printf("* ");
        }
        for (size_t j = 0; j < nColonne; j++) { // Per ogni colonna
            printf("%d ", matrice[i][j]);       // Stampo il valore della cella
            if (j + 1 < nColonne) {             // Se non sono sull'ultima cella stampo lo spaziatore
                printf("* ");
            }
        }
        if (coloreScacchiera == nero) { // Se inizio su una cella nera stampo lo spaziatore dopo
            printf("* ");
        }
        printf("\n");
        coloreScacchiera = coloreScacchiera == bianco ? nero : bianco; // Scambio il colore
        free(matrice[i]); // Dealloco la memoria
    }
    free(matrice); // Dealloco la memoria
}

void printScacchiera(int **matrix, size_t righe, size_t colonne) { // Stampa una scacchiera a video
    for (size_t i = 0; i < righe; i++) {                           // Per ogni riga
        for (size_t j = 0; j < colonne; j++) {                     // Per ogni colonna
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]) {
    size_t righe, colonne;
    int **matrix = malloc2dR(&righe, &colonne);
    int **bianchi, **neri;

    puts("Scacchiera originale:");
    printScacchiera(matrix, colonne, righe);
    printf("\n");

    separa(matrix, righe, colonne, &bianchi, &neri);
    puts("Scacchiera bianca:");
    printSottoScacchiera(bianchi, righe, colonne, bianco);
    printf("\n");
    puts("Scacchiera nera:");
    printSottoScacchiera(neri, righe, colonne, nero);

    return 0;
}

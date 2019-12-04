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

    // fclose(stream); // Chiudo il filestream
    return matrix;
}

size_t maxElementiMonocolore(size_t righe, size_t colonne) { // Restituisce il numero di elementi dello stesso colore in una scacchiera
    return ((righe * colonne) / 2) + ((righe * colonne) % 2);
}

void separa(int **matrice, size_t righe, size_t colonne, int **bianchiOut, int **neriOut) {
    int *bianchi, *neri; // Dichiaro le variabili puntatori
    size_t dimensioneArray = maxElementiMonocolore(righe, colonne);

    bianchi = (int *)calloc(sizeof(int), dimensioneArray); // Alloco memoria per le righe
    if (dimensioneArray % 2 == 1) {
        neri = (int *)calloc(sizeof(int), dimensioneArray - 1);
    } else {
        neri = (int *)calloc(sizeof(int), dimensioneArray);
    }

    colore inizioRiga = bianco; // Variabile che tiene conto del colore a inizio riga
    size_t nBianche = 0, nNere = 0;

    for (size_t i = 0; i < righe; i++) {             // Per ogni riga
        colore cella = inizioRiga;                   // Variabile che tiene conto del colore della prima cella
        for (size_t j = 0; j < colonne; j++) {       // Per ogni colonna
            if (cella == bianco) {                   // Se la cella è bianca
                bianchi[nBianche++] = matrice[i][j]; // Assegno il valore vettore dei bianchi
            } else {                                 // Se la cella è nera
                neri[nNere++] = matrice[i][j];       // Assegno il valore al vettori dei neri
            }
            cella = cella == bianco ? nero : bianco; // Scambio il colore
        }
        inizioRiga = inizioRiga == bianco ? nero : bianco; // Scambio il colore
    }

    *bianchiOut = bianchi;
    *neriOut    = neri;
}

void printSottoScacchiera(int *array, size_t righe, size_t colonne, colore coloreArray) {
    /* Disegna una scacchiera di soli bianchi o soli neri a partire dalle dimensioni originali
       della scacchiera e da una matrice contenente solo i bianchi o solo i neri
       infine dealloca le matrici dei singoli colori */
    size_t posizione = 0;
    bool spaziatore  = coloreArray == nero;

    for (size_t i = 0; i < righe; i++) {       // Per ogni riga
        for (size_t j = 0; j < colonne; j++) { // Per ogni colonna
            if (spaziatore) {
                printf("* ");
            } else {
                printf("%d ", array[posizione++]); // Stampo il valore della cella
            }
            spaziatore = !spaziatore;
        }
        printf("\n");
    }
    free(array); // Dealloco la memoria
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
    int *bianchi, *neri;

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

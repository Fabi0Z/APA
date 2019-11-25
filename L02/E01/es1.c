#include <stdio.h>

typedef struct Regione {
    int Inizio[2], FineX, FineY;
} regione;

int altezzaRegione(regione rettangolo) {
    int y = rettangolo.FineY + 1 - rettangolo.Inizio[0];
    return y;
}

int larghezzaRegione(regione rettangolo) {
    int x = rettangolo.FineX + 1 - rettangolo.Inizio[1];
    return x;
}

int areaRegione(regione rettangolo) {
    return larghezzaRegione(rettangolo) * altezzaRegione(rettangolo);
}

int maxAltezzaRegioni(int numeroRegioni, regione regioni[numeroRegioni]) {
    int max = 0;
    for (size_t i = 0; i < numeroRegioni; i++) {
        max = altezzaRegione(regioni[i]) > max ? altezzaRegione(regioni[i]) : max;
    }
    return max;
}

int maxLarghezzaRegioni(int numeroRegioni, regione regioni[numeroRegioni]) {
    int max = 0;
    for (size_t i = 0; i < numeroRegioni; i++) {
        max = larghezzaRegione(regioni[i]) > max ? larghezzaRegione(regioni[i]) : max;
    }
    return max;
}

int maxAreaRegioni(int numeroRegioni, regione regioni[numeroRegioni]) {
    int max = 0;
    for (size_t i = 0; i < numeroRegioni; i++) {
        max = areaRegione(regioni[i]) > max ? areaRegione(regioni[i]) : max;
    }
    return max;
}

void getMatrixSize(FILE *stream, int *righe, int *colonne) { // Leggo le dimensioni della matrice
    fscanf(stream, "%d %d", righe, colonne);
}

int checkFilestream(FILE *stream) {  // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return 0;
}

void leggiMatrice(FILE *stream, int righe, int colonne, int matrice[righe][colonne]) {
    for (size_t i = 0; i < righe; i++) {
        for (size_t j = 0; j < colonne; j++) {
            fscanf(stream, "%d", &matrice[i][j]);
        }
    }
    fclose(stream);
}

void printMatrice(int righe, int colonne, int matrice[righe][colonne]) {
    for (size_t i = 0; i < righe; i++) {
        for (size_t j = 0; j < colonne; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}

FILE* apriFile() { // Chiede quale file aprire e ne restituisce lo stream
    printf("Scrivi il nome del file che vuoi aprire: ");
    char filename[20];
    memset(filename, 0, 20*sizeof(char));
    scanf("%s", filename);
    FILE *stream = fopen(filename, "r");
    checkFilestream(stream);
    
    return stream;
}

int contaRegioni(int righe, int colonne, int matrice[righe][colonne]) {
    int regioniTrovate = 0;
    for (size_t i = 0; i < righe; i++) {
        for (size_t j = 0; j < colonne; j++) {
            int flag_i = 0;
            int flag_j = 0; // Flag per controllare che la cella sia un inizio di matrice
            if (matrice[i][j]) { // Mi fermo se trovo una cella nera
                if (i != 0) { // Controllo che la cella non sia subito sotto il margine 
                    flag_i += matrice[i-1][j] ? 0 : 1; // Se la cella sopra è bianca la condizione per i è verificata
                } else {
                    flag_i++; // Se è sotto il margine la condizione per j è verificata
                }
                
                if (j != 0) { // Controllo che la cella non sia subito a destra del margine 
                    flag_j += matrice[i][j-1] ? 0 : 1; // Se la cella a sinistra è bianca la condizione per j è verificata
                } else {
                    flag_j++; // Se è sotto il margine la condizione per j è verificata
                }

                if (flag_i + flag_j == 2) { // Se entrambi i flag sono validi ho trovato la prima cella di una regione
                    regioniTrovate++;
                }
            }
        }
    }
    return regioniTrovate;
}

void leggiRegioni(int righe, int colonne, int nRegioni, int matrice[righe][colonne], regione regioni[nRegioni]) {
    int regioniTrovate = 0;
    for (size_t i = 0; i < righe; i++) {
        for (size_t j = 0; j < colonne; j++) {
            int flag_i = 0;
            int flag_j = 0; // Flag per controllare che la cella sia un inizio di matrice
            if (matrice[i][j]) { // Mi fermo se trovo una cella nera
                if (i != 0) { // Controllo che la cella non sia subito sotto il margine 
                    flag_i += matrice[i-1][j] ? 0 : 1; // Se la cella sopra è bianca la condizione per i è verificata
                } else {
                    flag_i++; // Se è sotto il margine la condizione per j è verificata
                }
                
                if (j != 0) { // Controllo che la cella non sia subito a destra del margine 
                    flag_j += matrice[i][j-1] ? 0 : 1; // Se la cella a sinistra è bianca la condizione per j è verificata
                } else {
                    flag_j++; // Se è sotto il margine la condizione per j è verificata
                }

                if (flag_i + flag_j == 2) { // Se entrambi i flag sono validi ho trovato la prima cella di una regione
                    regioni[regioniTrovate].Inizio[0] = i; // Salvo gli indici dell'inizio della regione
                    regioni[regioniTrovate].Inizio[1] = j;
                    
                    int i_2 = i;
                    while (matrice[i_2 + 1][j] && i_2 + 1 < colonne) i_2++; // Controllo quante celle nere consecutive trovo percorrendo le righe
                    regioni[regioniTrovate].FineY = i_2;

                    int j_2 = j;
                    while (matrice[i][j_2 + 1] && j_2 + 1 < righe) j_2++; // Controllo quante celle nere consecutive trovo percorrendo le colonne
                    regioni[regioniTrovate].FineX = j_2;

                    regioniTrovate++;
                }
            }
        }
    }
}


int main(int argc, char const *argv[]) {
    FILE *input = apriFile(); // Apro il file
    int righe, colonne;
    getMatrixSize(input, &righe, &colonne); // Leggo la dimensione della matrice
    int matrice[righe][colonne];
    printf("La dimensione della matrice è %dx%d\n", righe, colonne);
    leggiMatrice(input, righe, colonne, matrice); // Leggo la matrice
    puts("Il contenuto della matrice è"); // Stampo il contenuto della matrice
    printMatrice(righe, colonne, matrice);

    int regioniTrovate = contaRegioni(righe, colonne, matrice);
    printf("\nSono presenti %d regioni:\n", regioniTrovate);
    regione regioni[regioniTrovate];
    leggiRegioni(righe, colonne, regioniTrovate, matrice, regioni);

    int altezzaMassima = maxAltezzaRegioni(regioniTrovate, regioni);
    int larghezzaMassima = maxLarghezzaRegioni(regioniTrovate, regioni);
    int areaMassima = maxAreaRegioni(regioniTrovate, regioni);

    printf("\nLe regioni più larghe sono quelle di larghezza %d e iniziano agli indici: ", larghezzaMassima);
    for (size_t i = 0; i < regioniTrovate; i++) {
        if (larghezzaRegione(regioni[i]) == larghezzaMassima) {
            printf("(%d, %d) ", regioni[i].Inizio[0], regioni[i].Inizio[1]);
        }
    }

    printf("\nLe regioni più alte sono quelle di altezza %d e iniziano agli indici: ", altezzaMassima);
    for (size_t i = 0; i < regioniTrovate; i++) {
        if (altezzaRegione(regioni[i]) == altezzaMassima) {
            printf("(%d, %d) ", regioni[i].Inizio[0], regioni[i].Inizio[1]);
        }
    }

    printf("\nLe regioni più grandi sono quelle di area %d e iniziano agli indici: ", areaMassima);
    for (size_t i = 0; i < regioniTrovate; i++) {
        if (areaRegione(regioni[i]) == areaMassima) {
            printf("(%d, %d) ", regioni[i].Inizio[0], regioni[i].Inizio[1]);
        }
    }
    printf("\n");

    puts("\nLe dimensioni di tutte le regioni sono:");
    for (size_t i = 0; i < regioniTrovate; i++) {
        int size = areaRegione(regioni[i]);
        printf("- Regione n° %d iniziante all'indice (%d, %d): %d\n", i, regioni[i].Inizio[0], regioni[i].Inizio[1], size);
    }

    
    return 0;
}

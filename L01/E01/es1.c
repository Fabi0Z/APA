#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_SQUADRE = 20;
const int MAX_GIORNATE = 20;

int checkFilestream(FILE *stream) {  // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return 0;
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

void dimensioniMatrice(FILE *stream, int *squadre, int *giornate) {
    char riga[MAX_GIORNATE*2], temp[2*MAX_GIORNATE];
    memset(riga, 0, 2*MAX_GIORNATE*sizeof(char));
    memset(temp, 0, 2*MAX_GIORNATE*sizeof(char));

    fgets(riga, 2*MAX_GIORNATE, stream);
    int j, tempInt = 0;
    while (sscanf(riga, "%d %[^\n]", &tempInt, temp) == 2) { // Conto le giornate
        memcpy(riga, temp, 2*(MAX_GIORNATE - j));
        j++;
    }

    int i = 1;
    while (fgets(riga, 2*MAX_SQUADRE, stream) != NULL) i++; // Conto le squadre

    *squadre = i;
    *giornate = j;
}

void leggiMatrice(FILE *stream, int squadre, int giornate, int matrice[squadre][giornate]) {
    char riga[giornate*2];
    memset(riga, 0, 2*giornate*sizeof(char));

    int i = 0;
    while (fgets(riga, 2*giornate, stream) != NULL) {
        int j = 0;
        char temp[2*(squadre - j)];
        memset(temp, 0, 2*(squadre - j)*sizeof(char));

        while (sscanf(riga, "%d %[^\n]", &matrice[i][j], temp) == 2) {
            memset(riga, 0, 2*squadre*sizeof(char));
            memcpy(riga, temp, 2*(squadre - j));
            j++;
        }

        memset(riga, 0, 2*squadre*sizeof(char));
        i++;
    }
}

int main() {
    int squadre, giornate; // Dichiaro la matrice contentente i dati del campionato

    FILE *input = apriFile(); // Apro il file indicato dall'utente
    dimensioniMatrice(input, &squadre, &giornate);
    int campionato[squadre][giornate];
    leggiMatrice(input, campionato); // Copio i dati del file su una matrice
    return 0;
}
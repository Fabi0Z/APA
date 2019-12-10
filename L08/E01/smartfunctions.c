#include "smartfunctions.h"

// Stampa un "Premi invio per continuare..."
void premiPerContinuare() {
    puts("Premi invio per continuare...");
    getchar();
    getchar();
}

// Controlla errori di apertura del file
bool checkFilestream(FILE *stream) {
    return stream == NULL ? false : true;
}

// Apre in maniera sicura un file, interrompe il programma se non è possibile aprirlo
FILE *smartFopen(char *filename, char *mode) {
    FILE *f = fopen(filename, mode);
    if (checkFilestream(f)) {
        return f;
    }
    printf("Errore d'apertura per il file %s\n", filename);
    exit(1);
    return NULL;
}
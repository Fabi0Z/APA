#include "smartfunctions.h"

// Stampa un "Premi invio per continuare..."
void premiPerContinuare() {
    puts("Premi invio per continuare...");
    getchar();
    getchar();
}

// Controlla errori di apertura del file
bool checkFilestream(FILE *stream) {
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return true;
}

// Apre in maniera sicura un file, interrompe il programma se non è possibile aprirlo
FILE *smartFopen(char *filename, char *mode) {
    FILE *f = fopen(filename, mode);
    return checkFilestream(f) ? f : NULL;
}
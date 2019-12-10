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
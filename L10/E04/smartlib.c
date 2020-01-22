#include "smartlib.h"

// Controlla errori di apertura del file
bool checkFilestream(FILE *stream) {
    return stream == NULL ? false : true;
}

// Conta il numero di righe di un file
unsigned int countNumberOfLines(char *filename) {
    FILE *stream       = smartFopen(filename, "r");
    unsigned int lines = 0;
    char c, precedente;
    precedente = EOF;
    for (c = getc(stream); c != EOF; precedente = c, c = getc(stream))
        if (c == '\n') {
            lines++;
        }
    lines += precedente != '\n' ? 1 : 0;
    fclose(stream);
    return lines;
}

// Restituisce true se la stringa a viene prima di b in ordine alfabetico
bool ordineAlfabetico(char *a, char *b) {
    unsigned int length  = strlen(a);
    unsigned int lengthb = strlen(b);
    length               = lengthb < length ? lengthb : length; // Prendo la lunghezza minore
    for (unsigned int i = 0; i < length; i++) {
        if (tolower(a[i]) < tolower(b[i])) { // Se viene prima
            return true;
        } else if (tolower(a[i]) > tolower(b[i])) { // Se viene dopo
            return false;
        }
    }
    return lengthb != length; // Se era uguale per tutta la lunghezza restituisco true nel solo caso in cui a fosse la parola più breve
}

// Restituisce true se due stringhe sono uguali
bool equalStrings(char *a, char *b) {
    unsigned int Length = strlen(a);
    if (strlen(b) != Length) {
        return false;
    }
    for (unsigned int i = 0; i < Length; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

// Stampa un "Premi invio per continuare..."
void premiPerContinuare() {
    puts("Premi invio per continuare...");
    getchar();
    getchar();
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
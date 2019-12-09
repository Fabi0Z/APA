#include "scacchiera.h"

// Legge e memorizza una cella da striga
void parseCella(cella *c, char *string, arrayTessera *a) {
    uint8_t rotazione;
    long int indiceTessera;
    sscanf(string, "%d/%" SCNd8 " %[^\n]", &indiceTessera, &rotazione, string);

    if (indiceTessera == -1) { // Se la cella è vuota scrivo NULL
        c = NULL;
        return;
    }

    c->Rotazione = rotazione;
    c->Tessera   = &a->Array[indiceTessera];
}

// Alloca la memoria della matrice di celle di una scacchiera
void allocaScacchiera(scacchiera *s) {
    s->Matrice = (cella **)calloc(s->Righe, sizeof(cella *));
    for (unsigned int i = 0; i < s->Righe; i++) {
        s->Matrice[i] = (cella *)calloc(s->Colonne, sizeof(cella));
    }
}

// Legge e memorizza una scacchiera da file
void parseScacchiera(scacchiera *s, FILE *stream, arrayTessera *a) {
    fscanf(stream, "%d %d\n", &s->Righe, &s->Colonne);
    allocaScacchiera(s);

    unsigned int strMax = 5 * s->Colonne;
    char temp[strMax + 1];
    for (size_t i = 0; i < s->Righe; i++) {
        fgets(temp, strMax, stream);
        for (size_t j = 0; j < s->Colonne; j++) {
            parseCella(&s->Matrice[i][j], temp, a);
        }
    }
}

// Stampa i due tubi di una cella in ordine corretto
void printTubi(tubo *orizzontale, tubo *verticale, FILE *stream) {
    fprintf(stream, " _ _ _ \n");
    fprintf(stream, "|* %c *|\n", verticale->Colore);
    fprintf(stream, "|%c * %" SCNd8 "|\n", orizzontale->Colore, orizzontale->Valore);
    fprintf(stream, "|* %" SCNd8 " *|\n", verticale->Valore);
    fprintf(stream, " ¯ ¯ ¯ \n");
}

// Stampa una cella
void printCella(cella *c, arrayTessera *a, FILE *stream) {
    tessera *t = c->Tessera;
    if (c->Rotazione) {
        printTubi(&t->Tubo2, &t->Tubo1, stream);
    } else {
        printTubi(&t->Tubo1, &t->Tubo2, stream);
    }
}
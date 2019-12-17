#include "scacchiera.h"

// Legge e memorizza una cella da striga
void parseCella(cella *c, char *string, arrayTessera *a) {
    uint8_t rotazione;
    int indiceTessera;
    sscanf(string, "%d/%" SCNd8 "%[^\n]", &indiceTessera, &rotazione, string);

    if (indiceTessera == -1) { // Se la cella è vuota scrivo NULL nella tessera
        c->Tessera = NULL;
        return;
    }

    c->Rotazione = rotazione;
    c->Tessera   = a->Array[indiceTessera];
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
    fscanf(stream, "%u %u\n", &s->Righe, &s->Colonne);
    allocaScacchiera(s);

    unsigned int strMax = 6 * s->Colonne;
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

// Stampa il bordo superiore di una riga di scacchiera
void stampaRigaSuperiore(scacchiera *s, FILE *stream) {
    for (unsigned int i = 0; i < s->Colonne; i++) {
        fprintf(stream, " __ __ __ ");
    }
    fprintf(stream, "\n");
}

// Stampa il bordo inferiore di una riga di scacchiera
void stampaRigaInferiore(scacchiera *s, FILE *stream) {
    for (unsigned int i = 0; i < s->Colonne; i++) {
        fprintf(stream, " ¯¯ ¯¯ ¯¯ ");
    }
    fprintf(stream, "\n");
}

void stampaSottoriga1(scacchiera *s, unsigned int indiceRiga, FILE *stream) {
    cella *c;
    tessera *t;
    for (unsigned int i = 0; i < s->Colonne; i++) {
        c = &s->Matrice[indiceRiga][i];

        if (c->Tessera == NULL) { // Controllo che la cella non sia vuota
            fprintf(stream, "|        |");
        } else {
            t = c->Tessera;
            if (c->Rotazione) {
                fprintf(stream, "| * %2c * |", t->Tubo1.Colore);
            } else {
                fprintf(stream, "| * %2c * |", t->Tubo2.Colore);
            }
        }
    }
    fprintf(stream, "\n");
}

void stampaSottoriga2(scacchiera *s, unsigned int indiceRiga, FILE *stream) {
    cella *c;
    tessera *t;
    for (unsigned int i = 0; i < s->Colonne; i++) {
        c = &s->Matrice[indiceRiga][i];

        if (c->Tessera == NULL) { // Controllo che la cella non sia vuota
            fprintf(stream, "|        |");
        } else {
            t = c->Tessera;
            if (c->Rotazione) {
                fprintf(stream, "|%2c  * %2" SCNd8 "|", t->Tubo2.Colore, t->Tubo2.Valore);
            } else {
                fprintf(stream, "|%2c  * %2" SCNd8 "|", t->Tubo1.Colore, t->Tubo1.Valore);
            }
        }
    }
    fprintf(stream, "\n");
}

void stampaSottoriga3(scacchiera *s, unsigned int indiceRiga, FILE *stream) {
    cella *c;
    tessera *t;
    for (unsigned int i = 0; i < s->Colonne; i++) {
        c = &s->Matrice[indiceRiga][i];

        if (c->Tessera == NULL) { // Controllo che la cella non sia vuota
            fprintf(stream, "|        |");
        } else {
            t = c->Tessera;
            if (c->Rotazione) {
                fprintf(stream, "| * %2" SCNd8 " * |", t->Tubo1.Valore);

            } else {
                fprintf(stream, "| * %2" SCNd8 " * |", t->Tubo2.Valore);
            }
        }
    }
    fprintf(stream, "\n");
}

// Stampa una riga di scacchiera
void stampaRigaScacchiera(scacchiera *s, unsigned int indiceRiga, FILE *stream) {
    stampaRigaSuperiore(s, stream);
    stampaSottoriga1(s, indiceRiga, stream);
    stampaSottoriga2(s, indiceRiga, stream);
    stampaSottoriga3(s, indiceRiga, stream);
    stampaRigaInferiore(s, stream);
}

// Stampa una scacchiera
void printScacchiera(scacchiera *s, FILE *stream) {
    for (unsigned int i = 0; i < s->Righe; i++) {
        stampaRigaScacchiera(s, i, stream);
    }
    fprintf(stream, "\n");
}

// Copia src in dest
void copiaArrayCella(arrayCella *dest, arrayCella *src) {
    dest->NumeroElementi = src->NumeroElementi;

    for (unsigned int i = 0; i < src->NumeroElementi; i++) {
        dest->Array[i]->Rotazione = src->Array[i]->Rotazione;
        dest->Array[i]->Tessera   = src->Array[i]->Tessera;
    }
}

// Alloca un array di celle
void allocaNuovoArrayCella(arrayCella *c, unsigned int NumeroElementi) {
    c->NumeroElementi = NumeroElementi;
    c->Array          = (cella **)calloc(c->NumeroElementi, sizeof(cella *));

    for (unsigned int i = 0; i < c->NumeroElementi; i++) {
        c->Array[i] = (cella *)malloc(sizeof(cella));
    }
}
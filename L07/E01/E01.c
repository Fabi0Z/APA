#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const uint8_t MAX_FILENAME = 51;

enum pietra { zaffiro,
              smeraldo,
              rubino,
              topazio };

typedef struct Collana { // Struttura rappresentante una collana
    unsigned int Zaffiri;
    unsigned int Smeraldi;
    unsigned int Rubini;
    unsigned int Topazi;
    unsigned int TotalePietre;
    uint8_t *Array;
} collana;

bool verificaSmeraldiRubini(uint8_t *array) { // Verifica che l'ordine dei rubini o degli smeraldi sia rispettato
    if (array[1] == smeraldo || array[1] == topazio) {
        return true;
    }
    return false;
}

bool verificaZaffiriTopazi(uint8_t *array) { // Verifica che l'ordine dei topazi o degli zaffiri sia rispettato
    if (array[1] == zaffiro || array[1] == rubino) {
        return true;
    }
    return false;
}

bool verificaCollana(collana *c) { // Verifica che l'ordine delle pietre sia rispettato
    unsigned int totale = c->Zaffiri + c->Smeraldi + c->Rubini + c->Topazi;
    bool check;
    for (size_t i = 0; i < totale - 1; i++) { // Per ogni pietra eccetto l'ultima
        check = false;
        switch (c->Array[i]) {
            case zaffiro: {
                check = verificaZaffiriTopazi(&c->Array[i]);
                break;
            }

            case smeraldo: {
                check = verificaSmeraldiRubini(&c->Array[i]);
                break;
            }

            case rubino: {
                check = verificaSmeraldiRubini(&c->Array[i]);
                break;
            }

            case topazio: {
                check = verificaZaffiriTopazi(&c->Array[i]);
                break;
            }
        }
        if (!check) { // Se trovo anche un solo errore nell'ordine restituisco false
            return false;
        }
    }
    return true;
}

collana parseCollana(char *string) { // Effettua il parse di una collana da stringa e svuota la stringa
    collana c;
    sscanf(string, "%d %[^\n]", &c.Zaffiri, string);
    sscanf(string, "%d %[^\n]", &c.Smeraldi, string);
    sscanf(string, "%d %[^\n]", &c.Rubini, string);
    sscanf(string, "%d", &c.Topazi);

    c.TotalePietre = c.Zaffiri + c.Smeraldi + c.Rubini + c.Topazi;
    c.Array        = (uint8_t)calloc(c.TotalePietre, sizeof(uint8_t)); // Alloco la memoria nell'array

    for (size_t i = 0; i < c.Rubini; i++) { // Per ogni rubino
        c.Array[i] = rubino;
    }
    for (size_t i = 0; i < c.Smeraldi; i++) { // Per ogni smeraldo
        c.Array[i] = smeraldo;
    }
    for (size_t i = 0; i < c.Zaffiri; i++) { // Per ogni zaffiro
        c.Array[i] = zaffiro;
    }
    for (size_t i = 0; i < c.Topazi; i++) { // Per ogni topazio
        c.Array[i] = topazio;
    }

    return c;
}

bool apriFile(char *filename, char *modalità, FILE **stream) { // Apre un file e controlla che l'operazione sia andata a buon fine
    *stream = fopen(filename, modalità);
    if (stream == NULL) { // Se l'apertura non è andata a buon fine
        puts("Errore apertura file");
        return false;
    }
    return true;
}

int main() {
    char filename[MAX_FILENAME];
    puts("Inserisci il numero di pietre secondo quest'ordine: z s r t");
    printf("==> ");
    fgets(filename, (MAX_FILENAME - 1), stdin);
    collana c = parseCollana(filename);
    return 0;
}

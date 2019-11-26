#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

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
    uint8_t *Array;
} collana;

bool verificaSmeraldiRubini(unsigned int *array) { // Verifica che l'ordine dei rubini o degli smeraldi sia rispettato
    if (array[1] == smeraldo || array[1] == topazio) {
        return true;
    }
    return false;
}

bool verificaZaffiriTopazi(unsigned int *array) { // Verifica che l'ordine dei topazi o degli zaffiri sia rispettato
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
                check = verificaZaffiriTopazi(c->Array[i]);
                break;
            }

            case smeraldo: {
                check = verificaSmeraldiRubini(c->Array[i]);
                break;
            }

            case rubino: {
                check = verificaSmeraldiRubini(c->Array[i]);
                break;
            }

            case topazio: {
                check = verificaZaffiriTopazi(c->Array[i]);
                break;
            }
        }
        if (!check) { // Se trovo anche un solo errore nell'ordine restituisco false
            return false;
        }
    }
    return true;
}

collana parseCollana(FILE *stream) { // Effettua il parse di una collana da un filestream
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
    FILE *stream;
    printf("Inserisci il nome del file (max %d caratteri):\n==> ", (MAX_FILENAME - 1));
    scanf(" %50s", filename);
    if (apriFile(filename, "r", &stream)) {
        collana c = parseCollana(stream);
    }
    return 0;
}

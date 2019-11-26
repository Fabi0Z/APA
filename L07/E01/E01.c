#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

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

int main() {
    /* code */
    return 0;
}

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
    bool check;
    for (size_t i = 0; i < c->TotalePietre - 1; i++) { // Per ogni pietra eccetto l'ultima
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
    c.Array        = (uint8_t *)calloc(c.TotalePietre, sizeof(uint8_t)); // Alloco la memoria nell'array

    size_t posizione = 0;
    for (size_t i = 0; i < c.Zaffiri; i++) { // Per ogni zaffiro
        c.Array[posizione++] = zaffiro;
    }
    for (size_t i = 0; i < c.Smeraldi; i++) { // Per ogni smeraldo
        c.Array[posizione++] = smeraldo;
    }
    for (size_t i = 0; i < c.Rubini; i++) { // Per ogni rubino
        c.Array[posizione++] = rubino;
    }
    for (size_t i = 0; i < c.Topazi; i++) { // Per ogni topazio
        c.Array[posizione++] = topazio;
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

/*
k = numero di ripetizioni massime per ogni singolo elemento
count conta il numero di soluzioni
*/
unsigned int disp_ripet(unsigned int pos, unsigned int *val, unsigned int *sol, unsigned int n, unsigned int k) {
    unsigned int count = 0;              // Contatore per il numero di soluzioni
    if (pos >= k) {                      // Condizione di terminazione, ovvero quando la posizione raggiunge il numero massimo di ripetizioni
        for (size_t i = 0; i < k; i++) { // Per il numero di ripetizioni massime
            printf("%d", sol[i]);        // Stampo ogni elemento della soluzione
        }
        printf("\n");
        return 1;
    }
    for (size_t i = 0; i < n; i++) { // Per ogni elemento dell'array dei valori
        sol[pos] = val[i];
        count += disp_ripet(pos + 1, val, sol, n, k); // Ricorsione nella posizione successiva
    }
    return count;
}

int main() {
    char filename[MAX_FILENAME];
    puts("Inserisci il numero di pietre secondo quest'ordine: z s r t");
    printf("==> ");
    fgets(filename, (MAX_FILENAME - 1), stdin);
    collana c   = parseCollana(filename);
    collana sol = c;
    sol.Array   = (uint8_t *)calloc(sol.TotalePietre, sizeof(uint8_t));
    disp_ripet(0, &c, &sol, 1);
    return 0;
}

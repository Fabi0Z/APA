#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const uint8_t MAX_FILENAME = 51;

enum pietra { zaffiro,
              smeraldo,
              rubino,
              topazio,
              totale };

typedef struct Collana { // Struttura rappresentante una collana
    unsigned int Pietre[totale + 1];
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
    for (size_t i = 0; i < c->Pietre[totale] - 1; i++) { // Per ogni pietra eccetto l'ultima
        check = false;
        switch (c->Array[i]) {
            case zaffiro || topazio: {
                check = verificaZaffiriTopazi(&c->Array[i]);
                break;
            }

            case smeraldo || rubino: {
                check = verificaSmeraldiRubini(&c->Array[i]);
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
    sscanf(string, "%d %[^\n]", &c.Pietre[zaffiro], string);
    sscanf(string, "%d %[^\n]", &c.Pietre[smeraldo], string);
    sscanf(string, "%d %[^\n]", &c.Pietre[rubino], string);
    sscanf(string, "%d", &c.Pietre[topazio]);

    c.Pietre[totale] = c.Pietre[zaffiro] + c.Pietre[smeraldo] + c.Pietre[rubino] + c.Pietre[topazio];
    c.Array          = (uint8_t *)calloc(c.Pietre[totale], sizeof(uint8_t)); // Alloco la memoria nell'array
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

unsigned int disp_ripet(unsigned int pos, unsigned int *val, unsigned int *sol, unsigned int n, unsigned int k) {
    /* 
    k = numero di ripetizioni massime per ogni singolo elemento
    count = conta il numero di soluzioni
    */
    unsigned int count = 0;
    if (pos >= k) { // Condizione di terminazione, ovvero quando la posizione raggiunge il numero massimo di ripetizioni
        puts("Soluzione:");
        for (size_t i = 0; i < k; i++) { // Per il numero di ripetizioni massime
            printf("%d ", sol[i]);       // Stampo ogni elemento della soluzione
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
    // puts("Inserisci il numero di pietre secondo quest'ordine: z s r t");
    // printf("==> ");
    // fgets(filename, (MAX_FILENAME - 1), stdin);
    // collana c   = parseCollana(filename);
    // collana sol = c;
    // sol.Array   = (uint8_t *)calloc(sol.TotalePietre, sizeof(uint8_t));
    // disp_ripet(0, &c, &sol, 1);
    unsigned int val[4] = {zaffiro, smeraldo, topazio, rubino};
    unsigned int k      = 4 * 2;
    unsigned int sol[k];
    unsigned int c = disp_ripet(0, &val, &sol, 4, k);
    return 0;
}

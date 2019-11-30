#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t MAX_FILENAME = 51;

enum pietra { zaffiro,
              smeraldo,
              rubino,
              topazio,
              totale };

typedef struct ArrayDisposizioni { // Dato specifico contenente l'array dei valori per le disposizioni
    unsigned int *Pietre;
    uint8_t NumeroTipi; // Indica quanti tipi di pietre sono disposinibili
} arrayDisposizioni;

typedef struct Collana { // Struttura rappresentante una collana
    unsigned int Pietre[totale + 1];
    arrayDisposizioni Disposizioni;
    uint8_t *Array;
} collana;

arrayDisposizioni generaArrayDisposizioni(collana *c) { // Genera l'array delle disposizioni relativo ad una collana
    unsigned int tempArray[totale];
    c->Disposizioni.NumeroTipi = 0;

    for (size_t i = 0; i < totale; i++) { // Per ogni tipo esistente
        if (c->Pietre[i] != 0) {          // Se c'è almeno una pietra di quel tipo
            tempArray[c->Disposizioni.NumeroTipi] = i;
            c->Disposizioni.NumeroTipi++;
        }
    }

    // Creo l'array
    c->Disposizioni.Pietre = (unsigned int *)calloc(c->Disposizioni.NumeroTipi, sizeof(unsigned int));
    memcpy(c->Disposizioni.Pietre, tempArray, c->Disposizioni.NumeroTipi * sizeof(unsigned int));
}

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

bool verificaCollana(collana *c) { // Verifica che l'ordine delle pietre sia rispettato e che il numero di pietre sia corretto
    bool check;
    unsigned int conteggio[totale] = {0, 0, 0, 0};
    for (size_t i = 0; i < c->Pietre[totale] - 1; i++) { // Per ogni pietra eccetto l'ultima
        check = false;
        switch (c->Array[i]) {
            case zaffiro: {
                conteggio[zaffiro]++;
                if (conteggio[zaffiro] > c->Pietre[zaffiro]) { // Se il numero di pietre eccede
                    return false;                              // Restituisco false
                }
                check = verificaZaffiriTopazi(&c->Array[i]);
                break;
            }

            case smeraldo: {
                conteggio[smeraldo]++;
                if (conteggio[smeraldo] > c->Pietre[smeraldo]) { // Se il numero di pietre eccede
                    return false;                                // Restituisco false
                }
                check = verificaSmeraldiRubini(&c->Array[i]);
                break;
            }

            case rubino: {
                conteggio[rubino]++;
                if (conteggio[rubino] > c->Pietre[rubino]) { // Se il numero di pietre eccede
                    return false;                            // Restituisco false
                }
                check = verificaSmeraldiRubini(&c->Array[i]);
                break;
            }

            case topazio: {
                conteggio[topazio]++;
                if (conteggio[topazio] > c->Pietre[topazio]) { // Se il numero di pietre eccede
                    return false;                              // Restituisco false
                }
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
    sscanf(string, "%d %[^\n]", &c.Pietre[zaffiro], string);
    sscanf(string, "%d %[^\n]", &c.Pietre[smeraldo], string);
    sscanf(string, "%d %[^\n]", &c.Pietre[rubino], string);
    sscanf(string, "%d", &c.Pietre[topazio]);

    c.Pietre[totale] = c.Pietre[zaffiro] + c.Pietre[smeraldo] + c.Pietre[rubino] + c.Pietre[topazio];
    c.Array          = (uint8_t *)calloc(c.Pietre[totale], sizeof(uint8_t)); // Alloco la memoria nell'array

    generaArrayDisposizioni(&c); // Genero l'array delle disposizioni
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

unsigned int generaCollane(unsigned int pos, collana *c) {
    unsigned int count = 0;
    if (pos >= c->Pietre[totale]) { // Condizione di terminazione, ovvero quando la posizione raggiunge il numero massimo di ripetizioni
        puts("Soluzione:");
        for (size_t i = 0; i < c->Pietre[totale]; i++) { // Per il numero di ripetizioni massime
            printf("%d ", c->Array[i]);                  // Stampo ogni elemento della soluzione
        }
        printf("\n");
        return 1;
    }
    for (size_t i = 0; i < c->Disposizioni.NumeroTipi; i++) { // Per ogni tipo di pietra
        c->Array[pos] = c->Disposizioni.Pietre[i];
        count += generaCollane(pos + 1, c); // Ricorsione nella posizione successiva
    }
    return count;
}

int main() {
    char filename[MAX_FILENAME];
    puts("Inserisci il numero di pietre secondo quest'ordine: z s r t");
    printf("==> ");
    fgets(filename, (MAX_FILENAME - 1), stdin);
    collana c          = parseCollana(filename);
    unsigned int count = generaCollane(0, &c);
    return 0;
}

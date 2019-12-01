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
    for (size_t i = 0; i < c->Pietre[totale]; i++) { // Per ogni pietra
        check = false;
        switch (c->Array[i]) {
            case zaffiro: {
                conteggio[zaffiro]++;
                if (conteggio[zaffiro] > c->Pietre[zaffiro]) { // Se il numero di pietre eccede
                    return false;                              // Restituisco false
                }
                // Eseguo il controllo dell'ordine solo se non mi trovo sull'ultima pietra
                check = i == c->Pietre[totale] - 1 ? true : verificaZaffiriTopazi(&c->Array[i]);
                break;
            }

            case smeraldo: {
                conteggio[smeraldo]++;
                if (conteggio[smeraldo] > c->Pietre[smeraldo]) { // Se il numero di pietre eccede
                    return false;                                // Restituisco false
                }
                // Eseguo il controllo dell'ordine solo se non mi trovo sull'ultima pietra
                check = i == c->Pietre[totale] - 1 ? true : verificaSmeraldiRubini(&c->Array[i]);
                break;
            }

            case rubino: {
                conteggio[rubino]++;
                if (conteggio[rubino] > c->Pietre[rubino]) { // Se il numero di pietre eccede
                    return false;                            // Restituisco false
                }
                // Eseguo il controllo dell'ordine solo se non mi trovo sull'ultima pietra
                check = i == c->Pietre[totale] - 1 ? true : verificaSmeraldiRubini(&c->Array[i]);
                break;
            }

            case topazio: {
                conteggio[topazio]++;
                if (conteggio[topazio] > c->Pietre[topazio]) { // Se il numero di pietre eccede
                    return false;                              // Restituisco false
                }
                // Eseguo il controllo dell'ordine solo se non mi trovo sull'ultima pietra
                check = i == c->Pietre[totale] - 1 ? true : verificaZaffiriTopazi(&c->Array[i]);
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

void printPietra(uint8_t p) { // Stampa una pietra
    switch (p) {
        case zaffiro: {
            printf("z");
            break;
        }

        case smeraldo: {
            printf("s");
            break;
        }

        case rubino: {
            printf("r");
            break;
        }

        case topazio: {
            printf("t");
            break;
        }
    }
}

void contaPietre(collana *c) { // Conta il numero di pietre in una collana
    c->Pietre[zaffiro]  = 0;
    c->Pietre[smeraldo] = 0;
    c->Pietre[rubino]   = 0;
    c->Pietre[topazio]  = 0;
    for (size_t i = 0; i < c->Pietre[totale]; i++) { // Per ogni pietra
        switch (c->Array[i]) {
            case zaffiro: {
                c->Pietre[zaffiro]++;
                break;
            }

            case smeraldo: {
                c->Pietre[smeraldo]++;
                break;
            }

            case rubino: {
                c->Pietre[rubino]++;
                break;
            }

            case topazio: {
                c->Pietre[topazio]++;
                break;
            }
        }
    }
}

void printCollana(collana *c) { // Stampa una collana
    contaPietre(c);
    printf("%d Zaffiri; ", c->Pietre[zaffiro]);
    printf("%d Smeraldi; ", c->Pietre[smeraldo]);
    printf("%d Rubini; ", c->Pietre[rubino]);
    printf("%d Topazi; ", c->Pietre[topazio]);
    printf("Totale %d pietre\n", c->Pietre[totale]);
    puts("La collana è composta così:");
    printPietra(c->Array[0]);
    for (size_t i = 1; i < c->Pietre[totale]; i++) { // Per ogni pietra
        printf("-");
        printPietra(c->Array[i]);
    }
    printf("\n");
}

unsigned int generaCollane(unsigned int pos, collana *c, collana *max) {
    unsigned int count = 0;
    if (pos >= c->Pietre[totale]) {                        // Condizione di terminazione, ovvero quando la posizione raggiunge il numero massimo di ripetizioni
        if (verificaCollana(c)) {                          // Se la collana è valida
            if (c->Pietre[totale] > max->Pietre[totale]) { // Se la collana generata ha lunghezza maggiore di quella massima
                memcpy(max->Pietre, c->Pietre, sizeof(unsigned int) * totale + 1);
                free(max->Array);
                max->Array = (uint8_t *)calloc(max->Pietre[totale], sizeof(uint8_t));
                memcpy(max->Array, c->Array, sizeof(uint8_t) * c->Pietre[totale]);
            }
            return 1;
        }
        return 0;
    }
    for (size_t i = 0; i < c->Disposizioni.NumeroTipi; i++) { // Per ogni tipo di pietra
        c->Array[pos] = c->Disposizioni.Pietre[i];
        count += generaCollane(pos + 1, c, max); // Ricorsione nella posizione successiva
    }
    return count;
}

unsigned int collaneVarieLunghezze(collana *c) { // Genera collane con lunghezza variabile
    unsigned int count = 0;
    collana max;
    max.Pietre[totale]            = 0;
    max.Array                     = (uint8_t *)malloc(sizeof(uint8_t));
    unsigned int lunghezzaMassima = c->Pietre[totale];

    for (size_t i = 1; i <= lunghezzaMassima; i++) { // Per un numero di volte pari al totale delle pietre
        c->Pietre[totale] = i;
        count += generaCollane(0, c, &max);
    }
    printf("Sono state generate %d collane, la seguente è quella di lunghezza massima:\n", count);
    printCollana(&max);
    return count;
}

bool checkFilestream(FILE *stream) { // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
    }
    return false;
}

void parseFromFile(char *filename) { // Esegue i vari test presenti in un file
    FILE *stream = fopen(filename, "r");
    checkFilestream(stream);
    unsigned int nTest;
    fscanf(stream, "%d\n", &nTest);
    for (size_t i = 0; i < nTest; i++) { // Per ogni test
        char riga[MAX_FILENAME];
        fgets(riga, MAX_FILENAME - 1, stream);
        collana c = parseCollana(riga);
        collaneVarieLunghezze(&c);
    }
}

int main() {
    char filename[MAX_FILENAME];
    puts("Inserisci il nome del file:");
    printf("==> ");
    fgets(filename, (MAX_FILENAME - 1), stdin);
    parseFromFile(filename);
    return 0;
}

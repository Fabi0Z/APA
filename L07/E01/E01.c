#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t MAX_FILENAME = 51;

typedef enum { zaffiro,
               rubino,
               topazio,
               smeraldo,
               totale } pietra;

typedef struct ArrayDisposizioni { // Dato specifico contenente l'array dei valori per le disposizioni
    unsigned int *Pietre;
    uint8_t NumeroTipi; // Indica quanti tipi di pietre sono disposinibili
} arrayDisposizioni;

typedef struct Collana { // Struttura rappresentante una collana
    unsigned int Pietre[totale + 1];
    arrayDisposizioni Disposizioni;
    pietra *Array;
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

bool verificaSmeraldiRubini(pietra *array) { // Verifica che l'ordine dei rubini o degli smeraldi sia rispettato
    if (array[1] == smeraldo || array[1] == topazio) {
        return true;
    }
    return false;
}

bool verificaZaffiriTopazi(pietra *array) { // Verifica che l'ordine dei topazi o degli zaffiri sia rispettato
    if (array[1] == zaffiro || array[1] == rubino) {
        return true;
    }
    return false;
}

bool verificaOrdine(pietra *array) { // Verifica che l'ordine della pietra successiva sia corretto
    switch (array[0]) {
        case zaffiro: {
            // Eseguo il controllo dell'ordine solo se non mi trovo sull'ultima pietra
            return verificaZaffiriTopazi(array);
        }

        case smeraldo: {
            // Eseguo il controllo dell'ordine solo se non mi trovo sull'ultima pietra
            return verificaSmeraldiRubini(array);
        }

        case rubino: {
            // Eseguo il controllo dell'ordine solo se non mi trovo sull'ultima pietra
            return verificaSmeraldiRubini(array);
        }

        case topazio: {
            // Eseguo il controllo dell'ordine solo se non mi trovo sull'ultima pietra
            return verificaZaffiriTopazi(array);
        }
    }
}

collana parseCollana(char *string) { // Effettua il parse di una collana da stringa e svuota la stringa
    collana c;
    sscanf(string, "%d %[^\n]", &c.Pietre[zaffiro], string);
    sscanf(string, "%d %[^\n]", &c.Pietre[rubino], string);
    sscanf(string, "%d %[^\n]", &c.Pietre[topazio], string);
    sscanf(string, "%d", &c.Pietre[smeraldo]);

    c.Pietre[totale] = c.Pietre[zaffiro] + c.Pietre[smeraldo] + c.Pietre[rubino] + c.Pietre[topazio];
    c.Array          = (pietra *)calloc(c.Pietre[totale], sizeof(pietra)); // Alloco la memoria nell'array

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

void printPietra(pietra p) { // Stampa una pietra
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
    printf("zaffiro = %d, ", c->Pietre[zaffiro]);
    printf("rubino = %d, ", c->Pietre[rubino]);
    printf("topazio = %d, ", c->Pietre[topazio]);
    printf("smeraldo = %d, ", c->Pietre[smeraldo]);
    printf("TOT = %d", c->Pietre[totale]);
    // puts("La collana è composta così:");
    // printPietra(c->Array[0]);
    // for (size_t i = 1; i < c->Pietre[totale]; i++) { // Per ogni pietra
    //     printf("-");
    //     printPietra(c->Array[i]);
    // }
    printf("\n");
}

unsigned int generaCollane(unsigned int pos, collana *c, collana *max) {
    unsigned int count = 0;

    if (pos > 0) { // Se sono almeno in seconda posizione controllo che il numero di pietre sia corretto
        pietra ultimaPietra = c->Array[pos - 1];
        if (c->Pietre[ultimaPietra] > max->Pietre[ultimaPietra]) { // Se il numero di pietre eccede il valore massimo
            return 0;
        }
    }

    if (pos >= c->Pietre[totale]) {                    // Condizione di terminazione, ovvero quando la posizione raggiunge il numero massimo di ripetizioni
        if (c->Pietre[totale] > max->Pietre[totale]) { // Se il numero di pietre è maggiore dell'attuale massimo
            max->Pietre[totale] = c->Pietre[totale];
            free(max->Array);
            max->Array = (pietra *)calloc(c->Pietre[totale], sizeof(pietra));
            memcpy(max->Array, c->Array, sizeof(pietra) * c->Pietre[totale]); // Copio l'array di pietre
        }
        return 1;
    } else if (pos > 1) {                         // Se ho almeno due elementi
        if (verificaOrdine(&c->Array[pos - 2])) { // Verifico che l'ordine dell'ultima pietra inserita sia corretto
            return 0;
        }
    }

    for (size_t i = 0; i < c->Disposizioni.NumeroTipi; i++) { // Per ogni tipo di pietra
        c->Array[pos] = c->Disposizioni.Pietre[i];
        c->Pietre[c->Disposizioni.Pietre[i]]++;  // Conto la pietra
        count += generaCollane(pos + 1, c, max); // Ricorsione nella posizione successiva
        c->Pietre[c->Disposizioni.Pietre[i]]--;  // Rimuovo la pietra
    }
    return count;
}

unsigned int collaneVarieLunghezze(collana *c) { // Genera collane con lunghezza variabile
    unsigned int count = 0;
    collana max;
    memcpy(max.Pietre, c->Pietre, sizeof(unsigned int) * totale); // Copio il numero massimo di pietre
    max.Pietre[totale]            = 0;
    max.Array                     = (pietra *)malloc(sizeof(pietra));
    unsigned int lunghezzaMassima = c->Pietre[totale];

    for (size_t i = 1; i <= lunghezzaMassima; i++) {         // Per un numero di volte pari al totale delle pietre
        memset(c->Pietre, 0, sizeof(unsigned int) * totale); // Svuoto il contatore
        c->Pietre[totale] = i;
        count += generaCollane(0, c, &max);
    }

    free(max.Array);
    return max.Pietre[totale];
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
    unsigned int nTest, massima;
    fscanf(stream, "%d\n", &nTest);
    for (size_t i = 0; i < nTest; i++) { // Per ogni test
        char riga[MAX_FILENAME];
        fgets(riga, MAX_FILENAME - 1, stream);
        collana c = parseCollana(riga);
        printf("TEST #%d\n", i + 1);
        printCollana(&c);
        massima = collaneVarieLunghezze(&c);
        printf("Collana massima lunghezza %d\n", massima);
    }
}

int main() {
    char filename[MAX_FILENAME];
    puts("Inserisci il nome del file:");
    printf("==> ");
    fgets(filename, (MAX_FILENAME - 1), stdin);
    sscanf(filename, "%s", filename);
    parseFromFile(filename);
    return 0;
}

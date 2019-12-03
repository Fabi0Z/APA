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

typedef struct Collana { // Struttura rappresentante una collana
    unsigned int Pietre[totale + 1];
    pietra *Array;
    unsigned int RipetizioniMassime;
    unsigned int ValorePietre[totale];
} collana;

unsigned int calcolaValore(collana *c) { // Calcola il valore di una collana
    unsigned int count = 0;
    for (size_t i = 0; i < totale; i++) { // Per ogni pietra
        count += c->Pietre[i] * c->ValorePietre[i];
    }
    return count;
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
    c.Pietre[totale] = 0;

    for (size_t i = 0; i < totale; i++) {                  // Per ogni pietra
        sscanf(string, "%d %[^\n]", &c.Pietre[i], string); // Scrivo la disponibilità
        c.Pietre[totale] += c.Pietre[i];
    }

    for (size_t i = 0; i < totale; i++) {                        // Per ogni pietra
        sscanf(string, "%d %[^\n]", &c.ValorePietre[i], string); // Scrivo il valore
    }

    sscanf(string, "%d", &c.RipetizioniMassime);

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
            printf("Z");
            break;
        }

        case smeraldo: {
            printf("S");
            break;
        }

        case rubino: {
            printf("R");
            break;
        }

        case topazio: {
            printf("T");
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
    printf("Sono presenti: %d Zaffiri di valore %d; ", c->Pietre[zaffiro], c->ValorePietre[zaffiro]);
    printf("%d Rubini di valore %d; ", c->Pietre[rubino], c->ValorePietre[rubino]);
    printf("%d Topazi di valore %d; ", c->Pietre[topazio], c->ValorePietre[topazio]);
    printf("%d Smerladi di valore %d;\n", c->Pietre[smeraldo], c->ValorePietre[smeraldo]);
    printf("Totale %d pietre con ripetizione massima di %d\n", c->Pietre[totale], c->RipetizioniMassime);
    printPietra(c->Array[0]);
    for (size_t i = 1; i < c->Pietre[totale]; i++) { // Per ogni pietra
        printf("-");
        printPietra(c->Array[i]);
    }
    printf("\n");
}

bool generaCollane(unsigned int pos, collana *c, collana *max) { // Restituisce true se è riuscito a trovare una combinazione, altrimenti false

    // Per collane con più di un elemento verifico l'ordine delle pietre
    if (pos > 1) {
        if (!verificaOrdine(&c->Array[pos - 2])) { // Verifico che l'ordine dell'ultima pietra inserita sia corretto
            return false;
        }
    }

    // Condizione di terminazione, ovvero quando la posizione raggiunge il numero massimo di ripetizioni
    if (pos >= c->Pietre[totale]) {
        if (c->Pietre[totale] > max->Pietre[totale]) { // Se il numero di pietre è maggiore dell'attuale massimo
            max->Pietre[totale] = c->Pietre[totale];
            free(max->Array);
            max->Array = (pietra *)calloc(c->Pietre[totale], sizeof(pietra));
            memcpy(max->Array, c->Array, sizeof(pietra) * c->Pietre[totale]); // Copio l'array di pietre
        }
        return true;
    }

    for (pietra i = 0; i < totale; i++) { // Per ogni tipo di pietra
        if (max->Pietre[i] > 0) {         // Se ho ancora disponibilità
            max->Pietre[i]--;             // Tolgo la pietra
            c->Array[pos] = i;
            if (generaCollane(pos + 1, c, max)) { // Se trovo una collana successiva
                return true;
            }
            max->Pietre[i]++; // Rimetto la pietra al suo posto
        }
    }
    return false;
}

void aggiornaDisponibilit(collana *b, collana *a) { // Scrive in b la disponibilità massima di pietre rispetto ad a
    for (size_t i = 0; i < totale; i++) {           // Per ogni pietra
        b->Pietre[i] = a->Pietre[i] > a->RipetizioniMassime ? a->RipetizioniMassime : a->Pietre[i];
    }
}

unsigned int collaneVarieLunghezze(collana *c, collana *max) {                 // Genera collane con lunghezza variabile
    aggiornaDisponibilit(max, c);                                              // Copio il numero massimo di pietre
    memcpy(max->ValorePietre, c->ValorePietre, sizeof(unsigned int) * totale); // Copio il valore delle pietre
    max->RipetizioniMassime       = c->RipetizioniMassime;
    max->Pietre[totale]           = 0;
    max->Array                    = (pietra *)malloc(sizeof(pietra));
    unsigned int lunghezzaMassima = c->Pietre[totale];
    c->Array                      = (pietra *)calloc(lunghezzaMassima, sizeof(pietra)); // Alloco la memoria nell'array

    unsigned int maxAttuale = 0;
    for (size_t i = 1; i <= lunghezzaMassima; i++) { // Per un numero di volte pari al totale delle pietre
        aggiornaDisponibilit(max, c);                // Copio il numero massimo di pietre
        c->Pietre[totale] = i;
        generaCollane(0, c, max);
        if (max->Pietre[totale] > maxAttuale) {
            maxAttuale = max->Pietre[totale];
        } else {
            break;
        }
    }

    contaPietre(max);
    free(c->Array);
    return max->Pietre[totale];
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
    collana max;
    fscanf(stream, "%d\n", &nTest);
    for (size_t i = 0; i < nTest; i++) { // Per ogni test
        char riga[MAX_FILENAME];
        fgets(riga, MAX_FILENAME - 1, stream);
        collana c = parseCollana(riga);
        printf("TEST #%d\n", i + 1);
        collaneVarieLunghezze(&c, &max);
        printCollana(&max);
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

#include "collana.h"

// Genera collane con lunghezza variabile
unsigned int collaneVarieLunghezze(collana *c, collana *max) {
    memcpy(max->Pietre, c->Pietre, sizeof(unsigned int) * totale); // Copio il numero massimo di pietre
    max->Pietre[totale]           = 0;
    max->Array                    = (pietra *)malloc(sizeof(pietra));
    unsigned int lunghezzaMassima = c->Pietre[totale];
    c->Array                      = (pietra *)calloc(lunghezzaMassima, sizeof(pietra)); // Alloco la memoria nell'array

    unsigned int maxAttuale = 0;
    for (size_t i = 1; i <= lunghezzaMassima; i++) {                   // Per un numero di volte pari al totale delle pietre
        memcpy(max->Pietre, c->Pietre, sizeof(unsigned int) * totale); // Copio il numero massimo di pietre
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

// Conta il numero di pietre in una collana
void contaPietre(collana *c) {
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

// Restituisce true se è riuscito a trovare una combinazione, altrimenti false
bool generaCollane(unsigned int pos, collana *c, collana *max) {

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

// Effettua il parse di una collana da stringa e svuota la stringa
collana parseCollana(char *string) {
    collana c;
    sscanf(string, "%u %[^\n]", &c.Pietre[zaffiro], string);
    sscanf(string, "%u %[^\n]", &c.Pietre[rubino], string);
    sscanf(string, "%u %[^\n]", &c.Pietre[topazio], string);
    sscanf(string, "%u", &c.Pietre[smeraldo]);

    c.Pietre[totale] = c.Pietre[zaffiro] + c.Pietre[smeraldo] + c.Pietre[rubino] + c.Pietre[topazio];

    return c;
}

// Stampa una collana
void printCollana(collana *c) {
    printf("Sono presenti: %u Zaffiri; ", c->Pietre[zaffiro]);
    printf("%u Rubini; ", c->Pietre[rubino]);
    printf("%u Topazi; ", c->Pietre[topazio]);
    printf("%u Smerladi; ", c->Pietre[smeraldo]);
    printf("Totale %u pietre\n", c->Pietre[totale]);
    printPietra(c->Array[0]);
    for (size_t i = 1; i < c->Pietre[totale]; i++) { // Per ogni pietra
        printf("-");
        printPietra(c->Array[i]);
    }
    printf("\n");
}

// Verifica che l'ordine della pietra successiva sia corretto
bool verificaOrdine(pietra *array) {
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

// Verifica che l'ordine dei rubini o degli smeraldi sia rispettato
bool verificaSmeraldiRubini(pietra *array) {
    if (array[1] == smeraldo || array[1] == topazio) {
        return true;
    }
    return false;
}

// Verifica che l'ordine dei topazi o degli zaffiri sia rispettato
bool verificaZaffiriTopazi(pietra *array) {
    if (array[1] == zaffiro || array[1] == rubino) {
        return true;
    }
    return false;
}

// Calcola la lunghezza massima di una collana composta da un tot di pietre e iniziante per uno zaffiro
unsigned int maxZaffiri(unsigned int *pietre) {
    if (pietre[zaffiro] == 0) { // Se non ho nemmeno uno zaffiro
        return 0;
    }

    pietre[zaffiro]--; // Rimuovo uno zaffiro

    if (pietre[zaffiro] > 0) { // Se ho altri zaffiri
        return maxZaffiri(pietre) + 1;
    } else if (pietre[rubino] > 0) { // Se ho almeno un rubino
        return maxRubini(pietre) + 1;
    }
}

// Calcola la lunghezza massima di una collana composta da un tot di pietre e iniziante per un rubino
unsigned int maxRubini(unsigned int *pietre) {
    if (pietre[rubino] == 0) { // Se non ho nemmeno un rubino
        return 0;
    }

    pietre[rubino]--; // Rimuovo un rubino

    if (pietre[topazio] > 0) { // Se ho almeno un topazio
        return maxTopazi(pietre) + 1;
    } else if (pietre[smeraldo] > 0) { // Se ho almeno uno smeraldo
        return maxSmeraldi(pietre) + 1;
    }
}

// Calcola la lunghezza massima di una collana composta da un tot di pietre e iniziante per un topazio
unsigned int maxTopazi(unsigned int *pietre) {
    if (pietre[topazio] == 0) { // Se non ho nemmeno un topazio
        return 0;
    }

    pietre[topazio]--; // Rimuovo un topazio

    if (pietre[zaffiro] > 0) { // Se ho almeno uno zaffiro
        return maxZaffiri(pietre) + 1;
    } else if (pietre[rubino] > 0) { // Se ho almeno un rubino
        return maxRubini(pietre) + 1;
    }
}

// Calcola la lunghezza massima di una collana composta da un tot di pietre e iniziante per uno smeraldo
unsigned int maxSmeraldi(unsigned int *pietre) {
    if (pietre[smeraldo] == 0) { // Se non ho nemmeno uno smeraldo
        return 0;
    }

    pietre[smeraldo]--; // Rimuovo uno smeraldo

    if (pietre[smeraldo] > 0) { // Se ho altri smeraldi
        return maxSmeraldi(pietre) + 1;
    } else if (pietre[topazio] > 0) { // Se ho almeno un topazio
        return maxTopazi(pietre) + 1;
    }
}

// Restituisce la collana di lunghezza massima per un insieme di pietre
unsigned int maxCollana(unsigned int *pietre) {
    unsigned int risultati[totale];

    // Calcolo i risultati con inizi differenti
    unsigned int pietre2[totale];
    memcpy(pietre2, pietre, sizeof(unsigned int) * totale);
    risultati[zaffiro] = maxZaffiri(pietre2);
    memcpy(pietre2, pietre, sizeof(unsigned int) * totale);
    risultati[rubino] = maxRubini(pietre2);
    memcpy(pietre2, pietre, sizeof(unsigned int) * totale);
    risultati[topazio] = maxTopazi(pietre2);
    memcpy(pietre2, pietre, sizeof(unsigned int) * totale);
    risultati[smeraldo] = maxSmeraldi(pietre2);

    unsigned int max = 0;
    pietra maxTipo;

    // Trovo il massimo
    for (size_t i = 0; i < totale; i++) { // Per ogni tipo di pietra
        if (risultati[i] > max) {
            max     = risultati[i];
            maxTipo = i;
        }
    }

    return risultati[maxTipo] + 1; // Restituisco il massimo
}
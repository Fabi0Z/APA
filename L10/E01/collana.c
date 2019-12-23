#include "collana.h"

// Allora e restituisce una collana
collana creaCollana() {
    return (collana)malloc(sizeof(struct Collana));
}

// Effettua il parse di una collana da stringa e svuota la stringa
collana parseCollana(char *string) {
    collana c = creaCollana();
    sscanf(string, "%u %[^\n]", &c->Pietre[zaffiro], string);
    sscanf(string, "%u %[^\n]", &c->Pietre[rubino], string);
    sscanf(string, "%u %[^\n]", &c->Pietre[topazio], string);
    sscanf(string, "%u", &c->Pietre[smeraldo]);

    c->Pietre[totale] = c->Pietre[zaffiro] + c->Pietre[smeraldo] + c->Pietre[rubino] + c->Pietre[topazio];

    return c;
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
    for (unsigned int i = 0; i < totale; i++) { // Per ogni tipo di pietra
        if (risultati[i] > max) {
            max     = risultati[i];
            maxTipo = i;
        }
    }

    return risultati[maxTipo] + 1; // Restituisco il massimo
}
#include "memoizationMatrix.h"

struct MemoizationMatrix {
    unsigned int ****Matrice;
    unsigned int Dimensioni[totale];
};

// Alloca una memoizationMatrix
void allocaMemoizationMatrix(memoizationMatrix m) {
    unsigned int elementiTotali = 1;
    for (unsigned int j = 0; j < totale; j++) { // Per ogni tipo di pietra
        // Moltiplico il valore
        elementiTotali *= m->Dimensioni[j];
    }

    // Alloco la matrice
    m->Matrice = (unsigned int ****)calloc(elementiTotali, sizeof(unsigned int));
    // Metto tutti i valori a -1
    memset(m->Matrice, -1, sizeof(unsigned int) * elementiTotali);
}

// Calcola le dimensioni della matrice Memoization
void calcolaDimensioniMatrice(arrayCollane a, memoizationMatrix m) {
    memset(m->Dimensioni, 0, sizeof(int) * totale); // Azzero le dimensioni

    // Trovo il massimo di ogni dimensione
    for (unsigned int i = 0; i < a->NumeroElementi; i++) {
        for (unsigned int j = 0; j < totale; j++) { // Per ogni tipo di pietra
            // Controllo se il valore è maggiore, nel caso lo sovrascrivo
            m->Dimensioni[j] = a->Array[i]->Pietre[j] > m->Dimensioni[j] ? a->Array[i]->Pietre[j] : m->Dimensioni[j];
        }
    }
}

// Crea una memoizationMatric
memoizationMatrix creaMemoizationMatrix() {
    return (memoizationMatrix)malloc(sizeof(struct MemoizationMatrix));
}

// Legge la lunghezza massima dalla matrice
unsigned int leggiMassimo(memoizationMatrix m, unsigned int *posizione) {
    unsigned int i = posizione[zaffiro];
    unsigned int j = posizione[rubino];
    unsigned int k = posizione[topazio];
    unsigned int l = posizione[smeraldo];

    return m->Matrice[i][j][k][l];
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

// Salva la lunghezza massima nella matrice
void salvaMassimo(memoizationMatrix m, unsigned int *posizione, unsigned int massimo) {
    unsigned int i = posizione[zaffiro];
    unsigned int j = posizione[rubino];
    unsigned int k = posizione[topazio];
    unsigned int l = posizione[smeraldo];

    m->Matrice[i][j][k][l] = massimo;
}

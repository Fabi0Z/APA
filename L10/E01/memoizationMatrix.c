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

// Salva la lunghezza massima nella matrice
void salvaMassimo(memoizationMatrix m, unsigned int *posizione, unsigned int massimo) {
    unsigned int i = posizione[zaffiro];
    unsigned int j = posizione[rubino];
    unsigned int k = posizione[topazio];
    unsigned int l = posizione[smeraldo];

    m->Matrice[i][j][k][l] = massimo;
}

#include "memoizationMatrix.h"

struct MemoizationMatrix {
    unsigned int ****Matrice;
    unsigned int Dimensioni[totale];
};

// Alloca una memoizationMatrix
void allocaMemoizationMatrix(memoizationMatrix m) {
    // Alloco gli zaffiri
    m->Matrice = (unsigned int ****)calloc(m->Dimensioni[zaffiro], sizeof(unsigned int ***));
    for (unsigned int i = 0; i < m->Dimensioni[zaffiro]; i++) {
        // Alloco i rubini
        m->Matrice[i] = (unsigned int ***)calloc(m->Dimensioni[rubino], sizeof(unsigned int **));
        for (unsigned int j = 0; j < m->Dimensioni[rubino]; j++) {
            // Alloco i topazi
            m->Matrice[i][j] = (unsigned int **)calloc(m->Dimensioni[topazio], sizeof(unsigned int *));
            for (unsigned int k = 0; k < m->Dimensioni[topazio]; k++) {
                // Alloco gli smeraldi
                m->Matrice[i][j][k] = (unsigned int *)calloc(m->Dimensioni[smeraldo], sizeof(unsigned int));
                for (unsigned int l = 0; l < m->Dimensioni[smeraldo]; l++) {
                    // Inizializzo il valore
                    m->Matrice[i][j][k][l] = (unsigned int)-1;
                }
            }
        }
    }
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

    // Incremento le dimensioni di 1
    for (unsigned int i = 0; i < totale; i++) {
        m->Dimensioni[i]++;
    }
}

// Restitusice true se ci sono altre pietre disponibili oltre quella indicata, altrimenti false
bool checkPietreDisponibili(pietra p, unsigned int *pietre) {
    bool disponibili = false;
    for (uint8_t i = 0; i < totale; i++) {
        if (i != p) {
            disponibili = pietre[i] > 0 ? true : false;
            if (disponibili) {
                break;
            }
        }
    }
    return disponibili;
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
unsigned int maxCollana(unsigned int *pietre, memoizationMatrix *matrici) {
    unsigned int risultati[totale];

    // Calcolo i risultati con inizi differenti
    unsigned int pietre2[totale];
    memcpy(pietre2, pietre, sizeof(unsigned int) * totale);
    risultati[zaffiro] = maxZaffiri(pietre2, matrici[zaffiro]);
    memcpy(pietre2, pietre, sizeof(unsigned int) * totale);
    risultati[rubino] = maxRubini(pietre2, matrici[rubino]);
    memcpy(pietre2, pietre, sizeof(unsigned int) * totale);
    risultati[topazio] = maxTopazi(pietre2, matrici[topazio]);
    memcpy(pietre2, pietre, sizeof(unsigned int) * totale);
    risultati[smeraldo] = maxSmeraldi(pietre2, matrici[smeraldo]);

    unsigned int max = 0;
    pietra maxTipo   = 0;

    // Trovo il massimo
    for (unsigned int i = 0; i < totale; i++) { // Per ogni tipo di pietra
        if (risultati[i] > max) {
            max     = risultati[i];
            maxTipo = i;
        }
    }

    return risultati[maxTipo]; // Restituisco il massimo
}

// Calcola la lunghezza massima di una collana composta da un tot di pietre e iniziante per un rubino
unsigned int maxRubini(unsigned int *pietre, memoizationMatrix m) {
    unsigned int massimo = leggiMassimo(m, pietre);
    if (massimo != (unsigned int)-1) { // Se ne ho già calcolato il valore
        return massimo;
    }

    if (pietre[rubino] == 0) { // Se non ho nemmeno un rubino
        return 0;
    }

    unsigned int posizione[totale];
    memcpy(posizione, pietre, sizeof(unsigned int) * totale); // Memorizzo la posizione per la memoizzazione
    pietre[rubino]--;                                         // Rimuovo un rubino

    // Controllo se ci sono altre pietre disponibili
    if (checkPietreDisponibili(rubino, pietre)) {
        if (pietre[topazio] > 0) { // Se ho almeno un topazio
            massimo = maxTopazi(pietre, m) + 1;
            salvaMassimo(m, posizione, massimo);
            return massimo;
        } else if (pietre[smeraldo] > 0) { // Se ho almeno uno smeraldo
            massimo = maxSmeraldi(pietre, m) + 1;
            salvaMassimo(m, posizione, massimo);
            return massimo;
        }
    }

    salvaMassimo(m, posizione, 1);
    return 1; // Se non ci sono altre pietre disponibili
}

// Calcola la lunghezza massima di una collana composta da un tot di pietre e iniziante per uno smeraldo
unsigned int maxSmeraldi(unsigned int *pietre, memoizationMatrix m) {
    unsigned int massimo = leggiMassimo(m, pietre);
    if (massimo != (unsigned int)-1) { // Se ne ho già calcolato il valore
        return massimo;
    }

    if (pietre[smeraldo] == 0) { // Se non ho nemmeno uno smeraldo
        return 0;
    }

    unsigned int posizione[totale];
    memcpy(posizione, pietre, sizeof(unsigned int) * totale); // Memorizzo la posizione per la memoizzazione
    pietre[smeraldo]--;                                       // Rimuovo uno smeraldo

    if (pietre[smeraldo] > 0) { // Se ho altri smeraldi
        massimo = maxSmeraldi(pietre, m) + 1;
        salvaMassimo(m, posizione, massimo);
        return massimo;
    } else if (pietre[topazio] > 0) { // Se ho almeno un topazio
        massimo = maxTopazi(pietre, m) + 1;
        salvaMassimo(m, posizione, massimo);
        return massimo;
    }

    salvaMassimo(m, posizione, 1);
    return 1; // Se non ci sono altre pietre disponibili
}

// Calcola la lunghezza massima di una collana composta da un tot di pietre e iniziante per un topazio
unsigned int maxTopazi(unsigned int *pietre, memoizationMatrix m) {
    unsigned int massimo = leggiMassimo(m, pietre);
    if (massimo != (unsigned int)-1) { // Se ne ho già calcolato il valore
        return massimo;
    }

    if (pietre[topazio] == 0) { // Se non ho nemmeno un topazio
        return 0;
    }

    unsigned int posizione[totale];
    memcpy(posizione, pietre, sizeof(unsigned int) * totale); // Memorizzo la posizione per la memoizzazione
    pietre[topazio]--;                                        // Rimuovo un topazio

    // Se ci sono altre pietre disponibili
    if (checkPietreDisponibili(topazio, pietre)) {
        if (pietre[zaffiro] > 0) { // Se ho almeno uno zaffiro
            massimo = maxZaffiri(pietre, m) + 1;
            salvaMassimo(m, posizione, massimo);
            return massimo;
        } else if (pietre[rubino] > 0) { // Se ho almeno un rubino
            massimo = maxRubini(pietre, m) + 1;
            salvaMassimo(m, posizione, massimo);
            return massimo;
        }
    }

    salvaMassimo(m, posizione, 1);
    return 1; // Se non ci sono altre pietre disponibili
}

// Calcola la lunghezza massima di una collana composta da un tot di pietre e iniziante per uno zaffiro
unsigned int maxZaffiri(unsigned int *pietre, memoizationMatrix m) {
    unsigned int massimo = leggiMassimo(m, pietre);
    if (massimo != (unsigned int)-1) { // Se ne ho già calcolato il valore
        return massimo;
    }

    if (pietre[zaffiro] == 0) { // Se non ho nemmeno uno zaffiro
        return 0;
    }

    unsigned int posizione[totale];
    memcpy(posizione, pietre, sizeof(unsigned int) * totale); // Memorizzo la posizione per la memoizzazione
    pietre[zaffiro]--;                                        // Rimuovo uno zaffiro

    if (pietre[zaffiro] > 0) { // Se ho altri zaffiri
        massimo = maxZaffiri(pietre, m) + 1;
        salvaMassimo(m, posizione, massimo);
        return massimo;
    } else if (pietre[rubino] > 0) { // Se ho almeno un rubino
        massimo = maxRubini(pietre, m) + 1;
        salvaMassimo(m, posizione, massimo);
        return massimo;
    }

    salvaMassimo(m, posizione, 1);
    return 1; // Se non ci sono altre pietre disponibili
}

// Salva la lunghezza massima nella matrice
void salvaMassimo(memoizationMatrix m, unsigned int *posizione, unsigned int massimo) {
    unsigned int i = posizione[zaffiro];
    unsigned int j = posizione[rubino];
    unsigned int k = posizione[topazio];
    unsigned int l = posizione[smeraldo];

    m->Matrice[i][j][k][l] = massimo;
}

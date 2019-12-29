#include "calcoloCombinatorio.h"

// * PRESETS

/* Preset per le disposizioni ripetute
check = funzione che si occupa della condizione di terminazione
ending = funzione che si occupa del return nella condizione di terminazione
next = funzione che si occupa di che fare con l'elemento successivo */
unsigned int _PRESET_disposizioniRipetute(array valori, array soluzione, unsigned int posizione, bool (*check)(array, array, unsigned int), unsigned int (*ending)(array, array, unsigned int), bool (*next)(array, array, unsigned int, unsigned int)) {
    unsigned int count = 0; // Contatore pre il numero di soluzioni

    if ((*check)(valori, soluzione, posizione)) {       // Condizione di terminazione
        return (*ending)(valori, soluzione, posizione); // Condizione di verifica per il return
    }

    for (unsigned int i = 0; i < valori->ObjectsNumber; i++) { // Per ogni valore
        // Funzione di esplorazione con pruning
        if ((*next)(valori, soluzione, posizione, i)) {                                                   // Esploro la posizione successiva solo se il pruning lo consente
            count += _PRESET_disposizioniRipetute(valori, soluzione, posizione + 1, check, ending, next); // Esplorazione sulla posizione successiva
        }
    }

    return count; // Restituisco il conteggio
}

// * CHECKS

// Controlla se la posizione ha raggiunto o superato la lunghezza massima dell'array soluzione
bool _CHECKS_posizioneLunghezzaSoluzione(array valori, array soluzione, unsigned int posizione) {
    return posizione >= soluzione->ObjectsNumber;
}

// * ENDINGS

// Stampa la soluzione e restituisce 1
unsigned int _ENDINGS_printOnly(array valori, array soluzione, unsigned int posizione) {
    printArray(soluzione);
    return 1;
}

// * NEXTS

// Copia l'elemento successivo del ciclo nella soluzione
bool _NEXT_copyNext(array valori, array soluzione, unsigned int posizione, unsigned int i) {
    soluzione->Objects[posizione] = valori->Objects[i];
    return true;
}

// * Models

// Modello per le disposizioni ripetute con limite dato dalla lunghezza dell'array delle soluzioni e stampa dei dati
unsigned int diposizioniRipetuteDefault(array valori, array soluzione) {
    return _PRESET_disposizioniRipetute(valori, soluzione, 0,
                                        &_CHECKS_posizioneLunghezzaSoluzione,
                                        &_ENDINGS_printOnly,
                                        &_NEXT_copyNext);
}
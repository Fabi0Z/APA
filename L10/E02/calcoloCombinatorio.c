#include "calcoloCombinatorio.h"

/* Modello per le disposizioni ripetute
   Il limite di elementi è dato dalla lunghezza dell'array delle soluzioni */
unsigned int diposizioniRipetute(array valori, array soluzione, unsigned int posizione) {
    unsigned int count = 0; // Contatore pre il numero di soluzioni

    if (posizione >= soluzione->ObjectsNumber) { // Se raggiungo il limite
        printArray(soluzione);
        return 1;
    }

    for (unsigned int i = 0; i < valori->ObjectsNumber; i++) { // Per ogni valore
        soluzione->Objects[posizione] = valori->Objects[i];
        count += diposizioniRipetute(valori, soluzione, posizione + 1);
    }

    return count; // Restituisco il conteggio
}
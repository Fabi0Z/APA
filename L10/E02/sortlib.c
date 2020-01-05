#include "sortlib.h"

// * Merge Sort
/* Unisce i due sottovettori ordinandoli
   minorEqual(item a, item b, item extraArgs) = restituisce true se a è minore o ugule a b secondo il criterio di ordinamento, extraArgs è un puntatore per contenere variabili aggiuntive */
static void merge(item *a, item *b, unsigned int inzio, unsigned int centro, unsigned int fine, bool (*minorEqual)(item a, item b, item extraArgs), item extraArgs) {
    unsigned int i, j;
    i = inzio;      // Contatore per l'esporazione dell'array sinistro
    j = centro + 1; // Contatore per l'esporazione dell'array destro

    unsigned int k;
    for (k = inzio; i <= centro && j <= fine; k++) { // Confronto gli array sinistro e destro
        if ((*minorEqual)(a[i], a[j], extraArgs))    // Se l'elemento nel sinistro è minore o uguale (oppure quello destro maggiore o uguale) all'altro copio di conseguenza
            b[k] = a[i++];
        else
            b[k] = a[j++];
    }

    while (i <= centro)
        b[k++] = a[i++]; // Copio il resto degli elementi a sinistra nell'array d'appoggio
    while (j <= fine)
        b[k++] = a[j++]; // Copio il resto degli elementi a destra nell'array d'appoggio
    for (k = inzio; k <= fine; k++)
        a[k] = b[k]; // Ricopio tutto nell'array originale
}

/* Componente ricorsiva del Merge Sort
   minorEqual(item a, item b, item extraArgs) = restituisce true se a è minore o ugule a b secondo il criterio di ordinamento, extraArgs è un puntatore per contenere variabili aggiuntive */
static void ordinaRicorsivo(item *a, item *b, unsigned int inizio, unsigned int fine, bool (*minorEqual)(item a, item b, item extraArgs), item extraArgs) {
    int centro = (inizio + fine) / 2; // Calcolo l'indice di metà vettore
    if (inizio >= fine) {             // Se ho un vettore unitario mi interrompo
        return;
    }

    ordinaRicorsivo(a, b, inizio, centro, minorEqual, extraArgs);   // Ordina a sinistra
    ordinaRicorsivo(a, b, centro + 1, fine, minorEqual, extraArgs); // Ordina a destra
    merge(a, b, inizio, centro, fine, minorEqual, extraArgs);       // Unisco i due array
}

/* Ordina un array tramite il Merge Sort
   minorEqual(item a, item b, item extraArgs) = restituisce true se a è minore o ugule a b secondo il criterio di ordinamento, extraArgs è un puntatore per contenere variabili aggiuntive */
void mergeSort(array a, bool (*minorEqual)(item a, item b, item extraArgs), item extraArgs) {
    array b             = cloneArray(a); // Clono
    unsigned int inizio = 0, fine = a->ObjectsNumber - 1;
    ordinaRicorsivo(a->Objects, b->Objects, inizio, fine, minorEqual, extraArgs);
}
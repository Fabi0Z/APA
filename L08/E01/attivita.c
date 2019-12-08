#include "attivita.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// * FUNZIONI DI CONTROLLO

// Controlla se due attività sono sovvrapposte
bool attivitaSovvrapposta(attivita *a, attivita *b) {
    return a->Inizio < b->Fine && b->Inizio < a->Fine;
}
// * -------------------------------------------------------------

// * LETTURA DATI

// Effettua il parse di un'attività da stringa
attivita parseAttivita(char *string) {
    attivita a;
    sscanf(string, "%" SCNd8 "%" SCNd8, &a.Inizio, &a.Fine);
    return a;
}
// Legge una serie di attività da file
void leggiAttivita(FILE *stream, arrayAttivita *a) {
    char string[10];
    a->Durata = 0;
    for (size_t i = 0; i < a->NumeroElementi; i++) { // Per ogni attività
        fgets(string, 9, stream);
        a->Array[i]        = parseAttivita(string);
        a->Array[i].Durata = durataAttivita(&a->Array[i]);
        a->Durata += a->Array[i].Durata;
    }
}
// * -------------------------------------------------------------

// * MANIPOLAZIONE DATI

// Unisce i due sottovettori ordinandoli
void merge(attivita *a, attivita *b, int inzio, int centro, int fine) {
    uint8_t i, j;
    i = inzio;      // Contatore per l'esporazione dell'array sinistro
    j = centro + 1; // Contatore per l'esporazione dell'array destro

    int k;
    for (k = inzio; i <= centro && j <= fine; k++) { // Confronto gli array sinistro e destro
        if (a[i].Inizio <= a[j].Inizio)              // Se l'elemento nel sinistro è minore o uguale (oppure quello destro maggiore o uguale) all'altro copio di conseguenza
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

// Componente ricorsiva del Merge Sort
void ordinaRicorsivo(attivita *a, attivita *b, uint8_t inizio, uint8_t fine) {
    int centro = (inizio + fine) / 2; // Calcolo l'indice di metà vettore
    if (inizio >= fine) {             // Se ho un vettore unitario mi interrompo
        return;
    }

    ordinaRicorsivo(a, b, inizio, centro);   // Ordina a sinistra
    ordinaRicorsivo(a, b, centro + 1, fine); // Ordina a destra
    merge(a, b, inizio, centro, fine);       // Unisco i due array
}

// Ordina un array di attività tramite il Merge Sort
void ordina(arrayAttivita *a) {
    attivita *b    = (attivita *)malloc(a->NumeroElementi * sizeof(attivita)); // Creo l'array d'appoggio
    uint8_t inizio = 0, fine = a->NumeroElementi - 1;
    ordinaRicorsivo(a->Array, b, inizio, fine);
}

// Calcola la durata di un'attività
uint8_t durataAttivita(attivita *a) {
    return a->Fine - a->Inizio;
}

// Calcola la durata di un array di attività
void durataArrayAttivita(arrayAttivita *a) {
    a->Durata = 0;
    for (uint8_t i = 0; i < a->NumeroElementi; i++) {
        a->Durata += a->Array[i].Durata;
    }
}

// Copia src in dest
void copiaArrayAttivita(arrayAttivita *dest, arrayAttivita *src) {
    for (size_t i = 0; i < src->NumeroElementi; i++) {
        dest->Array[i] = src->Array[i];
    }
    dest->Durata         = src->Durata;
    dest->NumeroElementi = src->NumeroElementi;
}
// * -------------------------------------------------------------

// * STAMPA DATI

// Stampa un'attività e restitusice la durata
void printAttivita(attivita *a) {
    printf("Inizio %" SCNd8 "; Fine %" SCNd8 "; Durata %" SCNd8 " ore\n", a->Inizio, a->Fine, durataAttivita(a));
}
// Stampa un array di attivita
void printArrayAttivita(arrayAttivita *a) {
    printf("%d attività\n", a->NumeroElementi);
    printf("Durata totale %d ore\n", a->NumeroElementi);
    for (size_t i = 0; i < a->NumeroElementi; i++) {
        printAttivita(&a->Array[i]);
    }
}
// * -------------------------------------------------------------

#include "attivita.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// * FUNZIONI DI CONTROLLO

// Controlla errori di apertura del file
bool checkFilestream(FILE *stream) {
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return true;
}
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
void leggiAttivita(FILE *stream, attivita *a, uint8_t numeroAttivita) {
    char string[10];
    for (size_t i = 0; i < numeroAttivita; i++) { // Per ogni attività
        fgets(string, 9, stream);
        a[i] = parseAttivita(string);
    }
}
// * -------------------------------------------------------------

// * STAMPA DATI

// Stampa un'attività
void printAttivita(attivita *a) {
    printf("Inizio %" SCNd8 "; Fine %" SCNd8 ";\n", a->Inizio, a->Fine);
}
// Stampa un array di attivita
void printArrayAttivita(attivita *a, uint8_t numeroAttivita) {
    printf("Sono presenti %d attività\n", numeroAttivita);
    for (size_t i = 0; i < numeroAttivita; i++) {
        printAttivita(&a[i]);
    }
    printf("\n");
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
void ordina(attivita *a, uint8_t numeroAttivita) {
    attivita *b    = (attivita *)malloc(numeroAttivita * sizeof(attivita)); // Creo l'array d'appoggio
    uint8_t inizio = 0, fine = numeroAttivita - 1;
    ordinaRicorsivo(a, b, inizio, fine);
}
// * -------------------------------------------------------------
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
    printf("Durata totale %d ore\n", a->Durata);
    for (size_t i = 0; i < a->NumeroElementi; i++) {
        printAttivita(&a->Array[i]);
    }
}
// * -------------------------------------------------------------

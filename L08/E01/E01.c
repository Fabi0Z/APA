#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// * STRUTTURE DATI
typedef struct Attivita {
    uint8_t Inizio;
    uint8_t Fine;
} attivita;
// * -------------------------------------------------------------

// * FUNZIONI DI CONTROLLO
bool checkFilestream(FILE *stream) { // Controlla errori di apertura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return true;
}
bool attivitaSovvrapposta(attivita *a, attivita *b) { // Controlla se due attività sono sovvrapposte
    return a->Inizio < b->Fine && b->Inizio < a->Fine;
}
// * -------------------------------------------------------------

// * LETTURA DATI
attivita parseAttivita(char *string) { // Effettua il parse di un'attività da stringa
    attivita a;
    sscanf(string, "%" SCNd8 "%" SCNd8, &a.Inizio, &a.Fine);
    return a;
}
void leggiAttivita(FILE *stream, attivita *a, uint8_t numeroAttivita) { // Legge una serie di attività da file
    char string[10];
    for (size_t i = 0; i < numeroAttivita; i++) { // Per ogni attività
        fgets(string, 9, stream);
        a[i] = parseAttivita(string);
    }
}
// * -------------------------------------------------------------

// * STAMPA DATI
void printAttivita(attivita *a) { // Stampa un'attività
    printf("Inizio %" SCNd8 "; Fine %" SCNd8 ";\n", a->Inizio, a->Fine);
}
void printArrayAttivita(attivita *a, uint8_t numeroAttivita) { // Stampa un array di attivita
    printf("Sono presenti %d attività\n", numeroAttivita);
    for (size_t i = 0; i < numeroAttivita; i++) {
        printAttivita(&a[i]);
    }
    printf("\n");
}
// * -------------------------------------------------------------

// * MANIPOLAZIONE DATI
// void merge(corsa *corse, corsa *corseAppoggio, int inzio, int centro, int fine, ordinamento ordine) { // Unisce i due sottovettori ordinandoli
//     int i, j;
//     i = inzio;      // Contatore per l'esporazione dell'array sinistro
//     j = centro + 1; // Contatore per l'esporazione dell'array destro

//     int k;
//     for (k = inzio; i <= centro && j <= fine; k++) {      // Confronto gli array sinistro e destro
//         if (confrontaCampi(&corse[j], &corse[i], ordine)) // Se l'elemento nel sinistro è minore o uguale (oppure quello destro maggiore o uguale) all'altro copio di conseguenza
//             corseAppoggio[k] = corse[i++];
//         else
//             corseAppoggio[k] = corse[j++];
//     }

//     while (i <= centro)
//         corseAppoggio[k++] = corse[i++]; // Copio il resto degli elementi a sinistra nell'array d'appoggio
//     while (j <= fine)
//         corseAppoggio[k++] = corse[j++]; // Copio il resto degli elementi a destra nell'array d'appoggio
//     for (k = inzio; k <= fine; k++)
//         corse[k] = corseAppoggio[k]; // Ricopio tutto nell'array originale
// }

// void ordinaRicorsivo(corsa *corse, corsa *corseAppoggio, int inizio, int fine, ordinamento ordine) { // Componente ricorsiva del Merge Sort
//     int centro = (inizio + fine) / 2;                                                                // Calcolo l'indice di metà vettore

//     if (inizio >= fine) { // Se ho un vettore unitario mi interrompo
//         return;
//     }

//     ordinaRicorsivo(corse, corseAppoggio, inizio, centro, ordine);   // Ordina a sinistra
//     ordinaRicorsivo(corse, corseAppoggio, centro + 1, fine, ordine); // Ordina a destra
//     merge(corse, corseAppoggio, inizio, centro, fine, ordine);       // Unisco i due array
// }

// void ordina(int numeroCorse, corsa corse[numeroCorse], ordinamento ordine) { // Funzione che ordina il log in base a come richiesto (è un Merge Sort)
//     corsa *corseAppoggio = (corsa *)malloc(numeroCorse * sizeof(corsa));     // Creo l'array d'appoggio
//     int inizio = 0, fine = numeroCorse - 1;
//     ordinaRicorsivo(corse, corseAppoggio, inizio, fine, ordine);
//     ORDINE_ATTUALE = ordine;
// }
// * -------------------------------------------------------------

int main() {
    FILE *stream = fopen("att.txt", "r");
    checkFilestream(stream);

    uint8_t numeroAttivita;
    fscanf(stream, "%" SCNd8 "\n", &numeroAttivita);
    attivita a[numeroAttivita];
    leggiAttivita(stream, a, numeroAttivita);
    printArrayAttivita(a, numeroAttivita);
    return 0;
}

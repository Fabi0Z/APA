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

// * FUNZIONI GENERALI
bool checkFilestream(FILE *stream) { // Controlla errori di apertura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return true;
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
} /* code */
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

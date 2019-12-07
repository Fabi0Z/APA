#include "attivita.h"
#include "smartfunctions.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// * CALCOLO COMBINATORIO

// Powerset
unsigned int powerset(uint8_t posizione, attivita *a, attivita *soluzione,
                      uint8_t maxLunghezza, uint8_t start) {
    unsigned int count = 0;

    if (start >= maxLunghezza) {                      // Se ho raggiunto la lunghezza massima
        if (posizione > 0) {                          // Se ho almeno un elemento
            printArrayAttivita(soluzione, posizione); // Stampo soluzione
            printf("\n");
            return 1;
        }
        return 0;
    }

    for (uint8_t i = start; i < maxLunghezza; i++) { // Per ogni posizione rimanente
        if (posizione > 1) {                         // Se ho almeno un'attività giaà presente nelle soluzioni

            while (attivitaSovvrapposta(&soluzione[posizione - 1], &a[i]) && i < maxLunghezza) { // Sinché l'attività successiva è sovrapposta
                i++;
            }
        }

        if (i < maxLunghezza) { // Se la condizione è ancora valida
            soluzione[posizione] = a[i];
            count += powerset(posizione + 1, a, soluzione, maxLunghezza, i + 1);
        }
    }

    count += powerset(posizione, a, soluzione, maxLunghezza, maxLunghezza);
    return count;
}
// Stampa le attività selezionate
void attSel(int N, attivita *v) {
    attivita b[N];
    unsigned int risultati = powerset(0, v, b, N, 0);
    printf("Sono state generate %d combinazioni di attività\n", risultati);
}
// * -------------------------------------------------------------

int main() {
    FILE *stream = fopen("att.txt", "r");
    checkFilestream(stream);

    uint8_t numeroAttivita;
    fscanf(stream, "%" SCNd8 "\n", &numeroAttivita);
    attivita a[numeroAttivita];
    leggiAttivita(stream, a, numeroAttivita);
    fclose(stream);
    ordina(a, numeroAttivita);
    printf("Sul file sono presenti ");
    printArrayAttivita(a, numeroAttivita);
    printf("\nLe combinazioni ottenute sono:\n\n");
    attSel(numeroAttivita, a);
    return 0;
}

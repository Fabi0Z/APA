#include "attivita.h"
#include "smartfunctions.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// * CALCOLO COMBINATORIO

// Powerset
unsigned int powerset(uint8_t posizione, attivita *a, attivita *soluzione,
                      uint8_t maxLunghezza, uint8_t start, arrayAttivita *max) {
    unsigned int count = 0;

    if (start >= maxLunghezza) { // Se ho raggiunto la lunghezza massima
        if (posizione > 0) {     // Se ho almeno un elemento
            arrayAttivita temp;
            temp.Array          = soluzione;
            temp.NumeroElementi = posizione;
            durataArrayAttivita(&temp);
            if (temp.Durata > max->Durata) {
                copiaArrayAttivita(max, &temp);
            }
            return 1;
        }
        return 0;
    }

    for (uint8_t i = start; i < maxLunghezza; i++) { // Per ogni posizione rimanente
        if (posizione > 0) {                         // Se ho almeno un'attività giaà presente nelle soluzioni

            while (attivitaSovvrapposta(&soluzione[posizione - 1], &a[i]) && i < maxLunghezza) { // Sinché l'attività successiva è sovrapposta
                i++;
            }
        }

        if (i < maxLunghezza) { // Se la condizione è ancora valida
            soluzione[posizione] = a[i];
            count += powerset(posizione + 1, a, soluzione, maxLunghezza, i + 1, max);
        }
    }

    count += powerset(posizione, a, soluzione, maxLunghezza, maxLunghezza, max);
    return count;
}
// Stampa le attività selezionate
void attSel(int N, attivita *v) {
    attivita b[N];
    arrayAttivita max;
    max.Array          = (attivita *)calloc(N, sizeof(attivita));
    max.Durata         = 0;
    max.NumeroElementi = 0;

    unsigned int risultati = powerset(0, v, b, N, 0, &max);
    printf("Sono state generate %d combinazioni di attività, quella di durata massima è\n", risultati);
    printArrayAttivita(&max);
}
// * -------------------------------------------------------------

int main() {
    FILE *stream = fopen("att.txt", "r");
    checkFilestream(stream);

    arrayAttivita a;
    fscanf(stream, "%" SCNd8 "\n", &a.NumeroElementi);
    a.Array = (attivita *)calloc(a.NumeroElementi, sizeof(attivita));
    leggiAttivita(stream, &a);
    fclose(stream);
    ordina(&a);
    printf("Sul file sono presenti ");
    printArrayAttivita(&a);
    printf("\nLe combinazioni ottenute sono:\n\n");
    attSel(a.NumeroElementi, a.Array);
    return 0;
}

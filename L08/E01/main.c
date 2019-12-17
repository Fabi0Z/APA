#include "attivita.h"
#include "smartfunctions.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// * CALCOLO COMBINATORIO

// Powerset
unsigned int powerset(uint8_t posizione, arrayAttivita *a, attivita *soluzione,
                      uint8_t start, arrayAttivita *max) {
    unsigned int count = 0;

    if (start >= a->NumeroElementi) { // Se ho raggiunto la lunghezza massima
        if (posizione > 0) {          // Se ho almeno un elemento
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

    for (uint8_t i = start; i < a->NumeroElementi; i++) { // Per ogni posizione rimanente
        if (posizione > 0) {                              // Se ho almeno un'attività giaà presente nelle soluzioni

            while (attivitaSovvrapposta(&soluzione[posizione - 1], &a->Array[i]) && i < a->NumeroElementi) { // Sinché l'attività successiva è sovrapposta
                i++;
            }
        }

        if (i < a->NumeroElementi) { // Se la condizione è ancora valida
            soluzione[posizione] = a->Array[i];
            count += powerset(posizione + 1, a, soluzione, i + 1, max);
        }
    }

    count += powerset(posizione, a, soluzione, a->NumeroElementi, max);
    return count;
}
// Stampa le attività selezionate
void attSel(int N, attivita *v) {
    attivita b[N];
    arrayAttivita a, max;
    max.Array          = (attivita *)calloc(N, sizeof(attivita));
    max.Durata         = 0;
    max.NumeroElementi = 0;
    a.Array            = v;
    a.NumeroElementi   = N;
    durataArrayAttivita(&a);

    unsigned int risultati = powerset(0, &a, b, 0, &max);
    printf("Sono state generate %u combinazioni di attività, quella di durata massima è\n", risultati);
    printArrayAttivita(&max);
}
// * -------------------------------------------------------------

int main() {
    FILE *stream = smartFopen("att.txt", "r");

    arrayAttivita a;
    fscanf(stream, "%" SCNd8 "\n", &a.NumeroElementi);
    a.Array = (attivita *)calloc(a.NumeroElementi, sizeof(attivita));
    leggiAttivita(stream, &a);
    fclose(stream);
    printf("Sul file sono presenti ");
    printArrayAttivita(&a);
    printf("\n");
    attSel(a.NumeroElementi, a.Array);
    return 0;
}

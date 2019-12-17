#include "attivita.h"
#include "smartfunctions.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Copia le attività della LA in un array di attività
void copiaLA(arrayAttivita *a, arrayAttivita *risultato, int *posizioni, unsigned int ultimo) {
    if (posizioni[ultimo] == -1) {
        risultato->Array[risultato->NumeroElementi++] = a->Array[ultimo];
        return;
    }
    copiaLA(a, risultato, posizioni, posizioni[ultimo]);
    risultato->Array[risultato->NumeroElementi++] = a->Array[ultimo];
}

unsigned int calcolaLA(arrayAttivita *att, int *P) {
    unsigned int i, j, ris = 1, V[att->NumeroElementi], last = 1, TMP[att->NumeroElementi];
    V[0] = att->Array[0].Durata;
    P[0] = -1;

    for (i = 1; i < (att->NumeroElementi); i++) {
        TMP[i] = att->Array[i].Durata;
        V[i]   = att->Array[i].Durata;
        P[i]   = -1;
        for (j = 0; j < i; j++)
            if (!attivitaSovvrapposta(&att->Array[i], &att->Array[j]) && (V[i] < TMP[i] + V[j])) {
                V[i] = TMP[i] + V[j];
                P[i] = j;
            }
        if (ris <= V[i]) {
            ris  = V[i];
            last = i;
        }
    }
    printf("Lunghezza: %d\nSequenza attività: ", ris);
    return last;
}

void selezioneDinamica(arrayAttivita *a) {
    ordina(a);
    int P[a->NumeroElementi];
    unsigned int ultimo = calcolaLA(a, P);
    arrayAttivita risultato;
    risultato.Array          = (attivita *)calloc(a->NumeroElementi, sizeof(attivita));
    risultato.NumeroElementi = 0;
    copiaLA(a, &risultato, P, ultimo);
    durataArrayAttivita(&risultato);
    printArrayAttivita(&risultato);
    printf("\n");
}

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
    selezioneDinamica(&a);
    return 0;
}

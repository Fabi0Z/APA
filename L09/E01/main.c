#include "attivita.h"
#include "smartfunctions.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Copia le attività della LA in un array di attività
void copiaLA(arrayAttivita *a, arrayAttivita *risultato, int *posizioni, unsigned int ultimo) {
    if (posizioni[ultimo] == (unsigned int)-1) {
        risultato->Array[risultato->NumeroElementi++] = a->Array[ultimo];
        return;
    }
    copiaLA(a, risultato, posizioni, posizioni[ultimo]);
    risultato->Array[risultato->NumeroElementi++] = a->Array[ultimo];
}

unsigned int calcolaLA(arrayAttivita *att, unsigned int *posizioni) {
    unsigned int i, j, ultimaDurata = 1, durate[att->NumeroElementi], last = 1, durateTemp[att->NumeroElementi];
    durate[0]    = att->Array[0].Durata;
    posizioni[0] = (unsigned int)-1;

    for (i = 1; i < (att->NumeroElementi); i++) {
        durateTemp[i] = att->Array[i].Durata;
        durate[i]     = att->Array[i].Durata;
        posizioni[i]  = -1;
        for (j = 0; j < i; j++)
            if (!attivitaSovvrapposta(&att->Array[i], &att->Array[j]) && (durate[i] < durateTemp[i] + durate[j])) {
                durate[i]    = durateTemp[i] + durate[j];
                posizioni[i] = j;
            }
        if (ultimaDurata <= durate[i]) {
            ultimaDurata = durate[i];
            last         = i;
        }
    }
    return last;
}

void selezioneDinamica(arrayAttivita *a) {
    ordina(a);
    unsigned int posizioni[a->NumeroElementi];
    unsigned int ultimo = calcolaLA(a, posizioni);
    arrayAttivita risultato;
    risultato.Array          = (attivita *)calloc(a->NumeroElementi, sizeof(attivita));
    risultato.NumeroElementi = 0;
    copiaLA(a, &risultato, posizioni, ultimo);
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

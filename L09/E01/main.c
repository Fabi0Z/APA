#include "attivita.h"
#include "smartfunctions.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void LIA_display(arrayAttivita *att, int *P, int i) {
    if (P[i] == -1) {
        printf("(%d,%d) ", att->Array[i].Inizio, att->Array[i].Fine);
        return;
    }
    LIA_display(att, P, P[i]);
    printf("(%d,%d) ", att->Array[i].Inizio, att->Array[i].Fine);
}

void LIA_calc(arrayAttivita *att) {
    int i, j, ris = 1, V[att->NumeroElementi], P[att->NumeroElementi], last = 1, TMP[att->NumeroElementi];
    V[0] = att->Array[0].Durata;
    P[0] = -1;
    TMP[0];

    for (i = 1; i < (att->NumeroElementi); i++) {
        TMP[i] = att->Array[i].Durata;
        V[i]   = att->Array[i].Durata;
        P[i]   = -1;
        for (j = 0; j < i; j++)
            if (attivitaSovvrapposta(&att->Array[i], &att->Array[j]) && (V[i] < TMP[i] + V[j])) {
                V[i] = TMP[i] + V[j];
                P[i] = j;
            }
        if (ris <= V[i]) {
            ris  = V[i];
            last = i;
        }
    }
    printf("Lunghezza: %d\nSequenza attività: ", ris);
    LIA_display(att, P, last);
}

void selezioneDinamica(arrayAttivita *a) {
    ordina(a);
    LIA_calc(a);
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
    puts("OLD");
    attSel(a.NumeroElementi, a.Array);
    puts("\nDinamica:\n");
    selezioneDinamica(&a);
    return 0;
}

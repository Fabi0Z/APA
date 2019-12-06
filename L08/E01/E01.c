#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "attivita.h"

// * CALCOLO COMBINATORIO
// TODO 
// * -------------------------------------------------------------

int main() {
    FILE *stream = fopen("att.txt", "r");
    checkFilestream(stream);

    uint8_t numeroAttivita;
    fscanf(stream, "%" SCNd8 "\n", &numeroAttivita);
    attivita a[numeroAttivita];
    leggiAttivita(stream, a, numeroAttivita);
    ordina(a, numeroAttivita);
    printArrayAttivita(a, numeroAttivita);
    return 0;
}

#include "pietra.h"

// Stampa una pietra
void printPietra(pietra p) {
    switch (p) {
        case zaffiro: {
            printf("Z");
            break;
        }

        case smeraldo: {
            printf("S");
            break;
        }

        case rubino: {
            printf("R");
            break;
        }

        case topazio: {
            printf("T");
            break;
        }
    }
}
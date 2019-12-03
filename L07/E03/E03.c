#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

const uint8_t MAX_STRING = 50;

typedef struct Personaggio *personaggioLink;
typedef struct Personaggio {
    uint16_t ID;
    char *Nome;
    char *Classe;
    uint16_t HP;
    uint16_t MP;
    uint16_t ATK;
    uint16_t DEF;
    uint16_t MAG;
    uint16_t SPR;
    personaggioLink Next;
} personaggio;

bool checkFilestream(FILE *stream) { // Controlla errori di apertura del file
    if (stream == NULL) {
        puts("Errore apertura file");
    }
    return false;
}

int main() {
    // Apro i filestream
    FILE *pg         = fopen("pg.txt", "r");
    FILE *inventario = fopen("inventario.txt", "R");

    // Verifico i filestream
    if (!checkFilestream(pg)) {
        return 1;
    }
    if (!checkFilestream(inventario)) {
        return 2;
    }

    return 0;
}

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

personaggioLink creaPersonaggioLink(personaggio *p) { // Salva un personaggio in un elemento di tipo personaggioLink
    // Alloco la memoria
    personaggioLink l = (personaggioLink)malloc(sizeof(personaggio));
    l->Nome           = (char *)calloc(strlen(p->Nome), sizeof(char));
    l->Classe         = (char *)calloc(strlen(p->Classe), sizeof(char));

    // Copio i dati
    *l = *p;
    strcpy(l->Nome, p->Nome);
    strcpy(l->Classe, p->Classe);

    return l;
}

personaggioLink parsePersonaggi(FILE *stream) { // Legge i personaggi da file e li salva in una lista
    personaggioLink head = (personaggioLink)malloc(sizeof(personaggio));
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

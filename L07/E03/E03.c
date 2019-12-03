#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t MAX_STRING = 50;

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
} personaggio;

typedef struct PersonaggioLink *personaggioLink;
typedef struct PersonaggioLink {
    personaggio Personaggio;
    personaggioLink Next;
} personaggioLink;

bool checkFilestream(FILE *stream) { // Controlla errori di apertura del file
    if (stream == NULL) {
        puts("Errore apertura file");
    }
    return false;
}

personaggio creaPersonaggio(uint16_t ID, char *Nome, char *Classe, uint16_t HP, uint16_t MP,
                            uint16_t ATK, uint16_t DEF, uint16_t MAG, uint16_t SPR) {
    // Crea un personaggio a partire dai dati in ingresso

    // Alloco i dati in memoria
    personaggio p;
    p.Nome   = (char *)calloc(strlen(Nome), sizeof(char));
    p.Classe = (char *)calloc(strlen(Classe), sizeof(char));

    // Copio il contenuto
    p.ID  = ID;
    p.HP  = HP;
    p.MP  = MP;
    p.ATK = ATK;
    p.DEF = DEF;
    p.MAG = MAG;
    p.SPR = SPR;
    strcpy(p.Nome, Nome);
    strcpy(p.Classe, Classe);

    return p;
}

personaggioLink creaPersonaggioLink(personaggio *p) { // Salva un personaggio in un elemento di tipo personaggioLink
    // Alloco la memoria
    personaggioLink l;
    l.Personaggio.Nome   = (char *)calloc(strlen(p->Nome), sizeof(char));
    l.Personaggio.Classe = (char *)calloc(strlen(p->Classe), sizeof(char));

    // Copio i dati
    l.Personaggio = *p;
    strcpy(l.Personaggio.Nome, p->Nome);
    strcpy(l.Personaggio.Classe, p->Classe);

    return l;
}

personaggioLink parsePersonaggi(FILE *stream) { // Legge i personaggi da file e li salva in una lista
    personaggioLink head = ;
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

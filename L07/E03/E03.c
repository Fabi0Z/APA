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

typedef struct PersonaggioLink personaggioLink;
typedef struct PersonaggioLink {
    personaggio *Personaggio;
    personaggioLink *Next;
} personaggioLink;

bool checkFilestream(FILE *stream) { // Controlla errori di apertura del file
    if (stream == NULL) {
        puts("Errore apertura file");
    }
    return false;
}

void allocaPersonaggio(personaggio *i, unsigned int nomeSize, unsigned int classeSize) { // Alloca memoria per un oggetto di tipo personaggio
    i->Nome   = (char *)calloc(nomeSize, sizeof(char));                                  // Alloco la memoria
    i->Classe = (char *)calloc(classeSize, sizeof(char));
}

personaggio *creaPersonaggio(uint16_t ID, char *Nome, char *Classe, uint16_t HP, uint16_t MP,
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
    l.Personaggio         = (personaggio *)malloc(sizeof(personaggio));
    l.Personaggio->Nome   = (char *)calloc(strlen(p->Nome), sizeof(char));
    l.Personaggio->Classe = (char *)calloc(strlen(p->Classe), sizeof(char));

    // Copio i dati
    *l.Personaggio = *p;
    strcpy(l.Personaggio->Nome, p->Nome);
    strcpy(l.Personaggio->Classe, p->Classe);

    return l;
}

bool leggiPersonaggio(char *string, personaggio *p) { // Effettua il parse di un personaggio da stringa, restituisce se la lettura è andata a buon fine o meno
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "PG%" SCNd16 "%[^\n]", &p->ID, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Nome, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Classe, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &p->HP, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &p->MP, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &p->ATK, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &p->DEF, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &p->MAG, string);
    conteggio += sscanf(string, "%" SCNd16, &p->SPR);
    return conteggio == 9;
}

void aggiungiDopo(personaggioLink *p, personaggioLink *next) { // Aggiunge next subito dopo p nella lista
    if (p->Next == NULL) {                                     // Se non ho personaggio successivo
        p->Next = *next;
        return;
    }

    personaggio *temp = p->Next;
    p->Next           = *next;
    next->Next        = temp;
}

personaggioLink parsePersonaggi(FILE *stream) { // Legge i personaggi da file e li salva in una lista
    personaggioLink head, *ultimoPersonaggio;
    head.Personaggio = NULL;

    // Creo PG temporaneo
    personaggio temp;
    temp.Nome   = (char *)calloc(MAX_STRING + 1, sizeof(char));
    temp.Classe = (char *)calloc(MAX_STRING + 1, sizeof(char));
    char string[MAX_STRING + 1];
    fgets(string, MAX_STRING, stream); // Leggo la prima riga del file

    while (leggiPersonaggio(string, &temp)) { // Sinché leggo correttamente i personaggi
        personaggioLink tempLink = creaPersonaggioLink(&temp);
        aggiungiDopo(ultimoPersonaggio, &tempLink);
    }
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

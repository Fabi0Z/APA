#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t MAX_STRING = 50;

typedef struct Oggetto {
    char *Nome;
    char *Tipo;
    uint16_t Statistica;
} oggetto;

typedef struct Inventario {
    oggetto *Oggetti;
    uint8_t NumeroOggetti;
    uint8_t OggettiTrasportabili;
} inventario;

typedef struct Equipaggiamento {
    bool Attivo;
    oggetto *Oggetti;
} equipaggiamento;

typedef struct Stats {
    uint16_t HP;
    uint16_t MP;
    uint16_t ATK;
    uint16_t DEF;
    uint16_t MAG;
    uint16_t SPR;
} stats;

typedef struct Personaggio {
    uint16_t ID;
    char *Nome;
    char *Classe;
    equipaggiamento *Equipaggiamento;
    stats Statistiche;
} personaggio;

typedef struct PersonaggioLink personaggioLink;
typedef struct PersonaggioLink {
    personaggio *Personaggio;
    personaggioLink *Next;
} personaggioLink;

typedef struct TabellaPersonaggio {
    personaggioLink *HEAD;
    personaggioLink *TAIL;
    unsigned int NumeroPersonaggi;
} tabellaPersonaggio;

bool checkFilestream(FILE *stream) { // Controlla errori di apertura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        return false;
    }
    return true;
}

void allocaPersonaggio(personaggio *p, unsigned int nomeSize, unsigned int classeSize) { // Alloca memoria per un oggetto di tipo personaggio
    p->Nome   = (char *)calloc(nomeSize, sizeof(char));                                  // Alloco la memoria
    p->Classe = (char *)calloc(classeSize, sizeof(char));
}

void freePersonaggio(personaggio *p) { // Dealloca la memoria di un personaggio
    free(p->Nome);
    free(p->Classe);
    free(p);
}

void printPersonaggio(personaggio *p, FILE *stream) { // Stampa un personaggio
    fprintf(stream, "PG%04" SCNd16, p->ID);
    fprintf(stream, " %s %s ", p->Nome, p->Classe);
    fprintf(stream, "%" SCNd16, p->Statistiche.HP);
    fprintf(stream, " %" SCNd16, p->Statistiche.MP);
    fprintf(stream, " %" SCNd16, p->Statistiche.ATK);
    fprintf(stream, " %" SCNd16, p->Statistiche.DEF);
    fprintf(stream, " %" SCNd16, p->Statistiche.MAG);
    fprintf(stream, " %" SCNd16, p->Statistiche.SPR);
    fprintf(stream, "\n");
}

void printPersonaggioLinkFile(personaggioLink *l, FILE *stream) { // Stampa una lista di personaggi su file
    puts("I personaggi presenti sono:");
    personaggioLink temp = *l;
    while (temp.Next != NULL) {                           // Sinché esiste un elemento successivo
        printPersonaggio(temp.Next->Personaggio, stream); // Stampo l'elemento
        temp = *temp.Next;                                // Passo all'elemento successivo in lista
    }
    printf("\n");
}

void printPersonaggioLink(personaggioLink *l) { // Stampa una lista di personaggi a video
    printPersonaggioLinkFile(l, stdout);
}

personaggioLink *creaLista(personaggio *p) { // Crea, alloca e restituisce un puntatore a personaggioLink
    personaggioLink *l = (personaggioLink *)malloc(sizeof(personaggioLink));
    l->Personaggio     = p;
    return l;
}

personaggio *creaPersonaggio(unsigned int nomeSize, unsigned int classeSize) { // Crea, alloca e restituisce un Item
    personaggio *temp = (personaggio *)malloc(sizeof(personaggio));
    allocaPersonaggio(temp, nomeSize, classeSize);
    return temp;
}

personaggioLink *creaPersonaggioLink(personaggio *p) { // Salva un personaggio in un elemento di tipo personaggioLink
    personaggioLink *l = (personaggioLink *)malloc(sizeof(personaggioLink));
    l->Personaggio     = p;
    return l;
}

bool leggiPersonaggio(char *string, personaggio *p) { // Effettua il parse di un personaggio da stringa, restituisce se la lettura è andata a buon fine o meno
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "PG%" SCNd16 "%[^\n]", &p->ID, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Nome, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Classe, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &p->Statistiche.HP, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &p->Statistiche.MP, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &p->Statistiche.ATK, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &p->Statistiche.DEF, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &p->Statistiche.MAG, string);
    conteggio += sscanf(string, "%" SCNd16, &p->Statistiche.SPR);
    return conteggio == 17;
}

void copiaEquipaggiamento(equipaggiamento *a, equipaggiamento *b) { // Copia l'equipaggiamento a in b

    // Copio i dati diretti
    b->ID          = a->ID;
    b->Statistiche = a->Statistiche;

    // Copio i dati per puntatore
    strcpy(b->Nome, a->Nome);
    strcpy(b->Classe, a->Classe);
}

void copiaPersonaggio(personaggio *a, personaggio *b) { // Copia il personaggio a in b

    // Copio i dati diretti
    b->ID          = a->ID;
    b->Statistiche = a->Statistiche;

    // Copio i dati per puntatore
    strcpy(b->Nome, a->Nome);
    strcpy(b->Classe, a->Classe);
    copiaEquipaggiamento(a->Equipaggiamento, b->Equipaggiamento);
}

personaggio *getResizedPersonaggio(personaggio *temp) { // Alloca memoria per realizzare una copia ridimensionata del personaggio
    personaggio *p = creaPersonaggio(strlen(temp->Nome), strlen(temp->Classe));
    return p;
}

void addNext(personaggioLink *l, personaggioLink *next) { // Aggiunge un elemento next subito dopo un elemento l in una lista
    if (l->Next == NULL) {                                // Se si tratta dell'ultimo elemento
        l->Next    = next;
        next->Next = NULL;
        return;
    }

    personaggioLink *temp = l->Next;
    next->Next            = temp;
    l->Next               = next;
    return;
}

void parsePersonaggi(tabellaPersonaggio *TABLE, FILE *stream) { // Legge i personaggi da file e li salva in una lista
    personaggio *temp = creaPersonaggio(MAX_STRING, MAX_STRING);
    personaggioLink *tempList;

    // Creo stringa di appoggio
    char string[MAX_STRING + 1];
    fgets(string, MAX_STRING, stream); // Leggo la prima riga del file

    while (leggiPersonaggio(string, temp)) { // Sinché leggo correttamente i personaggi
        personaggio *p = getResizedPersonaggio(temp);
        copiaPersonaggio(temp, p);
        tempList = creaPersonaggioLink(p);
        addNext(TABLE->TAIL, tempList);
        TABLE->NumeroPersonaggi++;
        TABLE->TAIL = tempList;
        fgets(string, MAX_STRING, stream); // Leggo la riga successiva
    }

    freePersonaggio(temp);
}

int main() {
    // Apro i filestream
    FILE *pg         = fopen("pg.txt", "r");
    FILE *inventario = fopen("inventario.txt", "r");

    // Verifico i filestream
    if (!checkFilestream(pg)) {
        return 1;
    }
    if (!checkFilestream(inventario)) {
        return 2;
    }

    tabellaPersonaggio table;
    table.HEAD             = creaLista(NULL);
    table.TAIL             = table.HEAD;
    table.NumeroPersonaggi = 0;
    parsePersonaggi(&table, pg);
    printPersonaggioLink(table.HEAD);

    return 0;
}

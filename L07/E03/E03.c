#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t MAX_STRING = 50;

typedef struct Stats {
    int16_t HP;
    int16_t MP;
    int16_t ATK;
    int16_t DEF;
    int16_t MAG;
    int16_t SPR;
} stats;

typedef struct Oggetto {
    char *Nome;
    char *Tipo;
    stats Statistiche;
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

void allocaOggetto(oggetto *o, unsigned int nomeSize, unsigned int tipoSize) { // Alloca memoria per un oggetto di tipo oggetto
    o->Nome = (char *)calloc(nomeSize, sizeof(char));                          // Alloco la memoria
    o->Tipo = (char *)calloc(tipoSize, sizeof(char));
}

void freeOggetto(oggetto *o) { // Dealloca un elemento di tipo oggetto
    free(o->Nome);
    free(o->Tipo);
    free(o);
}

void freeEquipaggiamento(equipaggiamento *e) { // Dealloca un elemento di tipo equipaggiamento
    freeOggetto(e->Oggetti);
    free(e);
}

void freePersonaggio(personaggio *p) { // Dealloca la memoria di un personaggio
    free(p->Nome);
    free(p->Classe);
    if (p->Equipaggiamento != NULL) { // Se è presente un equipaggiamento
        freeEquipaggiamento(p->Equipaggiamento);
    }
    free(p);
}

void freePersonaggioLink(personaggioLink *l) { // Dealloca la memoria di una lista ed il suo contenuto
    if (l->Personaggio != NULL) {              // Se non sono sulla HEAD
        freePersonaggio(l->Personaggio);
    }
    free(l);
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

oggetto *creaOggetto(unsigned int nomeSize, unsigned int tipoSize) { // Crea, alloca e restituisce un oggetto
    oggetto *temp = (oggetto *)malloc(sizeof(oggetto));
    allocaOggetto(temp, nomeSize, tipoSize);
    return temp;
}

personaggio *creaPersonaggio(unsigned int nomeSize, unsigned int classeSize) { // Crea, alloca e restituisce un personaggio senza equipaggiamento
    personaggio *temp     = (personaggio *)malloc(sizeof(personaggio));
    temp->Equipaggiamento = NULL;
    allocaPersonaggio(temp, nomeSize, classeSize);
    return temp;
}

personaggioLink *creaPersonaggioLink(personaggio *p) { // Salva un personaggio in un elemento di tipo personaggioLink
    personaggioLink *l = (personaggioLink *)malloc(sizeof(personaggioLink));
    l->Personaggio     = p;
    return l;
}

bool leggiStatistiche(char *string, stats *s) { // Effettua il parse delle statistiche da stringa
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &s->HP, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &s->MP, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &s->ATK, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &s->DEF, string);
    conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &s->MAG, string);
    conteggio += sscanf(string, "%" SCNd16, &s->SPR);
    return conteggio == 11;
}

bool leggiPersonaggio(char *string, personaggio *p) { // Effettua il parse di un personaggio da stringa, restituisce se la lettura è andata a buon fine o meno
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "PG%" SCNd16 "%[^\n]", &p->ID, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Nome, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Classe, string);

    stats s;
    if (!leggiStatistiche(string, &s)) { // Se la lettura delle statistiche fallisce
        return false;
    }
    p->Statistiche = s;

    return conteggio == 6;
}

bool leggiOggetto(char *string, oggetto *o) { // Effettua il parse di un personaggio da stringa, restituisce se la lettura è andata a buon fine o meno
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "%s %[^\n]", o->Nome, string);
    conteggio += sscanf(string, "%s %[^\n]", o->Tipo, string);

    stats s;
    if (!leggiStatistiche(string, &s)) { // Se la lettura delle statistiche fallisce
        return false;
    }
    o->Statistiche = s;

    return conteggio == 4;
}

void copiaEquipaggiamento(equipaggiamento *a, equipaggiamento *b) { // Copia l'equipaggiamento a in b

    // Copio i dati diretti
    b->Attivo = a->Attivo;

    // Copio i dati per puntatore
    memcpy(b->Oggetti, a->Oggetti, sizeof(equipaggiamento));
}

void copiaPersonaggio(personaggio *a, personaggio *b) { // Copia il personaggio a in b

    // Copio i dati diretti
    b->ID          = a->ID;
    b->Statistiche = a->Statistiche;

    // Copio i dati per puntatore
    strcpy(b->Nome, a->Nome);
    strcpy(b->Classe, a->Classe);
    if (a->Equipaggiamento != NULL) { // Se è presente l'equipaggiamento
        copiaEquipaggiamento(a->Equipaggiamento, b->Equipaggiamento);
    } else {
        b->Equipaggiamento = NULL;
    }
}

personaggio *getResizedPersonaggio(personaggio *temp) { // Alloca memoria per realizzare una copia ridimensionata del personaggio
    personaggio *p = creaPersonaggio(strlen(temp->Nome), strlen(temp->Classe));
    return p;
}

void copiaOggetto(oggetto *dest, oggetto *src) { // Copia src in dest
    dest->Statistiche = src->Statistiche;
    strcpy(dest->Nome, src->Nome);
    strcpy(dest->Tipo, src->Tipo);
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

inventario parseInventario(FILE *stream) { // Effettua il parse dell'inventario
    inventario inv;
    fscanf(stream, "%" SCNd8 "\n", &inv.NumeroOggetti);
    inv.Oggetti = (oggetto *)calloc(inv.NumeroOggetti, sizeof(oggetto));
    char string[MAX_STRING + 1];
    oggetto *temp = creaOggetto(MAX_STRING, MAX_STRING);

    for (size_t i = 0; i < inv.NumeroOggetti; i++) { // Per ogni oggetto nel file
        fgets(string, MAX_STRING, stream);           // Leggo la riga successiva
        leggiOggetto(string, temp);
        allocaOggetto(&inv.Oggetti[i], strlen(temp->Nome), strlen(temp->Tipo)); // Alloco la memoria necessaria
        copiaOggetto(&inv.Oggetti[i], temp);
    }
    freeOggetto(temp);

    return inv;
}

int main() {
    // Apro i filestream
    FILE *pg  = fopen("pg.txt", "r");
    FILE *inv = fopen("inventario.txt", "r");

    // Verifico i filestream
    if (!checkFilestream(pg)) {
        return 1;
    }
    if (!checkFilestream(inv)) {
        return 2;
    }

    // Creo e inizializzo la tabella dei personaggi
    tabellaPersonaggio table;
    table.HEAD             = creaLista(NULL);
    table.TAIL             = table.HEAD;
    table.NumeroPersonaggi = 0;
    parsePersonaggi(&table, pg);
    printPersonaggioLink(table.HEAD);

    // Creo e inizializzo l'array per l'inventario
    inventario inventory = parseInventario(inv);

    return 0;
}

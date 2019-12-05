#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// * VARIABILI GLOBALI
const uint8_t MAX_STRING        = 50;
const uint8_t MAX_TRASPORTABILI = 8;
typedef enum { HP,
               MP,
               ATK,
               DEF,
               MAG,
               SPR,
               N_STATISTICHE } stats;
// * --------------------------------------------------------

// * STRUTTURE
typedef struct Oggetto {
    char *Nome;
    char *Tipo;
    int16_t Statistiche[N_STATISTICHE];
} oggetto;
typedef struct Inventario {
    oggetto *Oggetti;
    uint8_t NumeroOggetti;
    uint8_t OggettiTrasportabili;
} inventario;
typedef struct Equipaggiamento {
    oggetto **Oggetti;
    uint8_t NumeroOggetti;
} equipaggiamento;
typedef struct Personaggio {
    uint16_t ID;
    char *Nome;
    char *Classe;
    equipaggiamento Equipaggiamento;
    int16_t Statistiche[N_STATISTICHE];
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
// * --------------------------------------------------------

// * FUNZIONI GENERALI E CONTROLLI
void premiPerContinuare() {
    puts("Premi qualisiasi tasto per continuare...");
    getchar();
    getchar();
}
bool checkFilestream(FILE *stream) { // Controlla errori di apertura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        return false;
    }
    return true;
}
bool checkLimiteEquipaggiamento(personaggio *p, inventario *i) { // Controlla se un personaggio ha raggiunto il limite di oggetti equipaggiabili
    return p->Equipaggiamento.NumeroOggetti >= i->OggettiTrasportabili;
}
// * --------------------------------------------------------

// * ALLOCAZIONE E DEALLOCAZIONE DATI
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
void freePersonaggio(personaggio *p) {        // Dealloca la memoria di un personaggio
    if (p->Equipaggiamento.Oggetti != NULL) { // Se è presente un equipaggiamento
        free(p->Equipaggiamento.Oggetti);
    }
    free(p->Nome);
    free(p->Classe);
    free(p);
}
void freePersonaggioLink(personaggioLink *l) { // Dealloca la memoria di una lista ed il suo contenuto
    if (l->Personaggio != NULL) {              // Se non sono sulla HEAD
        freePersonaggio(l->Personaggio);
    }
    free(l);
}
// * --------------------------------------------------------

// * STAMPA DATI
void printStatistiche(int16_t *s, FILE *stream) { // Stampa delle statistiche
    for (size_t i = 0; i < N_STATISTICHE; i++) {  // Per ogni statistica
        fprintf(stream, "%" SCNd16 " ", s[i]);
    }
}
void printPersonaggio(personaggio *p, FILE *stream) { // Stampa un personaggio
    fprintf(stream, "PG%04" SCNd16, p->ID);
    fprintf(stream, " %s %s ", p->Nome, p->Classe);
    printStatistiche(p->Statistiche, stream);
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
void printOggetto(oggetto *o, FILE *stream) { // Stampa un oggetto su file
    fprintf(stream, "%s %s ", o->Nome, o->Tipo);
    printStatistiche(o->Statistiche, stream);
    fprintf(stream, "\n");
}
void printInventarioFile(inventario *inv, FILE *stream, bool indici) { // Stampa un inventario su file
    if (stream != stdout) {                                            // Se non sono sullo stdout
        fprintf(stream, "%" SCNd8 "\n", inv->NumeroOggetti);
    }

    for (size_t i = 0; i < inv->NumeroOggetti; i++) { // Per ogni oggetto
        if (indici) {
            fprintf(stream, "%zu - ", i);
        }
        printOggetto(&inv->Oggetti[i], stream);
    }

    printf("\n");
}
void printInventario(inventario *i, bool indici) { // Stampa un inventario a video
    puts("L'inventario è composto da:");
    printInventarioFile(i, stdout, indici);
}
void printEquipaggiamentoFile(equipaggiamento *e, FILE *stream, bool indici) { // Stampa un equipaggiamento su file
    for (size_t i = 0; i < e->NumeroOggetti; i++) {                            // Per ogni oggetto
        if (indici) {
            fprintf(stream, "%zu - ", i);
        }
        printOggetto(e->Oggetti[i], stream);
    }
    printf("\n");
}
void printEquipaggiamento(equipaggiamento *e, bool indici) { // Stampa un equipaggiamento a video
    puts("L'equipaggiamento è composto da:");
    printEquipaggiamentoFile(e, stdout, indici);
}
// * --------------------------------------------------------

// * CREAZIONE E MANIPOLAZIONE OGGETTI
personaggioLink *getNextItem(personaggioLink *item) { // Restituisce l'elemento successivo nella lista
    return item->Next == NULL ? NULL : item->Next;
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
    personaggio *temp                   = (personaggio *)malloc(sizeof(personaggio));
    temp->Equipaggiamento.Oggetti       = NULL;
    temp->Equipaggiamento.NumeroOggetti = 0;
    allocaPersonaggio(temp, nomeSize, classeSize);
    return temp;
}
personaggioLink *creaPersonaggioLink(personaggio *p) { // Salva un personaggio in un elemento di tipo personaggioLink
    personaggioLink *l = (personaggioLink *)malloc(sizeof(personaggioLink));
    l->Personaggio     = p;
    return l;
}
void copiaEquipaggiamento(equipaggiamento *a, equipaggiamento *b) { // Copia l'equipaggiamento a in b
    // Se vi sono oggetti
    if (a->NumeroOggetti = 0) {
        b->NumeroOggetti = 0;
        if (b->Oggetti != NULL) {
            free(b->Oggetti);
            b->Oggetti == NULL;
        }
        return;
    }
    b->NumeroOggetti = a->NumeroOggetti;
    memcpy(b->Oggetti, a->Oggetti, sizeof(oggetto **) * a->NumeroOggetti);
}
void copiaPersonaggio(personaggio *a, personaggio *b) { // Copia il personaggio a in b

    // Copio i dati diretti
    b->ID = a->ID;

    // Copio i dati per puntatore
    strcpy(b->Nome, a->Nome);
    strcpy(b->Classe, a->Classe);
    memcpy(b->Statistiche, a->Statistiche, sizeof(int16_t) * N_STATISTICHE);
    copiaEquipaggiamento(&a->Equipaggiamento, &b->Equipaggiamento);
}
personaggio *getResizedPersonaggio(personaggio *temp) { // Alloca memoria per realizzare una copia ridimensionata del personaggio
    personaggio *p = creaPersonaggio(strlen(temp->Nome), strlen(temp->Classe));
    return p;
}
void copiaOggetto(oggetto *dest, oggetto *src) { // Copia src in dest
    memcpy(dest->Statistiche, src->Statistiche, sizeof(int16_t) * N_STATISTICHE);
    strcpy(dest->Nome, src->Nome);
    strcpy(dest->Tipo, src->Tipo);
}
bool aggiungiEquipaggiamento(personaggio *p, oggetto *o) { // Aggiunge un oggetto all'equipaggiamento di un personaggio
    if (p->Equipaggiamento.NumeroOggetti == 0) {           // Se non ho oggetti
        p->Equipaggiamento.NumeroOggetti++;
        p->Equipaggiamento.Oggetti    = (oggetto **)calloc(p->Equipaggiamento.NumeroOggetti, sizeof(oggetto *));
        p->Equipaggiamento.Oggetti[0] = o;
        return true;
    }

    // Creo nuovo array oggetti
    oggetto **new = (oggetto **)calloc(p->Equipaggiamento.NumeroOggetti + 1, sizeof(oggetto *));
    memcpy(new, p->Equipaggiamento.Oggetti, sizeof(oggetto *) * p->Equipaggiamento.NumeroOggetti); // Copio i dati

    // Metto il link all'oggetto
    new[p->Equipaggiamento.NumeroOggetti] = o;
    p->Equipaggiamento.NumeroOggetti++; // Incremento gli oggetti disponibili

    // Sostituisco l'array di oggetti
    free(p->Equipaggiamento.Oggetti);
    p->Equipaggiamento.Oggetti = new;
    return true;
}
bool rimuoviEquipaggiamento(personaggio *p, uint8_t indiceOggetto) { // Rimuove un oggetto dall'equipaggiamento di un personaggio
    p->Equipaggiamento.NumeroOggetti--;
    for (uint8_t i = indiceOggetto; i < p->Equipaggiamento.NumeroOggetti; i++) { // Per ogni oggetto successivo
        p->Equipaggiamento.Oggetti[i] = p->Equipaggiamento.Oggetti[i + 1];
    }
    if (p->Equipaggiamento.NumeroOggetti == 0) { // Se ho 0 oggetti
        free(p->Equipaggiamento.Oggetti);
        p->Equipaggiamento.Oggetti = NULL;
    } else {
        p->Equipaggiamento.Oggetti = realloc(p->Equipaggiamento.Oggetti, p->Equipaggiamento.NumeroOggetti);
    }
}
void calcolaStatistiche(personaggio *p, int16_t *s) {           // Calcola e restituisce le statistiche di un personaggio
    memcpy(s, p->Statistiche, sizeof(int16_t) * N_STATISTICHE); // Scrivo i valori del personaggio

    if (p->Equipaggiamento.NumeroOggetti == 0) { // Se non ci sono oggetti nell'equipaggiamento mi interrompo
        return;
    }

    oggetto *o;
    for (size_t i = 0; i < N_STATISTICHE; i++) {                        // Per ogni statistica
        for (size_t j = 0; j < p->Equipaggiamento.NumeroOggetti; j++) { // Per ogni oggetto dell'equipaggiamento
            o = p->Equipaggiamento.Oggetti[j];
            s[i] += o->Statistiche[i];
        }

        if (s[i] < 1) {
            s[i] = 1;
        }
    }
}
// * --------------------------------------------------------

// * LETTURA DA FILE
bool leggiStatistiche(char *string, int16_t *s) { // Effettua il parse delle statistiche da stringa
    uint8_t conteggio = 0;
    for (size_t i = 0; i < N_STATISTICHE; i++) { // Per ogni statistica
        conteggio += sscanf(string, "%" SCNd16 "%[^\n]", &s[i], string);
    }
    return conteggio == 11;
}
bool leggiPersonaggio(char *string, personaggio *p) { // Effettua il parse di un personaggio da stringa, restituisce se la lettura è andata a buon fine o meno
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "PG%" SCNd16 "%[^\n]", &p->ID, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Nome, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Classe, string);

    int16_t s[N_STATISTICHE];
    if (!leggiStatistiche(string, s)) { // Se la lettura delle statistiche fallisce
        return false;
    }
    memcpy(p->Statistiche, s, sizeof(int16_t) * N_STATISTICHE);
    return conteggio == 6;
}
bool leggiOggetto(char *string, oggetto *o) { // Effettua il parse di un personaggio da stringa, restituisce se la lettura è andata a buon fine o meno
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "%s %[^\n]", o->Nome, string);
    conteggio += sscanf(string, "%s %[^\n]", o->Tipo, string);

    int16_t s[N_STATISTICHE];
    if (!leggiStatistiche(string, s)) { // Se la lettura delle statistiche fallisce
        return false;
    }
    memcpy(o->Statistiche, s, sizeof(int16_t) * N_STATISTICHE);
    return conteggio == 4;
}
// * --------------------------------------------------------

// * LISTE
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
personaggioLink *ricercaID(personaggioLink *HEAD, uint16_t *ID) { // Ricerca ricorsiva che restituisce l'elemento precedete a quello trovato
    personaggioLink *pointer = getNextItem(HEAD);
    if (pointer == NULL) { // Condizione di terminazione (lista vuota)
        return NULL;
    }

    if (pointer->Next == NULL) { // Condizione di terminazione (lista di un elemento)
        return pointer->Personaggio->ID == *ID ? HEAD : NULL;
    }

    if (pointer->Personaggio->ID == *ID) { // Se ho trovato la corrispondenza
        return HEAD;
    }

    return ricercaID(pointer, ID); // Ricerco sull'elemento successivo
}
personaggioLink *estraiNext(personaggioLink *previous) { // Estrae l'elemento successivo in lista
    personaggioLink *elemento = previous->Next;
    previous->Next            = elemento->Next;
    return elemento;
}
void eliminaAndPrint(personaggioLink *previous) { // Estrare l'elemento successivo a quello dato da una lista, lo stampa e libera la memoria
    previous = estraiNext(previous);
    printf("L'elemento eliminato è ---> ");
    printPersonaggio(previous->Personaggio, stdout);
    freePersonaggioLink(previous);
}
// * --------------------------------------------------------

void parsePersonaggi(tabellaPersonaggio *TABLE, FILE *stream) { // Legge i personaggi da file e li salva in una lista
    personaggio *temp = creaPersonaggio(MAX_STRING, MAX_STRING);
    personaggioLink *tempList;

    // Creo stringa di appoggio
    char string[(MAX_STRING * 3) + 1];
    fgets(string, MAX_STRING * 3, stream); // Leggo la prima riga del file

    while (leggiPersonaggio(string, temp)) { // Sinché leggo correttamente i personaggi
        personaggio *p = getResizedPersonaggio(temp);
        copiaPersonaggio(temp, p);
        tempList = creaPersonaggioLink(p);
        addNext(TABLE->TAIL, tempList);
        TABLE->NumeroPersonaggi++;
        TABLE->TAIL = tempList;
        fgets(string, MAX_STRING * 3, stream); // Leggo la riga successiva
    }

    freePersonaggio(temp);
}
inventario parseInventario(FILE *stream) { // Effettua il parse dell'inventario
    inventario inv;
    fscanf(stream, "%" SCNd8 "\n", &inv.NumeroOggetti);
    inv.Oggetti = (oggetto *)calloc(inv.NumeroOggetti, sizeof(oggetto));
    char string[(MAX_STRING * 3) + 1];
    oggetto *temp = creaOggetto(MAX_STRING, MAX_STRING);

    for (size_t i = 0; i < inv.NumeroOggetti; i++) { // Per ogni oggetto nel file
        fgets(string, MAX_STRING * 2, stream);       // Leggo la riga successiva
        leggiOggetto(string, temp);
        allocaOggetto(&inv.Oggetti[i], strlen(temp->Nome), strlen(temp->Tipo)); // Alloco la memoria necessaria
        copiaOggetto(&inv.Oggetti[i], temp);
    }
    freeOggetto(temp);

    return inv;
}

int promptMenu(tabellaPersonaggio *TABLE, inventario *INVENTORY) {
    enum opzioneMenu { caricaPersonaggi,
                       caricaInventario,
                       aggiungiPersonaggio,
                       eliminaPersonaggio,
                       modificaEquipaggiamento,
                       contaStatistiche,
                       stampaPersonaggi,
                       stampaInventario,
                       stampaEquipaggiamento };
    uint8_t lettura;

    while (true) {
        puts("0 - Carica i personaggi dal file");
        puts("1 - Carica l'inventario dal file");
        puts("2 - Aggiungi un personaggio");
        puts("3 - Elimina un personaggio");
        puts("4 - Aggiungi/Rimuovi un oggetto dall'equipaggiamento di un personaggio");
        puts("5 - Calcola le statistiche di un personaggio con i modificatori");
        puts("6 - Stampa la lista dei personaggi");
        puts("7 - Stampa l'inventario");
        puts("8 - Stampa l'equipaggiamento di un personaggio");
        puts("\nPremi CTRL + C per uscire");
        printf("==> ");

        scanf("%" SCNd8, &lettura);
        printf("\n");
        switch (lettura) {
            case caricaPersonaggi: {
                FILE *pg = fopen("pg.txt", "r");
                // Verifico i filestream
                if (!checkFilestream(pg)) {
                    return 1;
                }
                parsePersonaggi(TABLE, pg);
                fclose(pg);
                break;
            }

            case caricaInventario: {
                FILE *inv = fopen("inventario.txt", "r");
                // Verifico i filestream
                if (!checkFilestream(inv)) {
                    return 2;
                }
                *INVENTORY = parseInventario(inv);
                fclose(inv);
                INVENTORY->OggettiTrasportabili = MAX_TRASPORTABILI;
                break;
            }

            case aggiungiPersonaggio: {
                puts("Inserisci i dati del personaggio:");
                printf("==> ");
                getchar();
                parsePersonaggi(TABLE, stdin);
            }

            case eliminaPersonaggio: {
                printPersonaggioLink(TABLE->HEAD);
                puts("Inserisci l'ID del personaggio da eliminare (senza \"PG\" davanti):");
                printf("==> ");
                uint16_t ID;
                getchar();
                scanf("%" SCNd16, &ID);                                    // Leggo l'ID
                personaggioLink *precedente = ricercaID(TABLE->HEAD, &ID); // Trovo l'elemento precedente
                if (precedente != NULL) {                                  // Se ho trovato l'ID
                    eliminaAndPrint(precedente);

                } else {
                    puts("ID non trovato");
                }
                premiPerContinuare();
                break;
            }

            case modificaEquipaggiamento: {
                printPersonaggioLink(TABLE->HEAD);
                // Leggo il personaggio
                puts("Inserisci l'ID del personaggio a cui modificare l'equipaggiamento (senza \"PG\" davanti):");
                printf("==> ");
                uint16_t ID;
                getchar();
                scanf("%" SCNd16, &ID);                                    // Leggo l'ID
                personaggioLink *precedente = ricercaID(TABLE->HEAD, &ID); // Trovo l'elemento precedente
                if (precedente == NULL) {                                  // Se non ho trovato l'ID
                    puts("ID non trovato");
                    premiPerContinuare();
                    break;
                }
                personaggio *pg = precedente->Next->Personaggio;
                puts("Questi sono gli oggetti presenti nell'equipaggiamento:");
                printEquipaggiamento(&pg->Equipaggiamento, false); // Stampo l'equipaggiamento
                premiPerContinuare();

                // Leggo l'azione dell'utente
                puts("Inserisci 1 per aggiungere un oggetto o 0 per rimuoverlo");
                printf("==> ");
                uint8_t scelta;
                scanf("%" SCNd8, &scelta);

                if (scelta == 0) {                                // Se l'utente desidera rimuovere
                    if (pg->Equipaggiamento.NumeroOggetti == 0) { // Se l'equipaggiamento è vuoto
                        puts("Non è possibile rimuovere oggetti a questo personaggio");
                        premiPerContinuare();
                        break;
                    }

                    printEquipaggiamento(&pg->Equipaggiamento, true); // Stampo l'equipaggiamento con gli indici
                    puts("Inserisci il numero dell'oggetto");
                    printf("==> ");
                    scanf("%" SCNd8, &scelta);
                    if (scelta >= pg->Equipaggiamento.NumeroOggetti) { // Controllo la validità della scelta
                        puts("Scelta non valida");
                        premiPerContinuare();
                        break;
                    }

                    rimuoviEquipaggiamento(pg, scelta);
                    puts("Oggetto rimosso!");
                } else if (scelta == 1) {                            // Se l'utente desidera aggiungere
                    if (checkLimiteEquipaggiamento(pg, INVENTORY)) { // Se l'equipaggiamento è pieno
                        puts("Non è possibile aggiungere oggetti a questo personaggio");
                        premiPerContinuare();
                        break;
                    }

                    printInventario(INVENTORY, true); // Stampo l'inventario con gli indici
                    puts("Inserisci il numero dell'oggetto");
                    printf("==> ");
                    scanf("%" SCNd8, &scelta);
                    if (scelta >= INVENTORY->NumeroOggetti) { // Controllo la validità della scelta
                        puts("Scelta non valida");
                        premiPerContinuare();
                        break;
                    }

                    aggiungiEquipaggiamento(pg, &INVENTORY->Oggetti[scelta]);
                    puts("Oggetto aggiunto!");
                } else { // Se la scelta non è valida
                    puts("Scelta non valida!");
                }
                premiPerContinuare();
                break;
            }

            case contaStatistiche: {
                printPersonaggioLink(TABLE->HEAD);
                puts("Inserisci l'ID del personaggio di cui vuoi calcolare le statistiche (senza \"PG\" davanti):");
                printf("==> ");
                uint16_t ID;
                getchar();
                scanf("%" SCNd16, &ID);                                    // Leggo l'ID
                personaggioLink *precedente = ricercaID(TABLE->HEAD, &ID); // Trovo il pg
                if (precedente != NULL) {                                  // Se ho trovato l'ID
                    personaggio *pg = getNextItem(precedente)->Personaggio;
                    int16_t s[N_STATISTICHE];
                    calcolaStatistiche(pg, s);
                    puts("Le statistiche sono");
                    printf("==> ");
                    printStatistiche(s, stdout);
                    printf("\n");

                } else {
                    puts("ID non trovato");
                }
                premiPerContinuare();
                break;
            }

            case stampaPersonaggi: {
                printPersonaggioLink(TABLE->HEAD);
                premiPerContinuare();
                break;
            }

            case stampaInventario: {
                printInventario(INVENTORY, false);
                premiPerContinuare();
                break;
            }

            case stampaEquipaggiamento: {
                printPersonaggioLink(TABLE->HEAD);
                puts("Inserisci l'ID del personaggio di cui vuoi stampare l'equipaggiamento (senza \"PG\" davanti):");
                printf("==> ");
                uint16_t ID;
                getchar();
                scanf("%" SCNd16, &ID);                                         // Leggo l'ID
                personaggioLink *precedente = ricercaID(TABLE->HEAD, &ID); // Trovo il pg
                if (precedente != NULL) {   // Se ho trovato l'ID
                    equipaggiamento *e = &precedente->Next->Personaggio->Equipaggiamento;                                         
                    printEquipaggiamento(e, false);

                } else {
                    puts("ID non trovato");
                }
                premiPerContinuare();
                break;
            }

            default: {
                puts("Opzione non valida!");
                premiPerContinuare();
                break;
            }
        }
    }
}

int main() {
    // Creo e inizializzo la tabella dei personaggi
    tabellaPersonaggio table;
    table.HEAD             = creaLista(NULL);
    table.TAIL             = table.HEAD;
    table.NumeroPersonaggi = 0;

    // Creo e inizializzo l'array per l'inventario
    inventario inventory;

    // Apro il menu
    return promptMenu(&table, &inventory);
}

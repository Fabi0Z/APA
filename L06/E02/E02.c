#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t MAX_STRING = 50;
typedef enum { inserimentoTastiera,
               inserimentoFile,
               ricerca,
               estrazione,
               estrazioneRange,
               printFile,
               printVideo
} sceltaMenu;

typedef struct Data { // Dimensione totale 4 byte, 4 in meno rispetto al salvare la data come stringa
    uint8_t Giorno;   // 1 byte
    uint8_t Mese;     // 1 byte
    uint16_t Anno;    // 2 byte
} data;

typedef struct ItemStruct { // Spazio massimo 12 byte + 4*MAX_STRING
    uint16_t Codice;        // 4 byte
    char *Nome;
    char *Cognome;
    data Nascita; // 4 byte
    char *Via;
    char *Città;
    uint32_t CAP; // 4 Byte
} Item;

typedef struct ListaAnagrafica listaAnagrafica;
typedef struct ListaAnagrafica { // Lista rappresentante le anagrafiche
    Item *Contenuto;
    listaAnagrafica *Next;
} listaAnagrafica;

void allocaItem(Item *i, unsigned int nomeSize, unsigned int cognomeSize, unsigned int viaSize, unsigned int cittàSize) { // Alloca memoria per un oggetto di tipo Item
    i->Nome    = (char *)calloc(nomeSize, sizeof(char));                                                                  // Alloco la memoria
    i->Cognome = (char *)calloc(cognomeSize, sizeof(char));
    i->Via     = (char *)calloc(viaSize, sizeof(char));
    i->Città   = (char *)calloc(cittàSize, sizeof(char));
}

void freeItem(Item *i) { // Dealloca la memoria di un Item
    free(i->Nome);
    free(i->Cognome);
    free(i->Via);
    free(i->Città);
    free(i);
}

void freeListaItem(listaAnagrafica *l) { // Dealloca la memoria di una lista ed il suo contenuto
    if (l->Contenuto != NULL) { // Se non sono sulla HEAD
        freeItem(l->Contenuto);
    }
    free(l);
}

Item *creaItem(unsigned int nomeSize, unsigned int cognomeSize, unsigned int viaSize, unsigned int cittàSize) { // Crea, alloca e restituisce un Item
    Item *temp = (Item *)malloc(sizeof(Item));
    allocaItem(temp, nomeSize, cognomeSize, viaSize, cittàSize);
    return temp;
}

void copiaItem(Item *a, Item *b) { // Copia l'item a in b
                                   // Copio i dati per variabile
    b->Codice  = a->Codice;
    b->Nascita = a->Nascita;
    b->CAP     = a->CAP;

    // Copio i dati per puntatore
    strcpy(b->Nome, a->Nome);
    strcpy(b->Cognome, a->Cognome);
    strcpy(b->Via, a->Via);
    strcpy(b->Città, a->Città);
}

unsigned int confrontaData(listaAnagrafica *list1, listaAnagrafica *list2) { // Confronta due elementi di tipo data e restituisce true se il primo è maggiore al secondo
    if (list1->Contenuto == NULL) {                                          // Se sono sulla HEAD
        return true;
    }

    data *a = &list1->Contenuto->Nascita;
    data *b = &list2->Contenuto->Nascita;

    if (a->Anno > b->Anno) { // Se Anno è maggiore
        return true;
    } else if (a->Anno < b->Anno) { // Se Anno è minore
        return false;
    }

    // Se arrivo qui Anno è uguale
    if (a->Mese > b->Mese) { // Se Mese è maggiore
        return true;
    } else if (a->Mese < b->Mese) { // Se Mese è minore
        return false;
    }

    // Se arrivo qui Mese è uguale
    return a->Giorno > b->Giorno;
}

bool checkFilestream(FILE *stream) { // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return false;
}

bool leggiRiga(FILE *stream, Item *dato) { // Legge una riga dal file di input e la salva su una variabile per riferimento
    uint8_t elementiLetti = 0;
    elementiLetti += fscanf(stream, "A%04" SCNd16, &dato->Codice);
    elementiLetti += fscanf(stream, "%s %s", dato->Nome, dato->Cognome);
    elementiLetti += fscanf(stream, "%02" SCNd8 "/%02" SCNd8 "/%04" SCNd16, &dato->Nascita.Giorno, &dato->Nascita.Mese, &dato->Nascita.Anno);
    elementiLetti += fscanf(stream, "%s %s", dato->Via, dato->Città);
    elementiLetti += fscanf(stream, "%05" SCNd32, &dato->CAP);
    if (stream != stdin) {
        fscanf(stream, "\n"); // Leggo a vuoto lo scanf
    }
    return elementiLetti == 9;
}

listaAnagrafica *creaLista(Item *i) { // Crea, alloca e restituisce un puntatore a listaAnagrafica
    listaAnagrafica *l = (listaAnagrafica *)malloc(sizeof(listaAnagrafica));
    l->Contenuto       = i;
    return l;
}

listaAnagrafica *getNextItem(listaAnagrafica *item) { // Restituisce l'elemento successivo nella lista
    return item->Next == NULL ? NULL : item->Next;
}

void addNext(listaAnagrafica *item, listaAnagrafica *next) { // Aggiunge un elemento next subito dopo un elemento item in una lista
    if (item->Next == NULL) {                                // Se si tratta dell'ultimo elemento
        item->Next = next;
        return;
    }

    listaAnagrafica *temp = item->Next;
    next->Next            = temp;
    item->Next            = next;
    return;
}

void putInBetween(listaAnagrafica *previous, listaAnagrafica *item) { // Sostituisce il next di previous con item e lo inserisce come next di item
    item->Next     = previous->Next;
    previous->Next = item;
}

void addInOrder(listaAnagrafica *head, listaAnagrafica *item) { // Inserisce un elemento in una lista in ordine di data
    listaAnagrafica *posizione = getNextItem(head);

    // Condizione di terminazione
    if (posizione == NULL) { // Se sono a fine lista
        return addNext(head, item);
    }

    // Se la data nella lista è > inserisco tra la head e il successivo, altrimenti proseguo ricorsivamente
    return confrontaData(posizione, item) ? putInBetween(head, item) : addInOrder(posizione, item);
}

Item *getResizedItem(Item *temp) { // Alloca memoria per realizzare una copia ridimensionata dell'item
    Item *dato = creaItem(strlen(temp->Nome), strlen(temp->Cognome), strlen(temp->Via), strlen(temp->Città));
    return dato;
}

void addAnagraficaFile(listaAnagrafica *Head, FILE *stream) {              // Aggiorna una lista di anagrafica leggendo gli elementi da file
    Item *temp = creaItem(MAX_STRING, MAX_STRING, MAX_STRING, MAX_STRING); // Item temporaneo per la lettura
    while (leggiRiga(stream, temp)) {                                      // Sinché la lettura va a buon fine
        Item *dato = getResizedItem(temp);
        copiaItem(temp, dato);             // Copio i dati
        addInOrder(Head, creaLista(dato)); // Aggiungo l'elemento alla coda
    }
    freeItem(temp); // Libero la memoria
}

listaAnagrafica *parseAnagrafica(char *filename) { // Effettua il parse da file su una nuova lista anagrafica
    FILE *stream = fopen(filename, "r");
    checkFilestream(stream);

    listaAnagrafica *Head = creaLista(NULL); // Creo la head
    addAnagraficaFile(Head, stream);

    fclose(stream);
    return Head;
}

void printItem(Item *i, FILE *stream) { // Stampa un Item
    fprintf(stream, "A%04" SCNd16, i->Codice);
    fprintf(stream, " %s %s ", i->Nome, i->Cognome);
    fprintf(stream, "%02" SCNd8 "/%02" SCNd8 "/%04" SCNd16, i->Nascita.Giorno, i->Nascita.Mese, i->Nascita.Anno);
    fprintf(stream, " %s %s ", i->Via, i->Città);
    fprintf(stream, "%05" SCNd32, i->CAP);
    fprintf(stream, "\n");
}

void printAnagraficaFile(listaAnagrafica *l, FILE *stream) { // Stampa un array di anagrafiche su file
    puts("Le anagrafiche presenti sono:");
    listaAnagrafica temp = *l;
    while (temp.Next != NULL) {                  // Sinché esiste un elemento successivo
        printItem(temp.Next->Contenuto, stream); // Stampo l'elemento
        temp = *temp.Next;                       // Passo all'elemento successivo in lista
    }
    printf("\n");
}

void printAnagrafica(listaAnagrafica *l) { // Stampa un array di anagrafiche a video
    printAnagraficaFile(l, stdout);
}

Item *ricercaCodiceR(listaAnagrafica *head, uint16_t *codice) { // Ricerca ricorsiva
    listaAnagrafica *pointer = getNextItem(head);
    if (pointer == NULL) { // Condizione di terminazione
        return NULL;
    }

    if (head->Contenuto->Codice == *codice) { // Se ho trovato la corrispondenza
        return head->Contenuto;
    }

    return ricercaCodiceR(pointer, codice); // Ricerco sull'elemento successivo
}

Item *ricercaCodice(listaAnagrafica *head, uint16_t *codice) { // Ricerca un elemento per codice nella lista, se lo trova ne restitusice il puntatore, altrimenti restituisce null
    listaAnagrafica *pointer = getNextItem(head);              // Salto la head
    return ricercaCodiceR(pointer, codice);                    // Ricerco sull'elemento successivo
}

listaAnagrafica *estraiNext(listaAnagrafica *previous) { // Estrae l'elemento successivo in lista
    listaAnagrafica *elemento = previous->Next;
    previous->Next            = elemento->Next;
    return elemento;
}

void promptMenu(listaAnagrafica **head) {
    puts("0 - Inserisci un elemento da tastiera");
    puts("1 - Inserisci elementi da file");
    puts("2 - Ricerca un elemento per codice");
    puts("3 - Estrai un elemento dalla lista");
    puts("4 - Estrai un range di elementi dalla lista");
    puts("5 - Stampa la lista su file");
    puts("6 - Stampa la lista a video");
    puts("Premi CTRL + C per uscire");
    printf("==> ");

    sceltaMenu scelta;
    scanf("%d", &scelta);
    printf("\n");
    switch (scelta) {
        case inserimentoTastiera: {
            puts("Inserisci l'elemento");
            printf("==> ");
            Item *temp = creaItem(MAX_STRING, MAX_STRING, MAX_STRING, MAX_STRING); // Item d'appoggio
            scanf("\n");
            leggiRiga(stdin, temp);
            Item *newItem = getResizedItem(temp); // Ridimensiono la lettura
            copiaItem(temp, newItem);             // Copio il contenuto
            freeItem(temp);
            addInOrder(*head, creaLista(newItem)); // Aggiungo alla lista
            break;
        }

        case inserimentoFile: {
            char filename[MAX_STRING];
            printf("Inserisci il nome del file (massimo %" SCNd8 " caratteri)\n", MAX_STRING);
            printf("==> ");
            scanf("%s", filename);
            FILE *stream = fopen(filename, "r");
            checkFilestream(stream);
            addAnagraficaFile(*head, stream);
            fclose(stream);
            break;
        }

        case ricerca: {
            printf("Inserisci il codice da ricercare\n");
            printf("==>");
            uint16_t codice;
            scanf("\nA%" SCNd16, &codice);
            Item *risultato = ricercaCodice(*head, &codice);
            if (risultato != NULL) { // Se ho trovato la codice
                printItem(risultato, stdout);
            } else {
                puts("Codice non trovato");
            }
            break;
        }

        case estrazione: {
            /* code */
            break;
        }

        case estrazioneRange: {
            /* code */
            break;
        }

        case printFile: {
            char filename[MAX_STRING];
            printf("Inserisci il nome del file (massimo %" SCNd8 " caratteri)\n", MAX_STRING);
            printf("==> ");
            scanf("%s", filename);
            FILE *stream = fopen(filename, "w");
            checkFilestream(stream);
            printAnagraficaFile(*head, stream);
            fclose(stream);
            break;
        }

        case printVideo: {
            printAnagrafica(*head);
            break;
        }

        default: {
            puts("Scelta non valida");
            break;
        }
    }
    printf("\n");
}

int main() {
    listaAnagrafica *Head = creaLista(NULL);
    while (true) {
        promptMenu(&Head);
    }

    return 0;
}
#include "inventario.h"
#include "personaggio.h"
#include "smartfunctions.h"

const uint8_t MAX_TRASPORTABILI = 8;

// Controlla se un personaggio ha raggiunto il limite di oggetti equipaggiabili
bool checkLimiteEquipaggiamento(personaggio *p, inventario *i) {
    return p->Equipaggiamento->NumeroOggetti >= i->OggettiTrasportabili;
}

// Mostra il menu interattivo
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
                FILE *pg = fopen("data/pg.txt", "r");
                // Verifico i filestream
                if (!checkFilestream(pg)) {
                    return 1;
                }
                parsePersonaggi(TABLE, pg);
                fclose(pg);
                break;
            }

            case caricaInventario: {
                FILE *inv = fopen("data/inventario.txt", "r");
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
                scanf("%" SCNd16, &ID);                                              // Leggo l'ID
                personaggioLink *precedente = ricercaIDprecedente(TABLE->HEAD, &ID); // Trovo l'elemento precedente
                if (precedente != NULL) {                                            // Se ho trovato l'ID
                    if (precedente->Next == TABLE->TAIL) {                           // Se è l'ultimo elemento
                        TABLE->TAIL = precedente;                                    // Aggiorno la TAIL
                    }

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
                scanf("%" SCNd16, &ID);                                // Leggo l'ID
                personaggioLink *pgLink = ricercaID(TABLE->HEAD, &ID); // Trovo l'elemento
                if (pgLink == NULL) {                                  // Se non ho trovato l'ID
                    puts("ID non trovato");
                    premiPerContinuare();
                    break;
                }
                personaggio *pg = pgLink->Personaggio;
                puts("Questi sono gli oggetti presenti nell'equipaggiamento:");
                printEquipaggiamento(pg->Equipaggiamento, false); // Stampo l'equipaggiamento

                // Leggo l'azione dell'utente
                puts("Inserisci 1 per aggiungere un oggetto o 0 per rimuoverlo");
                printf("==> ");
                uint8_t scelta;
                scanf("%" SCNd8, &scelta);

                if (scelta == 0) {                                 // Se l'utente desidera rimuovere
                    if (pg->Equipaggiamento->NumeroOggetti == 0) { // Se l'equipaggiamento è vuoto
                        puts("Non è possibile rimuovere oggetti a questo personaggio");
                        premiPerContinuare();
                        break;
                    }

                    printEquipaggiamento(pg->Equipaggiamento, true); // Stampo l'equipaggiamento con gli indici
                    puts("Inserisci il numero dell'oggetto");
                    printf("==> ");
                    scanf("%" SCNd8, &scelta);
                    if (scelta >= pg->Equipaggiamento->NumeroOggetti) { // Controllo la validità della scelta
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
                scanf("%" SCNd16, &ID);                            // Leggo l'ID
                personaggioLink *pg = ricercaID(TABLE->HEAD, &ID); // Trovo il pg
                if (pg != NULL) {                                  // Se ho trovato l'ID
                    int16_t s[N_STATISTICHE];
                    calcolaStatistiche(pg->Personaggio, s);
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
                scanf("%" SCNd16, &ID);                            // Leggo l'ID
                personaggioLink *pg = ricercaID(TABLE->HEAD, &ID); // Trovo il pg
                if (pg != NULL) {                                  // Se ho trovato l'ID
                    equipaggiamento *e = pg->Personaggio->Equipaggiamento;
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

#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_STRING = 30;

uint16_t oraConverter(uint8_t ora, uint8_t minuti) { // Converte in intero un orario composto da data e minuti
    uint16_t result = ora * 60;
    return result + minuti;
}

uint16_t dataConverter(uint16_t anno, uint8_t mese, uint8_t giorno) { // Converte in intero una data composta da data e minuti, questo formato permette di esprimere date sino al 31/06/2127
    anno -= 1970;                                                     // Sottraggo all'anno il valore di offset secondo gli standard UNIX
    uint16_t result = (anno * 13) + mese;                             // Esprimo l'anno in mesi
    result          = (result * 32) + giorno;                         // Esprimo i mesi in giorni
    return result;
}

void toOraMinuto(uint16_t Orario, uint8_t *ora, uint8_t *minuti) { // Converte in Ora e Minuto un orario intero
    *ora    = Orario / 60;
    *minuti = Orario - (*ora * 60);
}
void toAnnoMeseGiorno(uint16_t Data, uint16_t *anno, uint8_t *mese, uint8_t *giorno) { // Converte in Ora e Minuto un orario intero
    *anno = Data / (32 * 13);
    Data -= (*anno * 32 * 13); // Ricalcolo la data sottraendo gli anni
    *mese   = Data / 32;
    *giorno = Data - (*mese * 32);   // Calcolo i giorni sottraendo i mesi
    *anno += 1970;                   // Sommo il valore di offset
    *mese += *mese == 0 ? 1 : 0;     // Correggo eventuali errori nel calcolo del mese
    *giorno += *giorno == 0 ? 1 : 0; // Correggo eventuali errori nel calcolo del giorno
}

typedef struct Corsa { // Struttura per memorizzare le corse
    char CodiceTratta[MAX_STRING];
    char Partenza[MAX_STRING];
    char Destinazione[MAX_STRING];
    uint16_t Data;
    uint16_t OraPartenza;
    uint16_t OraArrivo;
    uint16_t Ritardo;
} corsa;

typedef enum { data,
               tratta,
               partenza,
               arrivo,
               nonOrdinato,
               ora } ordinamento;                      // Enum per indicare il tipo di ordinamento
ordinamento ORDINE_ATTUALE        = nonOrdinato;       // Variabile che segna l'attuale ordinamento
const size_t ordinamentiPossibili = (nonOrdinato + 1); // Il numero di ordinamenti è dato dall'indice dell'ultimo ordinamento nell'enum + 1
corsa *ORDINAMENTI[ordinamentiPossibili];              // Creo l'array che punta i vari ordinamenti

int numeroCorse(FILE *stream) { // Restituisce il numero di corse dentro il file
    int righe;
    fscanf(stream, "%d", &righe);
    return righe;
}

void parseCorse(FILE *stream) { // Funzione che effettua il parse delle corse
    char CodiceTratta[MAX_STRING];
    char Partenza[MAX_STRING];
    char Destinazione[MAX_STRING];
    uint8_t Giorno, Mese;
    uint16_t Anno;
    uint8_t OraPartenza, MinutoPartenza;
    uint8_t OraArrivo, MinutoArrivo;
    uint16_t Ritardo;
    corsa *corse = ORDINAMENTI[nonOrdinato];

    int scanCheck = fscanf(stream, "%s %s %s %2" SCNd8 "/%2" SCNd8 "/%4" SCNd16 " %2" SCNd8 ":%2" SCNd8 " %2" SCNu8 ":%2" SCNu8 " %" SCNd16, CodiceTratta, Partenza, Destinazione, &Giorno, &Mese, &Anno, &OraPartenza, &MinutoPartenza, &OraArrivo, &MinutoArrivo, &Ritardo);
    int i         = 0;
    while (scanCheck == 11) {
        strcpy(corse[i].CodiceTratta, CodiceTratta);
        strcpy(corse[i].Partenza, Partenza);
        strcpy(corse[i].Destinazione, Destinazione);
        corse[i].Data        = dataConverter(Anno, Mese, Giorno);
        corse[i].OraPartenza = oraConverter(OraPartenza, MinutoPartenza);
        corse[i].OraArrivo   = oraConverter(OraArrivo, MinutoArrivo);
        corse[i].Ritardo     = Ritardo;
        scanCheck            = fscanf(stream, "%s %s %s %2" SCNd8 "/%2" SCNd8 "/%4" SCNd16 " %2" SCNd8 ":%2" SCNd8 " %2" SCNu8 ":%2" SCNu8 " %" SCNd16, CodiceTratta, Partenza, Destinazione, &Giorno, &Mese, &Anno, &OraPartenza, &MinutoPartenza, &OraArrivo, &MinutoArrivo, &Ritardo);
        i++;
    }
    fclose(stream);
}

int checkFilestream(FILE *stream) { // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return 0;
}

void printLog(int numeroCorse) {                // Stampa il contenuto dell'array di corse
    corsa *corse = ORDINAMENTI[ORDINE_ATTUALE]; // Salvo il puntatore all'ordine attuale
    FILE *stream;
    char filename[MAX_STRING];
    printf("Dove vuoi che venga stampato il log? Inserisci il nome del file (max %d caratteri) o scrivi 0 per stampare a video: ", MAX_STRING);
    scanf("%s", filename);

    if (filename[0] != '0') {
        stream = fopen(filename, "w");
        fprintf(stream, "%d\n", numeroCorse);
    } else {
        stream = stdout;
        fprintf(stream, "\n");
    }

    for (size_t i = 0; i < numeroCorse; i++) { // Stampo tutte le corse
        uint8_t Giorno, Mese;
        uint16_t Anno;
        uint8_t OraPartenza, MinutoPartenza;
        uint8_t OraArrivo, MinutoArrivo;
        toOraMinuto(corse[i].OraPartenza, &OraPartenza, &MinutoPartenza); // Trasformo l'orario
        toOraMinuto(corse[i].OraArrivo, &OraArrivo, &MinutoArrivo);       // Trasformo l'orario
        toAnnoMeseGiorno(corse[i].Data, &Anno, &Mese, &Giorno);           // Trasformo la data
        fprintf(stream, "%s %s %s %02" SCNd8 "/%02" SCNd8 "/%04" SCNd16 " %02" SCNd8 ":%02" SCNd8 " %02" SCNu8 ":%02" SCNu8 " %" SCNd16 "\n", corse[i].CodiceTratta, corse[i].Partenza, corse[i].Destinazione, Giorno, Mese, Anno, OraPartenza, MinutoPartenza, OraArrivo, MinutoArrivo, corse[i].Ritardo);
    }
    printf("\n");
    if (stream != stdout) { // Se sto lavorando su file chiudo lo stream alla fine
        fclose(stream);
    }
}

void printTratta(corsa tratta, FILE *stream) { // Stampa una sola tratta su un FILE
    uint8_t Giorno, Mese;
    uint16_t Anno;
    uint8_t OraPartenza, MinutoPartenza;
    uint8_t OraArrivo, MinutoArrivo;
    toOraMinuto(tratta.OraPartenza, &OraPartenza, &MinutoPartenza); // Trasformo l'orario
    toOraMinuto(tratta.OraArrivo, &OraArrivo, &MinutoArrivo);       // Trasformo l'orario
    toAnnoMeseGiorno(tratta.Data, &Anno, &Mese, &Giorno);           // Trasformo la data
    fprintf(stream, "%s %s %s %02" SCNd8 "/%02" SCNd8 "/%04" SCNd16 " %02" SCNd8 ":%02" SCNd8 " %02" SCNu8 ":%02" SCNu8 " %" SCNd16 "\n", tratta.CodiceTratta, tratta.Partenza, tratta.Destinazione, Giorno, Mese, Anno, OraPartenza, MinutoPartenza, OraArrivo, MinutoArrivo, tratta.Ritardo);
}

bool ordineAlfabetico(char *string1, char *string2) { // Restituisce true se la prima stringa viene prima in ordine alfabetico è è uguale
    int lenght1 = strlen(string1);
    int lenght2 = strlen(string2);
    int min     = lenght1 <= lenght2 ? lenght1 : lenght2; // Controllo per la stringa più piccola

    for (size_t i = 0; i < min; i++) {                   // Sinché i caratteri sono uguali esploro quello successivo
        if (tolower(string1[i]) < tolower(string2[i])) { // Se il carattere viene prima nella tabella ASCII restituisco true
            return true;
        } else if (tolower(string1[i]) > tolower(string2[i])) { // Se viene dopo restituisco false
            return false;
        }
    }

    return (lenght1 <= lenght2); // Se la prima stringa è più corta o uguale significa che viene prima o è uguale alla seconda
}

bool confrontaCampi(corsa *elemento1, corsa *elemento2, ordinamento campo) { // Ricevute due corse in ingresso ed un campo di confronto, restituisce se la prima è maggiore o uguale alla seconda
    switch (campo) {                                                         // Per ogni campo ho un processo differente
        case data: {
            if (elemento1->Data > elemento2->Data) { // Se è maggiore
                return true;
            } else if (elemento1->Data < elemento2->Data) { // Se è minore
                return false;
            }

            return confrontaCampi(elemento1, elemento2, ora); // Se la data è ugualecontrollo per ora
            break;
        }

        case ora: {
            // Controllo per ora
            if (elemento1->OraPartenza >= elemento2->OraPartenza) {
                return true;
            }

            return false; // Se non è ne maggiore ne uguale restituisco false
            break;
        }
        case tratta: {
            return ordineAlfabetico(elemento1->CodiceTratta, elemento2->CodiceTratta);
            break;
        }

        case partenza: {                                                       // Controllo l'ordine alfabetico
            return ordineAlfabetico(elemento2->Partenza, elemento1->Partenza); // Se l'elemento 2 viene prima allora l'elemento 1 è maggiore in ordine alfabetico
            break;
        }

        case arrivo: {                                                                 // Controllo l'ordine alfabetico
            return ordineAlfabetico(elemento2->Destinazione, elemento1->Destinazione); // Se l'elemento 2 viene prima allora l'elemento 1 è maggiore in ordine alfabetico
            break;
        }
    }
}

void merge(corsa *corse, corsa *corseAppoggio, int inzio, int centro, int fine, ordinamento ordine) { // Unisce i due sottovettori ordinandoli
    int i, j;
    i = inzio;      // Contatore per l'esporazione dell'array sinistro
    j = centro + 1; // Contatore per l'esporazione dell'array destro

    int k;
    for (k = inzio; i <= centro && j <= fine; k++) {      // Confronto gli array sinistro e destro
        if (confrontaCampi(&corse[j], &corse[i], ordine)) // Se l'elemento nel sinistro è minore o uguale (oppure quello destro maggiore o uguale) all'altro copio di conseguenza
            corseAppoggio[k] = corse[i++];
        else
            corseAppoggio[k] = corse[j++];
    }

    while (i <= centro)
        corseAppoggio[k++] = corse[i++]; // Copio il resto degli elementi a sinistra nell'array d'appoggio
    while (j <= fine)
        corseAppoggio[k++] = corse[j++]; // Copio il resto degli elementi a destra nell'array d'appoggio
    for (k = inzio; k <= fine; k++)
        corse[k] = corseAppoggio[k]; // Ricopio tutto nell'array originale
}

void ordinaRicorsivo(corsa *corse, corsa *corseAppoggio, int inizio, int fine, ordinamento ordine) { // Componente ricorsiva del Merge Sort
    int centro = (inizio + fine) / 2;                                                                // Calcolo l'indice di metà vettore

    if (inizio >= fine) { // Se ho un vettore unitario mi interrompo
        return;
    }

    ordinaRicorsivo(corse, corseAppoggio, inizio, centro, ordine);   // Ordina a sinistra
    ordinaRicorsivo(corse, corseAppoggio, centro + 1, fine, ordine); // Ordina a destra
    merge(corse, corseAppoggio, inizio, centro, fine, ordine);       // Unisco i due array
}

void ordina(int numeroCorse, ordinamento ordine) { // Funzione che ordina il log in base a come richiesto (è un Merge Sort)
    if (ORDINAMENTI[ordine][0].Partenza != NULL) { // Se l'ordinamento è già stato effettuato aggiorno il puntatore, effettuo il controllo su un campo della tratta
        ORDINE_ATTUALE = ordine;
        return;
    }

    memcpy(ORDINAMENTI[ordine], ORDINAMENTI[ORDINE_ATTUALE], numeroCorse * sizeof(corsa)); // Copio l'ordinamento attuale nel nuovo
    corsa *corseAppoggio = (corsa *)malloc(numeroCorse * sizeof(corsa));                   // Creo l'array d'appoggio
    int inizio = 0, fine = numeroCorse - 1;
    ordinaRicorsivo(ORDINAMENTI[ordine], corseAppoggio, inizio, fine, ordine);
    ORDINE_ATTUALE = ordine; // Aggiorno l'ordine attuale
}

void promptOrdinamento(int numeroCorse) {
    puts("Inserisci l'ordinamento da applicare al vettore:");
    puts("0 - Ordina per Data/Ora");
    puts("1 - Ordina per Tratta");
    puts("2 - Ordina per stazione di partenza");
    puts("3 - Ordina per stazione di arrivo");
    puts("4 - Torna all'ordinamento originale");
    ordinamento ordine;
    scanf("%d", &ordine);
    ordina(numeroCorse, ordine);
    printf("\n");
}

void stampaRicerca(corsa *corse, char partenza[MAX_STRING], FILE *stream, int passo) { // Stampa le corse sinché son corrette avanzando ogni volta di un determinato passo
    int i = 0;
    while (strcmp(corse[i].Partenza, partenza) == 0) { // Sinché il valore è corretto
        printTratta(corse[i], stream);                 // Stampo la tratta
        i += passo;
    }
}

void ricercaDicotomica(int numeroCorse, corsa *corse, char strPartenza[MAX_STRING], FILE *stream) { // Ricerca le tratte che portano ad una destinazione a partire da un array ordinato
    size_t centro = numeroCorse / 2;

    if (strcmp(corse[centro].Partenza, strPartenza) == 0) {         // Condizione di interruzione
        stampaRicerca(&corse[centro - 1], strPartenza, stream, -1); // Stampo tutti gli elementi precedenti
        stampaRicerca(&corse[centro], strPartenza, stream, 1);      // Stampo tutti gli elementi successivi
    } else if (numeroCorse == 1) {                                  // Se abbiamo una sola corsa e questa non è quella corretta mi interrompo
        return;
    } else {                                                                 // Altrimenti continuo sulle corse rimanenti ricorsivamente
        if (confrontaCampi(corse[centro].Partenza, strPartenza, partenza)) { // Se la corsa è maggiore continuo a sinistra
            ricercaDicotomica(centro, &corse[0], strPartenza, stream);       // Ricerca nella prima metà
        } else {                                                             // Altrimenti continuo a destra
            numeroCorse -= centro;
            ricercaDicotomica(numeroCorse, &corse[centro], strPartenza, stream); // Ricerca nella seconda metà
        }
    }
}

void ricercaLineare(int numeroCorse, char strPartenza[MAX_STRING], FILE *stream) { // Ricerca le tratte che portano ad una destinazione a partire da un array non ordinato
    corsa *corse = ORDINAMENTI[ORDINE_ATTUALE];                                    // Salvo il puntatore all'ordinamento attuale
    for (size_t i = 0; i < numeroCorse; i++) {
        if (strcmp(corse[i].Partenza, strPartenza) == 0) { // Se la partenza combacia la stampo
            printTratta(corse[i], stream);
        }
    }
}

void cercaTratta(int numeroCorse) { // Ricerca e stampa le tratte che portano ad una determinata destinazione
    char strPartenza[MAX_STRING];
    puts("Scrivi la stazione di partenza");
    gets(strPartenza); // Prima lettura a vuoto
    gets(strPartenza); // Leggo la tratta di destinazione

    FILE *stream;
    char filename[MAX_STRING];
    printf("Dove vuoi che venga stampato il log? Inserisci il nome del file (max %d caratteri) o scrivi 0 per stampare a video: ", MAX_STRING);
    scanf("%s", filename);

    if (filename[0] != '0') {
        stream = fopen(filename, "w");
        fprintf(stream, "%d\n", numeroCorse);
    } else {
        stream = stdout;
        fprintf(stream, "\n");
    }

    if (ORDINE_ATTUALE == partenza) {
        ricercaDicotomica(numeroCorse, ORDINAMENTI[ORDINE_ATTUALE], strPartenza, stream); // Se il vettore è ordinato
    } else {
        ricercaLineare(numeroCorse, strPartenza, stream); // Altrimenti eseguo la ricerca lineare
    }

    if (stream != stdout) { // Se sto scrivendo un un file alla fine chiudo lo stream
        fclose(stream);
    }
}

void promptMenu(int numeroCorse) {
    while (true) {
        puts("Scegli una delle seguenti azioni o premi CTRL+C per uscire:");
        puts("0 - Stampa la lista delle corse");
        puts("1 - Riordina la lista delle corse");
        puts("2 - Ricerca all'interno della lista");

        int lettura;
        scanf("%d", &lettura);
        switch (lettura) {

            case 0: {
                printf("\n");
                printLog(numeroCorse);
                break;
            }

            case 1: {
                printf("\n");
                promptOrdinamento(numeroCorse);
                break;
            }

            case 2: {
                printf("\n");
                cercaTratta(numeroCorse);
                break;
            }

            default: {
                break;
            }
        }
    }
}

int main() {
    memset(ORDINAMENTI, NULL, ordinamentiPossibili); // Rendo null tutti i valori del puntatore
    FILE *corseStream = fopen("corse.txt", "r");
    checkFilestream(corseStream);
    int nCorse = numeroCorse(corseStream);

    for (size_t i = 0; i < ordinamentiPossibili; i++) {
        ORDINAMENTI[i] = (corsa *)malloc(nCorse * sizeof(corsa));
    }

    parseCorse(corseStream);
    promptMenu(nCorse);
    return 0;
}
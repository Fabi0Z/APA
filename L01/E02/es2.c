#include <stdio.h>
#include <string.h>
#include <error.h>

const int MAX_ROW_LENGHT = 200;

struct Chiave {
    char Originale[MAX_ROW_LENGHT];
    char Codificato[MAX_ROW_LENGHT];
};


int checkFilestream(FILE *stream) {  // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return 0;
}

int readNumeroChiavi(FILE *stream) { // Restituisce il numero di chiavi presenti
    int chiavi;
    fscanf(stream, "%d", &chiavi);
    return chiavi;
}

void readChiavi(FILE *stream, int chiavi, struct Chiave dizionario[chiavi]) {
    for (size_t i = 0; i < chiavi; i++) {
        memset(dizionario[i].Originale, 0, MAX_ROW_LENGHT*sizeof(char));
        memset(dizionario[i].Codificato, 0, MAX_ROW_LENGHT*sizeof(char));
        fscanf(stream, "%s %s", dizionario[i].Codificato, dizionario[i].Originale);
    }
}

int replaceDocument(int chiavi, FILE *input, FILE *output, struct Chiave dizionario[chiavi]) {
    int sosituzioni = 0;
    char rigaOriginale[MAX_ROW_LENGHT], riga[MAX_ROW_LENGHT];
    memset(rigaOriginale, 0, MAX_ROW_LENGHT*sizeof(char));
    memset(riga, 0, MAX_ROW_LENGHT*sizeof(char));

    int j = 0;
    while (fgets(rigaOriginale, MAX_ROW_LENGHT, input) != NULL) {
        for (size_t i = 0; i < chiavi; i++) { // Esploro per ogni chiave
            int lunghezzaChiave = strlen(dizionario[i].Originale);
            char temp[lunghezzaChiave]; // Dichiaro una sottostringa temporanea della lunghezza adatta

            for (size_t k = 0; k < strlen(rigaOriginale); k++) { // Esploro per ogni carattere della riga
                
                for (size_t l = 0; l < lunghezzaChiave; l++) { // Creo sottostringa temp
                    
                    temp[l] = rigaOriginale[k+l];
                }
                
                if (strcmp(temp, dizionario[i].Originale) == 0) { // Controllo se la sottostringa è uguale alla chiave decodificata
                    strcat(riga, dizionario[i].Codificato); // Concateno il risultato nella riga
                    k += lunghezzaChiave - 1; // Incremento l'indice di k della lunghezza della parola
                    sosituzioni++;
                    
                } else {
                    strncat(riga, temp, 1); // Copio il primo carattere temporaneo nella riga
                }
            }
            memcpy(rigaOriginale, riga, MAX_ROW_LENGHT);
            memset(riga, 0, MAX_ROW_LENGHT*sizeof(char));
        }
        fprintf(output, rigaOriginale);
        j++;
    }
    return sosituzioni;
}


int main() {
    // Apro e controllo i filestrem
    puts("Apro il file sorgente.txt");
    FILE *streamSorgente = fopen("sorgente.txt", "r");
    checkFilestream(streamSorgente);
    puts("Apro il file dizionario.txt");
    FILE *streamDizionario = fopen("dizionario.txt", "r");
    checkFilestream(streamDizionario);
    puts("Apro il file ricodificato.txt");
    FILE *streamRicodificato = fopen("ricodificato.txt", "w");
    checkFilestream(streamRicodificato);

    // Leggo le chiavi
    int numeroChiavi = readNumeroChiavi(streamDizionario);
    struct Chiave dizionario[numeroChiavi];
    readChiavi(streamDizionario, numeroChiavi, dizionario);

    // Sostituisco
    puts("\nSostituisco le chiavi nel documento...");
    int chiaviSostituite = replaceDocument(numeroChiavi, streamSorgente, streamRicodificato, dizionario);
    printf("Sono state sostituite %d chiavi\n", chiaviSostituite);

    // Chiudo i filestream
    fclose(streamSorgente);
    fclose(streamDizionario);
    fclose(streamRicodificato);
    return 0;
}
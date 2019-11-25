#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int MAX_SEQUENZE_Length = 5;

typedef struct DynamicString {
    char *Contents;
    size_t Length, Used;
} dynString;

typedef struct DynamicArray {
    int *Array;
    size_t Length, Used;
} dynArray;

typedef struct Sequenza{
    dynString Testo;
    dynArray Occorrenze;
    dynString *Parole;
} sequenza;

void initializeString(dynString *string, int size) { // Inizializa una dynString
    string->Contents = (char *)malloc(size*sizeof(char));
    string->Length = size;
    string->Used = 0;
    memset(string->Contents, 0, size*sizeof(char));
}

void initializeArray(dynArray *array, int size) { // Inizializa una dynString
    array->Array = (int *)malloc(size*sizeof(int));
    array->Length = size;
    array->Used = 0;
    memset(array->Array, 0, size*sizeof(int));
}

void insertValueDynString(dynString *string, char character) { // Inserisce un valore in una dynString
    if (string->Used == string->Length) {
        string->Contents = (char *)realloc(string->Contents, string->Length*sizeof(char)); // Raddoppio la dimensione della stringa
        string->Length++;
    }

    string->Contents[string->Used++] = character;
}

void insertValueDynArray(dynArray *array, int value) { // Inserisce un valore in una dynArray
    if (array->Used == array->Length) {
        array->Array = (int *)realloc(array->Array, array->Length*sizeof(int)); // Raddoppio la dimensione dell'Array
        array->Length++;
    }

    array->Array[array->Used++] = value;
}


int checkFilestream(FILE *stream) {  // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return 0;
}

int numeroSequenze(FILE *stream) {
    int i;
    fscanf(stream, "%d", &i);
    return i;
}

void readSequenze(FILE *input, int nSequenze, sequenza sequenze[nSequenze]) {
    char temp;
    int scanfcheck = fscanf(input, "%c", &temp);
    while (isalnum(temp) == 0) { // Salto tutti i valori non alfanumerici all'inizio
        fscanf(input, "%c", &temp);
    }

    for (size_t i = 0; i < nSequenze; i++) {
        initializeString(&sequenze[i].Testo, 1);
        do { // Leggo i singoli caratteri
            if (isalnum(temp)) {
                insertValueDynString(&sequenze[i].Testo, tolower(temp));   
            } 
            scanfcheck = fscanf(input, "%c", &temp);
        } while (temp != '\n' && scanfcheck != EOF);
        initializeArray(&sequenze[i].Occorrenze, 10); // Inizializzo l'Array con una lunghezza di sicurezza
    }
}

void getSubstring(int substringLength, int start, char *string, char subString[substringLength]) { // Restituisce una sottostringa di dimensione data a partire da un certo indice
    for (size_t i = 0; i < substringLength; i++) {
        subString[i] = tolower(string[start + i]);
    }
}

void contaOccorrenze(FILE *input, int nSequenze, sequenza sequenze[nSequenze]) {
    dynString temp;
    initializeString(&temp, 20);  // Inizializzo la stringa con una lunghezzadi sicurezza
    char character;
    int scanfCheck = fscanf(input, "%c", &character);
    int countCharacter = 0;

    while (scanfCheck != EOF) { // Leggo il file carattere per carattere e controllo che il carattere non sia EOF
        if (isalnum(character)) { // Controllo se la parola è finita o meno
            insertValueDynString(&temp, character);
        } else {
            for (size_t i = 0; i < temp.Used; i++) { // Per ogni carattere nella stringa
                for (size_t j = 0; j < nSequenze; j++) { // Per ogni Sequenza di caratteri
                    if (temp.Used - i >= sequenze[j].Testo.Used) { // Controllo solo se la lunghezza della sottotringa è pari o superiore a quella della sequenza
                        char substring[sequenze[j].Testo.Used];
                        getSubstring(sequenze[j].Testo.Used, i, temp.Contents, substring);
                        if (strncmp(substring, sequenze[j].Testo.Contents, sequenze[j].Testo.Used) == 0) { // Se la sottotringa è uguale all'occorrenza aumento il numero di occorrenze
                            insertValueDynArray(&sequenze[j].Occorrenze, countCharacter+j);
                        }
                    }
                }
            }
            memset(temp.Contents, 0, temp.Length*sizeof(char)); // Pulisco la riga temporanea
            temp.Used = 0;
        }
        scanfCheck = fscanf(input, "%c", &character); // Leggo il carattere successivo
        countCharacter++;
    }
}

void printOccorrenze(int nSequenze, sequenza sequenze[nSequenze]) {
    for (size_t i = 0; i < nSequenze; i++) {
        printf("La sequenza \"%s\" appare %zu volte ai caratteri in posizione:", sequenze[i].Testo.Contents, sequenze[i].Occorrenze.Used);
        for (size_t j = 0; j < sequenze[i].Occorrenze.Used; j++) {
            printf(" %d", sequenze[i].Occorrenze.Array[j]);
        }
        printf("\n");
    }
    
}

int main() {
    puts("Apro il file sequenze.txt");
    FILE *streamSequenze = fopen("sequenze.txt", "r");
    checkFilestream(streamSequenze);
    puts("Apro il file testo.txt");
    FILE *streamTesto = fopen("testo.txt", "r");
    checkFilestream(streamTesto);

    puts("\nLeggo le sequenze...");
    int nSequenze = numeroSequenze(streamSequenze);
    sequenza sequenze[nSequenze];
    readSequenze(streamSequenze, nSequenze, sequenze);

    puts("\nConfronto le sequenze...");
    contaOccorrenze(streamTesto, nSequenze, sequenze);
    printOccorrenze(nSequenze, sequenze);
    return 0;
}
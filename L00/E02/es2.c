#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxWordlength = 20;

int readNumber(FILE *stream) { // Leggi quante parole sono presenti all'interno del file
    int number;
    fscanf(stream, "%d", &number);
    return number;
}

int checkFilestream(FILE *stream) {  // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return 0;
}

void readWords(FILE *stream, int words, char parole[words][maxWordlength]) { // Leggi N parole dal file
    for (size_t i = 0; i < words; i++) {
        char temp[20];
        fscanf(stream, "%s", &temp);
        strcpy(&parole[i], temp);
    }
    
}

void printWords(int words, char parole[words][maxWordlength]) {
    for (size_t i = 0; i < words; i++) {
        printf("%s\n", &parole[i]);
    }
}

int conta2Vocali (int length, char parola[length]) { // Restituisce 1 se ci sono almeno 2 vocali nella parola, altrimenti 0
    int count = 0;
    size_t i = 0;

    while(i < length) {
        char temp = toupper(parola[i]);
        switch (temp) {
        case 'A':
            count++;
            break;
        
        case 'E':
            count++;
            break;

        case 'I':
            count++;
            break;

        case 'O':
            count++;
            break;

        case 'U':
            count++;
            break;

        case 0: // In caso di spazio vuoto interrompe la conta in quanto la sottostringa è terminata
            count = 0;
            i = length;
            break;
        }
        i++;
    }
    
    if (count == 2) {
        return 1;
    }
    
    return 0;
}

void componiStringa(char original[maxWordlength], char *result, int start, int length) { // Compone una sottostringa di una parola
    for (size_t i = 0; i < length; i++) {
        result[i] = original[start + i];
    }
    
}

int conta(char stringa[maxWordlength], int lunghezzaSottostringa) { // Conta il numero di vocali presenti all'interno di sottostringhe di N dimensione di una parola
    int conto = 0;

    for (size_t i = 0; i < lunghezzaSottostringa; i++) {
        char temp[lunghezzaSottostringa];
        componiStringa(stringa, temp, i, lunghezzaSottostringa);
        conto += conta2Vocali(lunghezzaSottostringa, temp);
    }

    return conto;
}

int main(int argc, char const *argv[]) {

    // Leggo il nome del file
    printf("Scrivi il nome del file: ");
    char filename[maxWordlength];
    scanf("%s", &filename);  

    
    FILE *f = fopen(filename, "r");
    checkFilestream(f);
    int words = readNumber(f);
    printf("Ci sono %d parole:\n", words);

    char parole[words][maxWordlength];
    readWords(f, words, parole);
    printWords(words, parole);
    printf("\n");

    int dimensioneSottostringhe;
    printf("Scrivi la dimensione delle sottostringhe: ");
    scanf("%d", &dimensioneSottostringhe);

    int conto = 0;
    for (size_t i = 0; i < words; i++) {  // Esploro l'array di parole e per ognuna di esse controllo quante vocali sono presenti nelle sottostringhe
        conto += conta(parole[i], dimensioneSottostringhe);
    }

    printf("Ci sono %d sottostringhe di dimensione %d\n", conto, dimensioneSottostringhe);
    

    fclose(f);
    return 0;
}

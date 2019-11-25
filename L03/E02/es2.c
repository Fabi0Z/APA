#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

bool bigEndian;

bool checkBigEndian() { // Controlla se la macchina è Big o Little Endian
    int a = 16777216;
    /* La rappresentazione in esadecimale di a è 0x01000000, quindi in Little Endian risulterà
       salvato in 4 celle di memoria contenenti i valori 00 00 00 01
    */
    uint8_t *valuePointer = (uint8_t *)&a; // Punto alla prima cella di memoria contenente a tramite un puntatore a int da 1 byte
    uint8_t value = *(valuePointer + 3); // Mi sposto col puntatore alla quarta cella che dovrebbe contenere 01

    if (value == 1) { // Se il valore corrisponde a 1 allora NON è Big Endian
        return 0;
    } else {
        return 1; // Altrimenti lo è
    }
}

void putIn(char c, size_t size, char array[size]) { // Sposta tutti i valori di una stringa a destra di una posizione e inserisce il carattere come primo
    for (size_t i = size - 1; i > 0; i--) {
        array[i] = array[i - 1]; // Copia i valori dell'array nella posizione di fianco dall'ultimo al primo
    }
    array[0] = c; // Copia c nella prima cella dell'array
}

void scanNumbers(float *af, double *ad, long double *ald) {
    printf("Inserisci un valore float: ");
    scanf("%f", af);
    printf("\nInserisci un valore double: ");
    scanf("%lf", ad);
    printf("\nInserisci un valore float: ");
    scanf("%Lf", ald);
    printf("\n");
}

typedef struct PrecisioneSingola{
    bool Segno;
    char Esponente[9];
    char Mantissa[24];
    char Macchina[33];
} precisioneSingola;

typedef struct PrecisioneDoppia{
    bool Segno;
    char Esponente[12];
    char Mantissa[53];
    char Macchina[65];
} precisioneDoppia;

typedef struct PrecisioneQuadrupla{
    bool Segno;
    char Esponente[16];
    char Mantissa[113];
    char Macchina[129];
} precisioneQuadrupla;

int8_t restoLongDouble(long double numero, int8_t divisore, long double *risultato) { // Restituisce il resto di una divisione tra un numero in floating point sino a lond double e un divisore intero
    modfl(numero, &numero); // Conservo solo la parte intera del numero
    *risultato = numero / divisore; // Scrivo il risultato della divisione
    modfl(*risultato, risultato); // Conservo solo la parte intera del risultato
    return (int8_t)(numero - *risultato*divisore); // Restituisco il resto della divisione
}

size_t printBinario(long double base10, uint8_t bit, char binario[bit+1]) { // Scrive il valore in binario di un determinato numero
    char interi[bit+1], decimali[bit+1];
    memset(interi, 0, bit+1); // Scrivo 0 su ogni stringa
    memset(decimali, 0, bit+1);
    memset(binario, 0, bit+1);
    long double parteIntera, parteDecimale;
    parteDecimale = modfl(base10, &parteIntera); // Suddivido il numero in parte interea e parte decimale

    size_t cifreIntere = 0; // Contatore per le cifre intere
    if (parteIntera != (long double)0) { // Se la parte intera è diversa da 0 trovo il binario della parte intera
        do { // Calcolo i valori binari interi
            interi[cifreIntere++] = restoLongDouble(parteIntera, 2, &parteIntera) + 48;
        } while (parteIntera != (long double)0);
    }

    size_t cifreDecimali = 0; // Conto le cifre decimali
    if (parteDecimale != (long double)0) { // Se la parte decimale è diversa da 0 trovo il binario della parte decimale
        do { // Calcolo i valori binari decimali
            parteDecimale *= 2;
            decimali[cifreDecimali++] = (char)(((uint8_t)parteDecimale % 2) + 48);
            parteDecimale = modfl(parteDecimale, &parteIntera);
        } while (parteDecimale != (long double)0); // Calcolo sinché la parte intera è diversa da 0
    }
    
    for (size_t i = 0; i < cifreIntere; i++) { // Riscrivo i valori interi nella stringa binaria invertendoli
        binario[i] = interi[cifreIntere -1 - i];
    }
    strcat(binario, decimali); // Aggiungo la parte decimale
    return cifreIntere; // Restituisco la quantià di cifre intere
}

void parseSingola(float number, precisioneSingola *risultato) { // Legge un double e lo salva in una variabile di tipo precisioneSingola
    const int BIAS = 127;
    const int8_t BASE = 2;
    const int BIT = 32;
    const int ESPONENTE = 8;
    const int MANTISSA = 23;

    risultato->Segno = number < 0 ? true : false; // Scrivo il segno
    number = number < 0 ? -1*number : number; // Riscrivo il numero in modulo

    char binario[BIT + 1], esponenteTemp[ESPONENTE + 1];
    size_t cifreIntere = printBinario(number, BIT, binario); // Salvo il numero in binario
    size_t cifreDecimali = strlen(binario) - cifreIntere;
    memset(risultato->Mantissa, 48, MANTISSA + 1); // Scrivo 0 nei primi nella mantissa
    memset(risultato->Esponente, 48, ESPONENTE + 1); // Scrivo 0 nell'esponente
    memset(esponenteTemp, 48, ESPONENTE + 1); // Scrivo 0 nell'esponente
    memset(risultato->Mantissa, 48, MANTISSA); // Scrivo '0' nei primi 23 caratteri della mantissa
    memset(risultato->Esponente, 48, ESPONENTE); // Scrivo '0' nell'esponente
    memset(esponenteTemp, 48, ESPONENTE); // Scrivo '0' nell'esponente
    int Esponente = 0; // Dichiaro l'esponente

    if (cifreIntere > 0) { // Se ho almeno una cifra intera prima della virgola
        Esponente = strlen(binario) - cifreDecimali - 1;
        for (size_t i = 0; i < strlen(binario) - 1; i++) { // Scrivo le cifre nella mantissa
            risultato->Mantissa[i] = binario[i + 1];
        }
    } else if (cifreDecimali > 0) { // Se ho almeno una cifra decimale conto l'esponente negativo
        for (size_t i = 0; i < cifreDecimali; i++) {
            Esponente--;
            if (binario[i] == 49) { // Mi trovo al primo 1 che trovo
                break;
            }
        }

        for (size_t i = -1*Esponente; i < strlen(binario); i++) { // Copio i valori nella mantissa
            risultato->Mantissa[i + Esponente] = binario[i];
        }
    }
    
    size_t cifreEsponente = printBinario(Esponente + BIAS, ESPONENTE, esponenteTemp); // Scrivo l'esponente corretto in binario
    for (size_t i = 0; i < ESPONENTE - cifreEsponente; i++) {
        putIn('0', ESPONENTE + 1, esponenteTemp);
    }
    memcpy(risultato->Esponente, esponenteTemp, ESPONENTE);

    // Scrivo il numero in Floating Point
    memset(risultato->Macchina, 0, BIT+1);
    risultato->Macchina[0] = risultato->Segno + 48;
    strncat(risultato->Macchina, risultato->Esponente, ESPONENTE);
    strncat(risultato->Macchina, risultato->Mantissa, MANTISSA);
}

void parseDoppia(double number, precisioneDoppia *risultato) { // Legge un double e lo salva in una variabile di tipo precisioneSingola
    const int BIAS = 1023;
    const int8_t BASE = 2;
    const int BIT = 64;
    const int ESPONENTE = 11;
    const int MANTISSA = 52;

    risultato->Segno = number < 0 ? true : false; // Scrivo il segno
    number = number < 0 ? -1*number : number; // Riscrivo il numero in modulo

    char binario[BIT + 1], esponenteTemp[ESPONENTE + 1];
    size_t cifreIntere = printBinario(number, BIT, binario); // Salvo il numero in binario
    size_t cifreDecimali = strlen(binario) - cifreIntere;
    memset(risultato->Mantissa, 48, MANTISSA + 1); // Scrivo 0 nei primi nella mantissa
    memset(risultato->Esponente, 48, ESPONENTE + 1); // Scrivo 0 nell'esponente
    memset(esponenteTemp, 48, ESPONENTE + 1); // Scrivo 0 nell'esponente
    memset(risultato->Mantissa, 48, MANTISSA); // Scrivo '0' nei primi 23 caratteri della mantissa
    memset(risultato->Esponente, 48, ESPONENTE); // Scrivo '0' nell'esponente
    memset(esponenteTemp, 48, ESPONENTE); // Scrivo '0' nell'esponente
    int Esponente = 0; // Dichiaro l'esponente

    if (cifreIntere > 0) { // Se ho almeno una cifra intera prima della virgola
        Esponente = strlen(binario) - cifreDecimali - 1;
        for (size_t i = 0; i < strlen(binario) - 1; i++) { // Scrivo le cifre nella mantissa
            risultato->Mantissa[i] = binario[i + 1];
        }
    } else if (cifreDecimali > 0) { // Se ho almeno una cifra decimale conto l'esponente negativo
        for (size_t i = 0; i < cifreDecimali; i++) {
            Esponente--;
            if (binario[i] == 49) { // Mi trovo al primo 1 che trovo
                break;
            }
        }

        for (size_t i = -1*Esponente; i < strlen(binario); i++) { // Copio i valori nella mantissa
            risultato->Mantissa[i + Esponente] = binario[i];
        }
    }
    
    size_t cifreEsponente = printBinario(Esponente + BIAS, ESPONENTE, esponenteTemp); // Scrivo l'esponente corretto in binario
    for (size_t i = 0; i < ESPONENTE - cifreEsponente; i++) {
        putIn('0', ESPONENTE + 1, esponenteTemp);
    }
    memcpy(risultato->Esponente, esponenteTemp, ESPONENTE);

    // Scrivo il numero in Floating Point
    memset(risultato->Macchina, 0, BIT+1);
    risultato->Macchina[0] = risultato->Segno + 48;
    strncat(risultato->Macchina, risultato->Esponente, ESPONENTE);
    strncat(risultato->Macchina, risultato->Mantissa, MANTISSA);
}

void parseQuadrupla(long double number, precisioneQuadrupla *risultato) { // Legge un double e lo salva in una variabile di tipo precisioneSingola
    const int BIAS = 16383;
    const int8_t BASE = 2;
    const int BIT = 128;
    const int ESPONENTE = 15;
    const int MANTISSA = 112;

    risultato->Segno = number < 0 ? true : false; // Scrivo il segno
    number = number < 0 ? -1*number : number; // Riscrivo il numero in modulo

    char binario[BIT + 1], esponenteTemp[ESPONENTE + 1];
    size_t cifreIntere = printBinario(number, BIT, binario); // Salvo il numero in binario
    size_t cifreDecimali = strlen(binario) - cifreIntere;
    memset(risultato->Mantissa, 48, MANTISSA + 1); // Scrivo 0 nei primi nella mantissa
    memset(risultato->Esponente, 48, ESPONENTE + 1); // Scrivo 0 nell'esponente
    memset(esponenteTemp, 48, ESPONENTE + 1); // Scrivo 0 nell'esponente
    memset(risultato->Mantissa, 48, MANTISSA); // Scrivo '0' nei primi 23 caratteri della mantissa
    memset(risultato->Esponente, 48, ESPONENTE); // Scrivo '0' nell'esponente
    memset(esponenteTemp, 48, ESPONENTE); // Scrivo '0' nell'esponente
    int Esponente = 0; // Dichiaro l'esponente

    if (cifreIntere > 0) { // Se ho almeno una cifra intera prima della virgola
        Esponente = strlen(binario) - cifreDecimali - 1;
        for (size_t i = 0; i < strlen(binario) - 1; i++) { // Scrivo le cifre nella mantissa
            risultato->Mantissa[i] = binario[i + 1];
        }
    } else if (cifreDecimali > 0) { // Se ho almeno una cifra decimale conto l'esponente negativo
        for (size_t i = 0; i < cifreDecimali; i++) {
            Esponente--;
            if (binario[i] == 49) { // Mi trovo al primo 1 che trovo
                break;
            }
        }

        for (size_t i = -1*Esponente; i < strlen(binario); i++) { // Copio i valori nella mantissa
            risultato->Mantissa[i + Esponente] = binario[i];
        }
    }
    
    size_t cifreEsponente = printBinario(Esponente + BIAS, ESPONENTE, esponenteTemp); // Scrivo l'esponente corretto in binario
    for (size_t i = 0; i < ESPONENTE - cifreEsponente; i++) {
        putIn('0', ESPONENTE + 1, esponenteTemp);
    }
    memcpy(risultato->Esponente, esponenteTemp, ESPONENTE);

    // Scrivo il numero in Floating Point
    memset(risultato->Macchina, 0, BIT+1);
    risultato->Macchina[0] = risultato->Segno + 48;
    strncat(risultato->Macchina, risultato->Esponente, ESPONENTE);
    strncat(risultato->Macchina, risultato->Mantissa, MANTISSA);
}

void printMacchinaSingola(precisioneSingola numero) {
    printf("FLOAT: ");
    puts(numero.Macchina);
}

void printMacchinaDoppia(precisioneDoppia numero) {
    printf("DOUBLE: ");
    puts(numero.Macchina);
}
void printMacchinaQuadrupla(precisioneQuadrupla numero) {
    printf("LONG DOUBLE: ");
    puts(numero.Macchina);
}

void convertLittleEndian(size_t bit, char binario[bit + 1]) {
    for (size_t i = 0; i < bit/32; i++) { // Per ogni riga
        char bit1[9];
        char bit2[9];
        char bit3[9];
        char bit4[9];
        memset(bit1, 0, 9);
        memset(bit2, 0, 9);
        memset(bit3, 0, 9);
        memset(bit4, 0, 9);

        size_t j = i*32; // Parto sempre dalla riga di memoria successiva
        // Scompongo in 4 byte separati
        for (size_t k = 0; k < 8; k++) {
            bit1[k] = binario[j++]; 
        }
        for (size_t k = 0; k < 8; k++) {
            bit2[k] = binario[j++]; 
        }
        for (size_t k = 0; k < 8; k++) {
            bit3[k] = binario[j++]; 
        }
        for (size_t k = 0; k < 8; k++) {
            bit4[k] = binario[j++]; 
        }

        // Ricompongo i 4 byte invertiti di ordine tra di loro
        j = i*32;
        for (size_t k = 0; k < 8; k++) {
            binario[j++] = bit4[k];
        }
        for (size_t k = 0; k < 8; k++) {
            binario[j++] = bit3[k];
        }
        for (size_t k = 0; k < 8; k++) {
            binario[j++] = bit2[k];
        }
        for (size_t k = 0; k < 8; k++) {
            binario[j++] = bit1[k];
        }
    }
}

int main() {
    bigEndian = checkBigEndian();
    float af;
    double ad;
    long double ald;
    scanNumbers(&af, &ad, &ald);
    // af = -0.05;
    precisioneSingola afloat;
    parseSingola(af, &afloat);

    // ad = 1.0005;
    precisioneDoppia adouble;
    parseDoppia(ad, &adouble);

    // ald = 1.0005;
    precisioneQuadrupla alongdouble;
    parseQuadrupla(ald, &alongdouble);

    if (bigEndian == false) {
        convertLittleEndian(32, &afloat.Macchina);
        convertLittleEndian(64, &adouble.Macchina);
        convertLittleEndian(128, &alongdouble.Macchina);
    }
    

    puts("Le rappresentazioni in floating point dei numeri sono:\n");
    printMacchinaSingola(afloat);
    printMacchinaDoppia(adouble);
    printMacchinaQuadrupla(alongdouble);
}
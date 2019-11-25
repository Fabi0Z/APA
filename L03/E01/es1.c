#include <stdio.h>


/* NOTE SU QUESTO ESERCIZIO:
   
   Vorrei far notare che la funzione leggiMatrice assegnata, richiede di passare per parametro
   il valore MAXR, e non da spazio alla possibilità di passare un parametro di tipo FILE *,
   e vorrei evidenziare anche che:
   - MAXR è un valore utilizzato come dimensione limite, ma sopratutto un valore che non ha alcun
     motivo di cambiare nel corso del programma, può benissimo esser considerato un valore costante
     che si potrebbe dichiarare come costante globale o tramite DEFINE, qual è lo scopo di passarlo
     alla variabile leggiMatrice?
   - Il nome del file di testo non è noto a priori, ma bensì digitato da tastiera dall'utente, di 
     conseguenza non può esser dichiarato come costante globale all'inizio del programma, e
     l'unico modo rimanente per potervi accedere globalmente è appunto quello di inzializzare una
     variabile globale contenente il nome del file o il puntatore al filestream, perché imporre 
     questa limitazione riguardante la possibilità di passare il nome del file o il filestream
     come parametro alla funzione leggiMatrice?
*/


FILE *input;
const int MAXR = 50;

typedef struct Regione {
    int Inizio[2], Base, Altezza;
} regione;

int areaRegione(regione rettangolo) {
    return rettangolo.Base * rettangolo.Altezza;
}

int maxAltezzaRegioni(int numeroRegioni, regione regioni[numeroRegioni]) {
    int max = 0;
    for (size_t i = 0; i < numeroRegioni; i++) {
        max = regioni[i].Altezza > max ? regioni[i].Altezza : max;
    }
    return max;
}

int maxLarghezzaRegioni(int numeroRegioni, regione regioni[numeroRegioni]) {
    int max = 0;
    for (size_t i = 0; i < numeroRegioni; i++) {
        max = regioni[i].Base > max ? regioni[i].Base : max;
    }
    return max;
}

int maxAreaRegioni(int numeroRegioni, regione regioni[numeroRegioni]) {
    int max = 0;
    for (size_t i = 0; i < numeroRegioni; i++) {
        max = areaRegione(regioni[i]) > max ? areaRegione(regioni[i]) : max;
    }
    return max;
}

int checkFilestream(FILE *stream) {  // Controlla errori di aperrtura del file
    if (stream == NULL) {
        puts("Errore apertura file");
        exit(1);
    }
    return 0;
}

void leggiMatrice(int MAXR, int M[MAXR][MAXR], int *righe, int *colonne) {
    fscanf(input, "%d %d", righe, colonne);
    for (size_t i = 0; i < *righe; i++) {
        for (size_t j = 0; j < *colonne; j++) {
            fscanf(input, "%d", &M[i][j]);
        }
    }
    fclose(input);
}

void printMatrice(int righe, int colonne, int M[MAXR][MAXR]) {
    for (size_t i = 0; i < righe; i++) {
        for (size_t j = 0; j < colonne; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

FILE* apriFile() { // Chiede quale file aprire e ne restituisce lo stream
    printf("Scrivi il nome del file che vuoi aprire: ");
    char filename[20];
    memset(filename, 0, 20*sizeof(char));
    scanf("%s", filename);
    FILE *stream = fopen(filename, "r");
    checkFilestream(stream);
    
    return stream;
}

int riconosciRegione(int M[MAXR][MAXR], int nr, int nc, int r, int c, int *b, int *h) {
    int flag_c = 0;
    int flag_r = 0; // Flag per controllare che la cella sia un inizio di matrice
    if (M[c][r]) { // Mi fermo se trovo una cella nera
        if (r != 0) { // Controllo che la cella non sia subito sotto il margine 
            flag_c += M[c-1][r] ? 0 : 1; // Se la cella sopra è bianca la condizione per le colonne è verificata
        } else {
            flag_c++; // Se è sotto il margine la condizione per le colonne è verificata
        }
        
        if (c != 0) { // Controllo che la cella non sia subito a destra del margine 
            flag_r += M[c][r-1] ? 0 : 1; // Se la cella a sinistra è bianca la condizione per le righe è verificata
        } else {
            flag_r++; // Se è sotto il margine la condizione per le righe è verificata
        }

        if (flag_c + flag_r != 2) { // Se almeno uno dei due flag non è valido non ho trovato l'inizio di una regione
            return 0;
        } else {
            int c_2 = c;
            while (M[c_2 + 1][r] && c_2 + 1 < nc) c_2++; // Controllo quante celle nere consecutive trovo percorrendo le righe
            *h = c_2 + 1 - c;

            int r_2 = r;
            while (M[c][r_2 + 1] && r_2 + 1 < nr) r_2++; // Controllo quante celle nere consecutive trovo percorrendo le colonne
            *b = r_2 + 1 - r;

            return 1;
        }
    }
    return 0;
}

int contaRegioni(int righe, int colonne, int M[MAXR][MAXR]) {
    int regioniTrovate = 0;
    for (size_t i = 0; i < righe; i++) {
        for (size_t j = 0; j < colonne; j++) {
            int flag_i = 0;
            int flag_j = 0; // Flag per controllare che la cella sia un inizio di matrice
            if (M[i][j]) { // Mi fermo se trovo una cella nera
                if (i != 0) { // Controllo che la cella non sia subito sotto il margine 
                    flag_i += M[i-1][j] ? 0 : 1; // Se la cella sopra è bianca la condizione per i è verificata
                } else {
                    flag_i++; // Se è sotto il margine la condizione per i è verificata
                }
                
                if (j != 0) { // Controllo che la cella non sia subito a destra del margine 
                    flag_j += M[i][j-1] ? 0 : 1; // Se la cella a sinistra è bianca la condizione per j è verificata
                } else {
                    flag_j++; // Se è sotto il margine la condizione per j è verificata
                }

                if (flag_i + flag_j == 2) { // Se entrambi i flag sono validi ho trovato la prima cella di una regione
                    regioniTrovate++;
                }
            }
        }
    }
    return regioniTrovate;
}

void leggiRegioni(int righe, int colonne, int nRegioni, int M[MAXR][MAXR], regione regioni[nRegioni]) {
    int regioniTrovate = 0;
    for (size_t i = 0; i < righe; i++) {
        for (size_t j = 0; j < colonne; j++) {
            int base;
            int altezza;
            if (riconosciRegione(M, righe, colonne, j, i, &base, &altezza)) {
                regioni[regioniTrovate].Inizio[0] = i;
                regioni[regioniTrovate].Inizio[1] = j;
                regioni[regioniTrovate].Base = base;
                regioni[regioniTrovate].Altezza = altezza;
                regioniTrovate++;
            }
        }
    }
}


int main(int argc, char const *argv[]) {
    input = apriFile(); // Apro il file
    int dimensioneMassimaMatrice = MAXR;
    int righe, colonne;
    int matrice[MAXR][MAXR];
    leggiMatrice(dimensioneMassimaMatrice, matrice, &righe, &colonne); // Leggo la matrice
    printf("La dimensione della matrice è %dx%d\n", righe, colonne);
    puts("Il contenuto della matrice è"); // Stampo il contenuto della matrice
    printMatrice(righe, colonne, matrice);

    int regioniTrovate = contaRegioni(righe, colonne, matrice);
    printf("\nSono presenti %d regioni:\n", regioniTrovate);
    regione regioni[regioniTrovate];
    leggiRegioni(righe, colonne, regioniTrovate, matrice, regioni);

    int altezzaMassima = maxAltezzaRegioni(regioniTrovate, regioni);
    int larghezzaMassima = maxLarghezzaRegioni(regioniTrovate, regioni);
    int areaMassima = maxAreaRegioni(regioniTrovate, regioni);

    printf("\nLe regioni più larghe sono quelle di larghezza %d e iniziano agli indici: ", larghezzaMassima);
    for (size_t i = 0; i < regioniTrovate; i++) {
        if (regioni[i].Base == larghezzaMassima) {
            printf("(%d, %d) ", regioni[i].Inizio[0], regioni[i].Inizio[1]);
        }
    }

    printf("\nLe regioni più alte sono quelle di altezza %d e iniziano agli indici: ", altezzaMassima);
    for (size_t i = 0; i < regioniTrovate; i++) {
        if (regioni[i].Altezza == altezzaMassima) {
            printf("(%d, %d) ", regioni[i].Inizio[0], regioni[i].Inizio[1]);
        }
    }

    printf("\nLe regioni più grandi sono quelle di area %d e iniziano agli indici: ", areaMassima);
    for (size_t i = 0; i < regioniTrovate; i++) {
        if (areaRegione(regioni[i]) == areaMassima) {
            printf("(%d, %d) ", regioni[i].Inizio[0], regioni[i].Inizio[1]);
        }
    }
    printf("\n");

    puts("\nLe dimensioni di tutte le regioni sono:");
    for (size_t i = 0; i < regioniTrovate; i++) {
        int size = areaRegione(regioni[i]);
        printf("- Regione n° %d iniziante all'indice (%d, %d): %d\n", i, regioni[i].Inizio[0], regioni[i].Inizio[1], size);
    }

    
    return 0;
}

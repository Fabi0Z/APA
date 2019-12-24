#include "smartfunctions.h"

// Alloca un array
void allocaArray(array a, unsigned int NumeroElementi, unsigned int sizeOf) {
    a->NumeroElementi = NumeroElementi;
    a->Elementi       = (void **)calloc(a->NumeroElementi, sizeof(void *));

    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni elemento
        a->Elementi[i] = (void *)malloc(sizeOf);
    }
}

// Crea un array
array creaArray() {
    return (array)malloc(sizeof(struct Array));
}

// Controlla errori di apertura del file
bool checkFilestream(FILE *stream) {
    return stream == NULL ? false : true;
}

// Elimina un array ed il suo contenuto
void freeArray(array a) {
    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni elemento
        free(a->Elementi[i]);
    }
    free(a);
}

/* Effettua il parse da file di una serie di elementi
   parseObject è la funzione che si occupa di effettuare il parse del singolo oggetto da string
   sizeOf è il risultato della sizeof() sul tipo del dato */
array parseFromFile(char *filename, unsigned int max_string, void *(*parseObject)(char *), unsigned int sizeOf) {
    FILE *stream = smartFopen(filename, "r"); // Apro il filestream

    array a = creaArray();
    fscanf(stream, "%d\n", a->NumeroElementi); // Leggo il numero di attività
    allocaArray(a, a->NumeroElementi, sizeOf); // Alloco la memoria

    char string[max_string + 1];
    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni elemento
        fgets(string, max_string, stream);
        a->Elementi[i] = (void *)(*parseObject)(string);
    }

    return a;
}

// Stampa un "Premi invio per continuare..."
void premiPerContinuare() {
    puts("Premi invio per continuare...");
    getchar();
    getchar();
}

// Apre in maniera sicura un file, interrompe il programma se non è possibile aprirlo
FILE *smartFopen(char *filename, char *mode) {
    FILE *f = fopen(filename, mode);
    if (checkFilestream(f)) {
        return f;
    }
    printf("Errore d'apertura per il file %s\n", filename);
    exit(1);
    return NULL;
}
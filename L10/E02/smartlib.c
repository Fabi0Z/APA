#include "smartlib.h"

// * hidden functions

/* Elimina un array ed il suo contenuto
   freeItem è la funzione per eliminare il singolo elemento */
void freeArray(array a, void (*freeItem)(void *)) {
    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni elemento
        (*freeItem)(a->Elementi[i]);
    }
    free(a);
}

/* Effettua il parse da file di una serie di elementi
   parseObject è la funzione che si occupa di effettuare il parse del singolo oggetto da string */
void parseFromFile(array a, char *filename, unsigned int max_string, void *(*parseObject)(char *)) {
    FILE *stream = smartFopen(filename, "r"); // Apro il filestream

    fscanf(stream, "%u\n", &a->NumeroElementi); // Leggo il numero di attività
    allocaArray(a, a->NumeroElementi);          // Alloco la memoria

    char string[max_string + 1];
    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni elemento
        fgets(string, max_string, stream);
        a->Elementi[i] = (void *)(*parseObject)(string);
    }
    fclose(stream);
}

/* Stampa un array
   printObject è la funzione che stampa il singolo oggetto */
void printArray(array a, void(*printObject(void *))) {
    for (unsigned int i = 0; i < a->NumeroElementi; i++) { // Per ogni elemento
        (*printObject)(a->Elementi[i]);
    }
    printf("\n");
}

// * END static functions

// Alloca un array
void allocaArray(array a, unsigned int NumeroElementi) {
    a->NumeroElementi = NumeroElementi;
    a->Elementi       = (void **)calloc(a->NumeroElementi, sizeof(void *));
}

// Crea un array
array creaArray() {
    array a  = (array)malloc(sizeof(struct Array));
    a->free  = &freeArray;
    a->print = &printArray;
    a->parse = &parseFromFile;
    return a;
}

// Controlla errori di apertura del file
bool checkFilestream(FILE *stream) {
    return stream == NULL ? false : true;
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
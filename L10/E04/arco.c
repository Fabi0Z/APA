#include "arco.h"

// * STATICS

static const uint8_t NUMERO_COPPIE     = 2;
static const unsigned int SAFE_LENGHT  = 51;
static const unsigned int SAFE_SIZE[4] = {SAFE_LENGHT, SAFE_LENGHT, SAFE_LENGHT, SAFE_LENGHT};

// * END OF STATICS

// Calcola la lunghezza dei nomi inseriti
static bool calcolaLunghezze(arco a, unsigned int *sizes) {
    if (a == NULL || sizes == NULL) {
        return false;
    }
    for (uint8_t i = 0; i < NUMERO_COPPIE; i++) { // Per ogni coppia
        sizes[i]                 = strlen(a->IDElaboratori[i]);
        sizes[i + NUMERO_COPPIE] = strlen(a->IDRete[i]);
    }
    return true;
}

/* Alloca memoria per un arco
   sizes è un array di 4 elementi contenenti le dimensioni dei caratteri per le stringhe 
   se sizes == NULL un valore sicuro di default verrà usato */
void allocateArco(arco a, unsigned int *sizes) {
    sizes = sizes == NULL ? (unsigned int *)SAFE_SIZE : sizes;
    for (uint8_t i = 0; i < NUMERO_COPPIE; i++) { // Per ogni coppia
        a->IDElaboratori[i] = calloc(sizes[i], sizeof(char));
        a->IDRete[i]        = calloc(sizes[i + NUMERO_COPPIE], sizeof(char));
    }
}

// Copia SRC in DEST
void copyArco(arco DEST, arco SRC) {
    for (uint8_t i = 0; i < NUMERO_COPPIE; i++) { // Per ogni coppia
        strcpy(DEST->IDElaboratori[i], SRC->IDElaboratori[i]);
        strcpy(DEST->IDRete[i], SRC->IDRete[i]);
    }
    DEST->Flusso = SRC->Flusso;
}

// Elimina un arco
void freeArco(arco a) {
    for (uint8_t i = 0; i < NUMERO_COPPIE; i++) { // Per ogni coppia
        if (a->IDElaboratori[i] != NULL) {
            free(a->IDElaboratori[i]);
        }
        if (a->IDRete[i] != NULL) {
            free(a->IDRete[i]);
        }
    }
}

// Crea un arco
arco newArco() {
    arco a    = malloc(sizeof(struct Arco));
    a->Flusso = 0;

    a->IDElaboratori = calloc(NUMERO_COPPIE, sizeof(char *));
    a->IDRete        = calloc(NUMERO_COPPIE, sizeof(char *));
    for (uint8_t i = 0; i < NUMERO_COPPIE; i++) { // Per ogni coppia
        a->IDElaboratori[i] = NULL;
        a->IDRete[i]        = NULL;
    }
    return a;
}

// Effettua il parse di un argo da stringa
arco parseArco(char *string) {
    arco temp = newArco();
    allocateArco(temp, NULL);

    unsigned int conto = 0;
    for (uint8_t i = 0; i < NUMERO_COPPIE; i++) { // Per ogni coppia
        conto += sscanf(string, "%s%s%[^\n]", temp->IDElaboratori[i], temp->IDRete[i], string);
    }
    conto += sscanf(string, "%u", &temp->Flusso);

    if (conto != NUMERO_COPPIE * 3 + 1) { // Controllo sugli elementi letti
        freeArco(temp);
        return NULL;
    }

    unsigned int sizes[NUMERO_COPPIE * 2];
    calcolaLunghezze(temp, sizes); // Calcolo le lunghezze
    arco a = newArco();
    allocateArco(a, sizes);
    copyArco(a, temp);
    freeArco(temp);

    return a;
}
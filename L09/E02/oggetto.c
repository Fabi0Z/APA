#include "oggetto.h"

struct Oggetto {
    char *Nome;
    char *Tipo;
    stats Statistiche;
};

struct ArrayOggetti {
    oggetto *Array;
    unsigned int NumeroOggetti;
};

struct ArrayPuntatoriOggetti {
    oggetto **Array;
    unsigned int NumeroOggetti;
};

// Alloca memoria per un oggetto di tipo oggetto
void allocaOggetto(oggetto o, unsigned int nomeSize, unsigned int tipoSize) {
    o->Nome        = (char *)calloc(nomeSize, sizeof(char)); // Alloco la memoria
    o->Tipo        = (char *)calloc(tipoSize, sizeof(char));
    o->Statistiche = creaStatistiche();
}

// Dealloca un elemento di tipo oggetto
void freeOggetto(oggetto o) {
    free(o->Nome);
    free(o->Tipo);
    free(o->Statistiche);
    free(o);
}

// Dealloca un elemento di tipo arrayOggetti, se il parametro elementi è true libera anche gli oggetti dentro l'array
void freeArrayOggetti(arrayOggetti a, bool elementi) {
    if (elementi) {
        for (unsigned int i = 0; i < a->NumeroOggetti; i++) { // Per ogni oggetto
            freeOggetto(a->Array[i]);
        }
    }
    free(a);
}

// Dealloca un elemento di tipo arrayPuntatoriOggetti, se il parametro elementi è true libera anche gli oggetti dentro l'array
void freeArrayPuntatoriOggetti(arrayPuntatoriOggetti a, bool elementi) {
    if (elementi) {
        for (unsigned int i = 0; i < a->NumeroOggetti; i++) { // Per ogni oggetto
            freeOggetto(*a->Array[i]);
        }
    }

    free(a);
}

// Stampa un oggetto su file
void printOggetto(oggetto o, FILE *stream) {
    fprintf(stream, "%s %s ", o->Nome, o->Tipo);
    printStatistiche(o->Statistiche, stream);
    fprintf(stream, "\n");
}

// Stampa un oggetto su file
void printArrayOggetti(arrayOggetti a, FILE *stream, bool indici) {
    for (unsigned int i = 0; i < a->NumeroOggetti; i++) {
        if (indici) {
            fprintf(stream, "%zu - ", i);
        }
        printOggetto(a->Array[i], stream);
        printf("\n");
    }
}

// Stampa un oggetto su file
void printArrayPuntatoriOggetti(arrayPuntatoriOggetti a, FILE *stream, bool indici) {
    for (unsigned int i = 0; i < a->NumeroOggetti; i++) {
        if (indici) {
            fprintf(stream, "%zu - ", i);
        }
        printOggetto(*a->Array[i], stream);
        printf("\n");
    }
}

// Crea, alloca e restituisce un oggetto
oggetto creaOggetto(unsigned int nomeSize, unsigned int tipoSize) {
    oggetto temp = (oggetto)malloc(sizeof(struct Oggetto));
    allocaOggetto(temp, nomeSize, tipoSize);
    return temp;
}

// Crea e restituisce un array di oggetti non allocati
arrayOggetti creaArrayOggetti(unsigned int NumeroOggetti) {
    arrayOggetti a;
    a->NumeroOggetti = NumeroOggetti;
    a->Array         = (oggetto *)calloc(NumeroOggetti, sizeof(oggetto));
    return a;
}

// Crea e restituisce un array di oggetti non allocati
arrayPuntatoriOggetti creaArrayPuntatoriOggetti(unsigned int NumeroOggetti) {
    arrayPuntatoriOggetti a;
    a->NumeroOggetti = NumeroOggetti;
    a->Array         = (oggetto **)calloc(NumeroOggetti, sizeof(oggetto *));
    return a;
}

// Copia src in dest
void copiaOggetto(oggetto dest, oggetto src) {
    memcpy(dest->Statistiche, src->Statistiche, sizeof(int16_t) * N_STATISTICHE);
    strcpy(dest->Nome, src->Nome);
    strcpy(dest->Tipo, src->Tipo);
}

// Copia gli oggetti di src in dest
void copiaArrayOggetti(arrayOggetti dest, arrayOggetti src) {
    unsigned int min = dest->NumeroOggetti < src->NumeroOggetti ? dest->NumeroOggetti : src->NumeroOggetti;
    for (unsigned int i = 0; i < min; i++) { // Per il numero minimo di oggetti
        copiaOggetto(dest->Array[i], src->Array[i]);
    }
}

// Copia gli oggetti di src in dest
void copiaArrayPuntatoriOggetti(arrayPuntatoriOggetti dest, arrayPuntatoriOggetti src) {
    unsigned int min = dest->NumeroOggetti < src->NumeroOggetti ? dest->NumeroOggetti : src->NumeroOggetti;
    for (unsigned int i = 0; i < min; i++) { // Per il numero minimo di oggetti
        copiaOggetto(*dest->Array[i], *src->Array[i]);
    }
}

// Effettua il parse di un personaggio da stringa, restituisce se la lettura è andata a buon fine o meno
bool leggiOggetto(char *string, oggetto o) {
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "%s %[^\n]", o->Nome, string);
    conteggio += sscanf(string, "%s %[^\n]", o->Tipo, string);

    stats s = creaStatistiche();
    if (!leggiStatistiche(string, s)) { // Se la lettura delle statistiche fallisce
        return false;
    }
    o->Statistiche = creaStatistiche();
    copiaStatistiche(o->Statistiche, s);
    free(s);
    return conteggio == 4;
}

// Aggiunge un oggetto ad un array di oggetti
void aggiungiOggettoArray(arrayOggetti a, oggetto o) {
    if (a->NumeroOggetti == 0) { // Se non ho oggetti
        freeArrayOggetti(a, false);
        a           = creaArrayOggetti(1);
        a->Array[0] = o;
        return;
    }

    // Creo nuovo array oggetti
    arrayOggetti new = creaArrayOggetti(a->NumeroOggetti + 1);
    memcpy(new->Array, a->Array, sizeof(oggetto *) * a->NumeroOggetti);

    // Inserisco il nuovo oggetto
    new->Array[a->NumeroOggetti] = o;

    // Sostituisco l'array di oggetti
    a->Array = new->Array;
    freeArrayOggetti(new, false);
}

// Aggiunge un oggetto ad un array di oggetti
void aggiungiOggettoArrayPuntatori(arrayPuntatoriOggetti a, oggetto *o) {
    if (a->NumeroOggetti == 0) { // Se non ho oggetti
        freeArrayPuntatoriOggetti(a, false);
        a           = creaArrayPuntatoriOggetti(1);
        a->Array[0] = o;
        return;
    }

    // Creo nuovo array oggetti
    arrayPuntatoriOggetti new = creaArrayPuntatoriOggetti(a->NumeroOggetti + 1);
    memcpy(new->Array, a->Array, sizeof(oggetto **) * a->NumeroOggetti);

    // Inserisco il nuovo oggetto
    new->Array[a->NumeroOggetti] = o;

    // Sostituisco l'array di oggetti
    a->Array = new->Array;
    freeArrayPuntatoriOggetti(new, false);
}

// Restituisce il nome di un oggetto
char *getNomeOggetto(oggetto o) {
    return o->Nome;
}

// Restituisce il tipo di un oggetto
char *getTipoOggetto(oggetto o) {
    return o->Tipo;
}

// Restituisce le statistiche di un oggetto
stats getStatisticheOggetto(oggetto o) {
    return o->Statistiche;
}

// Restituisce l'oggetto nella posizione index dell'array
oggetto getOggettoByIndex(arrayOggetti a, unsigned int index) {
    return a->Array[index];
}

// Restituisce il puntatore a oggetto nella posizione index dell'array
oggetto *getOggettoPointerByIndex(arrayPuntatoriOggetti a, unsigned int index) {
    return a->Array[index];
}

// Cerca un oggetto per nome nell'array di oggetti, se non lo trova restituisce NULL
oggetto getOggettoByName(arrayOggetti a, char *nome) {
    for (unsigned int i = 0; i < a->NumeroOggetti; i++) { // Per ogni oggetto
        if (strcmp(nome, a->Array[i]->Nome) == 0) {       // Se il nome corrisponde
            return a->Array[i];
        }
    }
    return NULL;
}

// Cerca un puntatore a oggetto per nome nell'array di oggetti, se non lo trova restituisce NULL
oggetto *getPuntatoreOggettoByName(arrayPuntatoriOggetti a, char *nome) {
    for (unsigned int i = 0; i < a->NumeroOggetti; i++) { // Per ogni oggetto
        oggetto temp = *a->Array[i];
        if (strcmp(nome, temp->Nome) == 0) { // Se il nome corrisponde
            return a->Array[i];
        }
    }
    return NULL;
}
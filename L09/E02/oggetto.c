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

// Dealloca un elemento di tipo arrayOggetto, se il parametro elementi è true libera anche gli oggetti dentro l'array
void freeArrayOggetti(arrayOggetti a, bool elementi) {
    if (elementi) {
        for (unsigned int i = 0; i < a->NumeroOggetti; i++) { // Per ogni oggetto
            freeOggetto(a->Array[i]);
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
void aggiungiOggetto(arrayOggetti a, oggetto o) {
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
#include "oggetto.h"

// Alloca memoria per un oggetto di tipo oggetto
void allocaOggetto(oggetto o, unsigned int nomeSize, unsigned int tipoSize) {
    o->Nome        = (char *)calloc(nomeSize, sizeof(char)); // Alloco la memoria
    o->Tipo        = (char *)calloc(tipoSize, sizeof(char));
    o->Statistiche = creaStatistiche();
}

// Copia src in dest
void copiaOggetto(oggetto dest, oggetto src) {
    memcpy(dest->Statistiche, src->Statistiche, sizeof(int16_t) * N_STATISTICHE);
    strcpy(dest->Nome, src->Nome);
    strcpy(dest->Tipo, src->Tipo);
}

// Crea, alloca e restituisce un oggetto
oggetto creaOggetto(unsigned int nomeSize, unsigned int tipoSize) {
    oggetto temp = (oggetto)malloc(sizeof(struct Oggetto));
    allocaOggetto(temp, nomeSize, tipoSize);
    return temp;
}

// Dealloca un elemento di tipo oggetto
void freeOggetto(oggetto o) {
    free(o->Nome);
    free(o->Tipo);
    free(o->Statistiche);
    free(o);
}

// Restituisce il nome di un oggetto
char *getNomeOggetto(oggetto o) {
    return o->Nome;
}

// Restituisce le statistiche di un oggetto
stats getStatisticheOggetto(oggetto o) {
    return o->Statistiche;
}

// Restituisce il tipo di un oggetto
char *getTipoOggetto(oggetto o) {
    return o->Tipo;
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

// Stampa un oggetto su file
void printOggetto(oggetto o, FILE *stream) {
    fprintf(stream, "%s %s ", o->Nome, o->Tipo);
    printStatistiche(o->Statistiche, stream);
    fprintf(stream, "\n");
}
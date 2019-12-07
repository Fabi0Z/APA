#include "oggetto.h"
#include "statistiche.h"

// Alloca memoria per un oggetto di tipo oggetto
void allocaOggetto(oggetto *o, unsigned int nomeSize, unsigned int tipoSize) {
    o->Nome = (char *)calloc(nomeSize, sizeof(char)); // Alloco la memoria
    o->Tipo = (char *)calloc(tipoSize, sizeof(char));
}

// Dealloca un elemento di tipo oggetto
void freeOggetto(oggetto *o) {
    free(o->Nome);
    free(o->Tipo);
    free(o);
}

// Stampa un oggetto su file
void printOggetto(oggetto *o, FILE *stream) {
    fprintf(stream, "%s %s ", o->Nome, o->Tipo);
    printStatistiche(o->Statistiche, stream);
    fprintf(stream, "\n");
}

// Crea, alloca e restituisce un oggetto
oggetto *creaOggetto(unsigned int nomeSize, unsigned int tipoSize) {
    oggetto *temp = (oggetto *)malloc(sizeof(oggetto));
    allocaOggetto(temp, nomeSize, tipoSize);
    return temp;
}

// Copia src in dest
void copiaOggetto(oggetto *dest, oggetto *src) {
    memcpy(dest->Statistiche, src->Statistiche, sizeof(int16_t) * N_STATISTICHE);
    strcpy(dest->Nome, src->Nome);
    strcpy(dest->Tipo, src->Tipo);
}

// Effettua il parse di un personaggio da stringa, restituisce se la lettura è andata a buon fine o meno
bool leggiOggetto(char *string, oggetto *o) {
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "%s %[^\n]", o->Nome, string);
    conteggio += sscanf(string, "%s %[^\n]", o->Tipo, string);

    stats s = creaStatistiche();
    if (!leggiStatistiche(string, s)) { // Se la lettura delle statistiche fallisce
        return false;
    }
    copiaStatistiche(o->Statistiche, s);
    free(s);
    return conteggio == 4;
}
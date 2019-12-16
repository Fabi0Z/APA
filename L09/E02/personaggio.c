#include "personaggio.h"

// Alloca memoria per un oggetto di tipo personaggio
void allocaPersonaggio(personaggio p, unsigned int nomeSize, unsigned int classeSize) {
    p->Nome            = (char *)calloc(nomeSize, sizeof(char)); // Alloco la memoria
    p->Classe          = (char *)calloc(classeSize, sizeof(char));
    p->Equipaggiamento = creaEquipaggiamento();
    p->Statistiche     = creaStatistiche();
}

// Aggiunge un oggetto all'equipaggiamento di un personaggio
void aggiungiEquipaggiamento(personaggio p, oggetto o) {
    aggiungiOggettoEquipaggiamento(p->Equipaggiamento, o);
}

// Calcola e restituisce le statistiche di un personaggio
void calcolaStatistiche(personaggio p, stats s) {
    copiaStatistiche(s, p->Statistiche); // Scrivo i valori del personaggio

    if (getNumeroOggettiEquipaggiamento(p->Equipaggiamento) == 0) { // Se non ci sono oggetti nell'equipaggiamento mi interrompo
        return;
    }

    oggetto *o;
    for (size_t i = 0; i < N_STATISTICHE; i++) {                                           // Per ogni statistica
        for (size_t j = 0; j < getNumeroOggettiEquipaggiamento(p->Equipaggiamento); j++) { // Per ogni oggetto dell'equipaggiamento
            o = getOggettoEquipaggiamentoByIndex(p->Equipaggiamento, j);
            s[i] += getStatisticheOggetto(*o)[i];
        }

        if (s[i] < 1) {
            s[i] = 1;
        }
        memcpy(p->Statistiche, s, sizeof(int16_t) * N_STATISTICHE);
    }
}

// Copia src in dest
void copiaPersonaggio(personaggio dest, personaggio src) {
    // Copio i dati diretti
    dest->ID = src->ID;

    // Copio i dati per puntatore
    strcpy(dest->Nome, src->Nome);
    strcpy(dest->Classe, src->Classe);

    if (src->Statistiche != NULL) {
        copiaStatistiche(dest->Statistiche, src->Statistiche);
    }

    if (src->Equipaggiamento != NULL) {
        copiaEquipaggiamento(dest->Equipaggiamento, src->Equipaggiamento);
    }
}

// Crea, alloca e restituisce un personaggio senza equipaggiamento
personaggio creaPersonaggio(unsigned int nomeSize, unsigned int classeSize) {
    personaggio temp = (personaggio)malloc(sizeof(struct Personaggio));
    allocaPersonaggio(temp, nomeSize, classeSize);
    return temp;
}

// Dealloca un personaggio
void freePersonaggio(personaggio p) { // Dealloca la memoria di un personaggio
    if (p->Equipaggiamento != NULL) { // Se è presente un equipaggiamento
        freeEquipaggiamento(p->Equipaggiamento);
    }
    free(p->Nome);
    free(p->Classe);
    free(p->Statistiche);
    free(p);
}

// Alloca memoria per realizzare una copia ridimensionata del personaggio
personaggio getResizedPersonaggio(personaggio temp) {
    personaggio p = creaPersonaggio(strlen(temp->Nome), strlen(temp->Classe));
    return p;
}

// Effettua il parse di un personaggio da stringa, restituisce se la lettura è andata a buon fine o meno
bool leggiPersonaggio(char *string, personaggio p) {
    uint8_t conteggio = 0;
    conteggio += sscanf(string, "PG%" SCNd16 "%[^\n]", &p->ID, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Nome, string);
    conteggio += sscanf(string, "%s %[^\n]", p->Classe, string);

    stats s = creaStatistiche();
    if (!leggiStatistiche(string, s)) { // Se la lettura delle statistiche fallisce
        return false;
    }
    copiaStatistiche(p->Statistiche, s);
    return conteggio == 6;
}

// Stampa un personaggio
void printPersonaggio(personaggio p, FILE *stream) {
    fprintf(stream, "PG%04" SCNd16, p->ID);
    fprintf(stream, " %s %s ", p->Nome, p->Classe);
    printStatistiche(p->Statistiche, stream);
    fprintf(stream, "\n");
}

// Rimuove un oggetto dall'equipaggiamento di un personaggio
bool rimuoviEquipaggiamento(personaggio p, oggetto o) {
    return rimuoviOggettoEquipaggiamento(p->Equipaggiamento, o);
}

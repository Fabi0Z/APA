#include "elemento.h"

static const uint8_t MAX_STRING = 150;

// Crea un elemento
elemento creaElemento() {
    elemento e = (elemento)malloc(sizeof(struct Elemento));
    e->Nome    = NULL;
    return e;
}

// Elimina un elemento
void freeElemento(elemento e) {
    free(e->Nome);
    free(e);
}

// Legge e crea un elemento da stringa
elemento parseElemento(char *string) {
    elemento e = creaElemento();
    char tempNome[MAX_STRING];

    sscanf(string, "%s%[^\n]", tempNome, string);               // Leggo il nome
    sscanf(string, "%" SCNd8 "%[^\n]", &e->Tipo, string);       // Leggo il tipo
    sscanf(string, "%" SCNd8 "%[^\n]", &e->Ingresso, string);   // Leggo l'ingresso
    sscanf(string, "%" SCNd8 "%[^\n]", &e->Uscita, string);     // Leggo l'uscita
    sscanf(string, "%" SCNd8 "%[^\n]", &e->Precedenza, string); // Leggo la precedenza
    sscanf(string, "%" SCNd8 "%[^\n]", &e->Finale, string);     // Leggo il finale
    sscanf(string, "%" SCNd8 "%[^\n]", &e->Ingresso, string);   // Leggo l'ingresso
    sscanf(string, "%f%[^\n]", &e->Valore, string);             // Leggo il valore
    sscanf(string, "%u", &e->Difficolta);                       // Leggo la difficoltà

    // Copio il nome ridimensionato
    e->Nome = (char *)calloc(strlen(tempNome), sizeof(char));
    strcpy(e->Nome, tempNome);
}
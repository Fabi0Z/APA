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
    return e;
}

// Stampa un elemento
void printElemento(elemento e) {
    printf("%s ", e->Nome);               // Stampo il nome
    printf("%" SCNd8 " ", e->Tipo);       // Stampo il tipo
    printf("%" SCNd8 " ", e->Ingresso);   // Stampo l'ingresso
    printf("%" SCNd8 " ", e->Uscita);     // Stampo l'uscita
    printf("%" SCNd8 " ", e->Precedenza); // Stampo la precedenza
    printf("%" SCNd8 " ", e->Finale);     // Stampo il finale
    printf("%" SCNd8 " ", e->Ingresso);   // Stampo l'ingresso
    printf("%f ", e->Valore);             // Stampo il valore
    printf("%u\n", e->Difficolta);        // Stampo la difficoltà
}
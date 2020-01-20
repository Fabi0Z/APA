#ifndef LISTAADICENZE_H
#define LISTAADICENZE_H

#include "adiacenza.h"
#include "array.h"
#include "list.h"

typedef struct ListaAdicenze {
    array Indici;
} * listaAdicenze;

void freeListaAdiacenza(listaAdicenze l);
listaAdicenze newListaAdiacenze(unsigned int NumeroVertici);
bool addAdiacenza(listaAdicenze l, unsigned int Index, unsigned int Destinazione, unsigned int Peso);

#endif // ! LISTAADICENZE_H

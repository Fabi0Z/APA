#ifndef GRAFO_H
#define GRAFO_H

#include "ListaAdicenze.h"
#include "SymbleTable.h"
#include "arco.h"
#include "matriceAdiacenze.h"
#include "sortlib.h"

struct Grafo;
typedef struct Grafo *grafo;

void reorderVertexByName(grafo g);
bool minorUgualeNomeVertice(unsigned int *a, unsigned int *b, grafo g);
void printGrafo(grafo g);
grafo parseGrafo(char *filename);
void creaListaAdiacenze(grafo g);
grafo creaGrafo(unsigned int NumeroVertici, unsigned int NumeroArchi);

#endif // ! GRAFO_H

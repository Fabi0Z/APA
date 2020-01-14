#ifndef MATRICEADIACENZE_H
#define MATRICEADIACENZE_H

#include <stdlib.h>

typedef struct MatriceAdiacenze {
    unsigned int **Matrix;
    unsigned int Size;
} * matriceAdiacenze;

void freeMatrice(matriceAdiacenze m);
matriceAdiacenze creaMatrice(unsigned int size);

#endif // ! MATRICEADIACENZE_H

#ifndef MEMOIZATIONMATRIX_H
#define MEMOIZATIONMATRIX_H

#include "arrayCollane.h"
#include <inttypes.h>
#include <stdbool.h>

typedef struct MemoizationMatrix *memoizationMatrix;

void salvaMassimo(memoizationMatrix m, unsigned int *posizione, unsigned int massimo);
unsigned int maxSmeraldi(unsigned int *pietre, memoizationMatrix m);
unsigned int maxTopazi(unsigned int *pietre, memoizationMatrix m);
unsigned int maxRubini(unsigned int *pietre, memoizationMatrix m);
unsigned int maxZaffiri(unsigned int *pietre, memoizationMatrix m);
unsigned int maxCollana(unsigned int *pietre, memoizationMatrix *m);
unsigned int leggiMassimo(memoizationMatrix m, unsigned int *posizione);
memoizationMatrix creaMemoizationMatrix();
void calcolaDimensioniMatrice(arrayCollane a, memoizationMatrix m);
void allocaMemoizationMatrix(memoizationMatrix m);

#endif // MEMOIZATIONMATRIX_H

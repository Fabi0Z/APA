#ifndef MEMOIZATIONMATRIX_H
#define MEMOIZATIONMATRIX_H

#include "arrayCollane.h"

typedef struct MemoizationMatrix *memoizationMatrix;

void salvaMassimo(memoizationMatrix m, unsigned int *posizione, unsigned int massimo);
unsigned int maxSmeraldi(unsigned int *pietre);
unsigned int maxTopazi(unsigned int *pietre);
unsigned int maxRubini(unsigned int *pietre);
unsigned int maxZaffiri(unsigned int *pietre);
unsigned int maxCollana(unsigned int *pietre);
unsigned int leggiMassimo(memoizationMatrix m, unsigned int *posizione);
memoizationMatrix creaMemoizationMatrix();
void calcolaDimensioniMatrice(arrayCollane a, memoizationMatrix m);
void allocaMemoizationMatrix(memoizationMatrix m);

#endif // MEMOIZATIONMATRIX_H

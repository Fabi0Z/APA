#ifndef MEMOIZATIONMATRIX_H
#define MEMOIZATIONMATRIX_H

#include "collana.h"
#include <inttypes.h>
#include <stdbool.h>

typedef struct MemoizationMatrix *memoizationMatrix;

void salvaMassimo(memoizationMatrix m, unsigned int *posizione, unsigned int massimo);
unsigned int maxSmeraldi(unsigned int *pietre, memoizationMatrix m);
unsigned int maxTopazi(unsigned int *pietre, memoizationMatrix m);
unsigned int maxRubini(unsigned int *pietre, memoizationMatrix m);
unsigned int maxZaffiri(unsigned int *pietre, memoizationMatrix m);
unsigned int maxCollana(collana c);
unsigned int leggiMassimo(memoizationMatrix m, unsigned int *posizione);
void freeMemoizationMatrix(memoizationMatrix m);
memoizationMatrix creaMemoizationMatrix();
bool checkPietreDisponibili(pietra p, unsigned int *pietre);
void calcolaDimensioniMatrice(collana c, memoizationMatrix m);
void allocaMemoizationMatrix(memoizationMatrix m);

#endif // MEMOIZATIONMATRIX_H

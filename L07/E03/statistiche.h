#if !defined(STATISTICHE_H)
#define STATISTICHE_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum { HP,
               MP,
               ATK,
               DEF,
               MAG,
               SPR,
               N_STATISTICHE } statsField;
typedef int16_t *stats;

bool leggiStatistiche(char *string, stats s);
void printStatistiche(stats s, FILE *stream);
stats creaStatistiche();
void copiaStatistiche(stats dest, stats src);

#endif // STATISTICHE_H

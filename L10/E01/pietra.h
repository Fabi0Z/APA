#ifndef PIETRA_H
#define PIETRA_H

#include <stdio.h>

typedef enum { zaffiro,
               rubino,
               topazio,
               smeraldo,
               totale } pietra;

void printPietra(pietra p);

#endif // PIETRA_H

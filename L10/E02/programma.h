#ifndef PROGRAMMA_H
#define PROGRAMMA_H

#include "elemento.h"
#include "smartlib.h"

typedef array *programma;

void freeGruppoDiagonali(programma g);
programma creaGruppoDiagonali(void (*freeObject)(void *), void *(*parseObject)(char *), void (*printObject)(void *));

#endif // PROGRAMMA_H

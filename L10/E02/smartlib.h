#ifndef SMARTLIB_H
#define SMARTLIB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef void *item;

void premiPerContinuare();
FILE *smartFopen(char *filename, char *mode);
bool checkFilestream(FILE *stream);

#endif // SMARTLIB_H

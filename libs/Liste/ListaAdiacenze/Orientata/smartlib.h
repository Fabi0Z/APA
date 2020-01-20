#ifndef SMARTLIB_H
#define SMARTLIB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *item;

void premiPerContinuare();
bool equalStrings(char *a, char *b);
FILE *smartFopen(char *filename, char *mode);
unsigned int countNumberOfLines(char *filename);
bool checkFilestream(FILE *stream);

#endif // ! SMARTLIB_H

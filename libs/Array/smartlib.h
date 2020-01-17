#ifndef SMARTLIB_H
#define SMARTLIB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *item;

FILE *smartFopen(char *filename,char *mode);
void premiPerContinuare();
bool equalStrings(char *a,char *b);
bool checkFilestream(FILE *stream);

#endif // ! SMARTLIB_H

#ifndef SMARTLIB_H
#define SMARTLIB_H

#include <stdbool.h>
#include <stdio.h>

void premiPerContinuare();
FILE *smartFopen(char *filename, char *mode);
bool checkFilestream(FILE *stream);

#endif // SMARTLIB_H

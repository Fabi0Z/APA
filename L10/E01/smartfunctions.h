#ifndef SMARTFUNCTIONS_H
#define SMARTFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

FILE *smartFopen(char *filename, char *mode);
bool checkFilestream(FILE *stream);
void premiPerContinuare();

#endif // SMARTFUNCTIONS_H

#ifndef SYMBLETABLE_H
#define SYMBLETABLE_H

#include "Symble.h"
#include "array.h"

struct SymbleTable;
typedef struct SymbleTable *symbleTable;

bool updateSymbleTableItemIndex(symbleTable s, unsigned int Index, unsigned int NewIndex);
bool updateSymbleTableItemName(symbleTable s, unsigned int Index, char *NewName);
unsigned int numberOfItem(symbleTable s);
symbleTable newSymbleTable(unsigned int MaxItems);
char *getSymbleName(symbleTable s, unsigned int Index);
void freeSymbleTable(symbleTable s);
unsigned int getSymbleIndex(symbleTable s, char *Name);
bool checkSymbleByIndex(symbleTable s, unsigned int Index);
bool checkSymbleByName(symbleTable s, char *Name);
bool addSymble(symbleTable s, char *Name);

#endif // ! SYMBLETABLE_H

#include "SymbleTable.h"

struct SymbleTable {
    array Table;
    unsigned int AddedItems;
};

// * STATIC

// Restituisce true se il valore è fuori dal range
static bool OutOfRange(symbleTable s, unsigned int Index) {
    return Index >= s->AddedItems;
}

// Restituisce true se si ha raggiunto il numero di elementi
static bool MaxLimit(symbleTable s) {
    return s->AddedItems >= s->Table->ObjectsNumber;
}

// * END OF STATIC

// Aggiunge un simbolo
bool addSymble(symbleTable s, char *Name) {
    if (MaxLimit(s)) { // Se supero il limite
        return false;
    }
    if (!checkSymbleByName(s, Name)) { // Se esiste già un elemento con questo nome
        return false;
    }
    s->Table->Objects[s->AddedItems++] = newSymble(strlen(Name)); // Creo il simbolo
    updateSymbleName(s->Table->Objects[s->AddedItems], Name);     // Aggiorno il nome
    return true;
}

// Controlla se il valore esiste o meno
bool checkSymbleByIndex(symbleTable s, unsigned int Index) {
    if (OutOfRange(s, Index)) { // Interruzione numero non possibile
        return false;
    }
    return s->Table->Objects[Index] != NULL;
}

// Controlla se il nome esiste o meno
bool checkSymbleByName(symbleTable s, char *Name) {
    unsigned int index = getSymbleIndex(s, Name);
    return index == (unsigned int)-1 ? false : true;
}

// Elimina una symbleTable
void freeSymbleTable(symbleTable s) {
    freeArray(s->Table, true);
    free(s);
}

// Restituisce l'indice dell'elemento con il nome corrispondente a Name, se non lo trova restituisce (unsigned int)-1
unsigned int getSymbleIndex(symbleTable s, char *Name) {
    for (unsigned int i = 0; i < s->AddedItems; i++) { // Per ogni elemento inserito
        symble tmp = s->Table->Objects[i];
        if (equalStrings(tmp->Name, Name)) { // Se l'elemento è uguale
            return i;
        }
    }
    return (unsigned int)-1;
}

// Restituisce il nome di un simbolo a partire dall'indice
char *getSymbleName(symbleTable s, unsigned int Index) {
    if (OutOfRange(s, Index)) { // Se non esiste l'elemento
        return NULL;
    }
    symble temp = s->Table->Objects[Index];
    return temp->Name;
}

// Crea una nuova symbleTable
symbleTable newSymbleTable(unsigned int MaxItems) {
    symbleTable s = malloc(sizeof(struct SymbleTable));
    s->Table      = newArray((void *)freeSymble, NULL, NULL); // Creo l'array
    allocateArray(s->Table, MaxItems);                        // Alloco l'array
    s->AddedItems = 0;
    return s;
}

// Modifico un symble della table
bool updateSymble(symbleTable s, unsigned int Index, char *Name) {
    if (OutOfRange(s, Index)) { // Interruzione numero non possibile
        return false;
    }
    symble temp = s->Table->Objects[Index];
    updateSymbleName(temp, Name);
    return true;
}
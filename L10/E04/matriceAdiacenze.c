#include "matriceAdiacenze.h"

static const unsigned int DEFAULT_VALUE = 0;

// Crea una matrice di adiacenze
matriceAdiacenze creaMatrice(unsigned int size) {
    matriceAdiacenze m = malloc(sizeof(struct MatriceAdiacenze));
    m->Size            = size;

    if (m->Size == 0) { // Se la dimensione è 0
        m->Matrix = NULL;
        return m;
    }

    m->Matrix = calloc(m->Size, sizeof(unsigned int *));      // Alloco per le X
    for (unsigned int i = 0; i < m->Size; i++) {              // Per ogni X
        m->Matrix[i] = calloc(m->Size, sizeof(unsigned int)); // Alloco celle Y
        for (unsigned int j = 0; j < m->Size; j++) {
            m->Matrix[i][j] = DEFAULT_VALUE; // Assegno il valore di default
        }
    }
    return m;
}

// Elimina una matrice di adiacenze
void freeMatrice(matriceAdiacenze m) {
    if (m == NULL) {
        return;
    }
    if (m->Matrix == NULL) {
        free(m);
        return;
    }
    for (unsigned i = 0; i < m->Size; i++) {
        free(m->Matrix[i]);
    }
    free(m->Matrix);
    free(m);    
}
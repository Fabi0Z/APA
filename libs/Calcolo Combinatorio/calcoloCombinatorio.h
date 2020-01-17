#ifndef CALCOLOCOMBINATORIO_H
#define CALCOLOCOMBINATORIO_H

#include "array.h"

unsigned int combinazioniRipetuteRecursive(unsigned int posizione, array valori, array soluzione, unsigned int start);
unsigned int combinazioniRipetute(array valori, array soluzione);
unsigned int diposizioniRipetuteDefault(array valori, array soluzione);
bool _NEXT_copyNext(array valori, array soluzione, unsigned int posizione, unsigned int i);
unsigned int _ENDINGS_printOnly(array soluzione, unsigned int posizione);
bool _CHECKS_posizioneLunghezzaSoluzione(array soluzione, unsigned int posizione);
unsigned int _PRESET_disposizioniRipetute(array valori, array soluzione, unsigned int posizione, bool (*check)(array, unsigned int), unsigned int (*ending)(array, unsigned int), bool (*next)(array, array, unsigned int, unsigned int));

#endif // CALCOLOCOMBINATORIO_H

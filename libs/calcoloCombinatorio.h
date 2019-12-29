#ifndef CALCOLOCOMBINATORIO_H
#define CALCOLOCOMBINATORIO_H

#include "smartlib.h"

unsigned int diposizioniRipetuteDefault(array valori, array soluzione);
bool _NEXT_copyNext(array valori, array soluzione, unsigned int posizione, unsigned int i);
unsigned int _ENDINGS_printOnly(array valori, array soluzione, unsigned int posizione);
bool _CHECKS_posizioneLunghezzaSoluzione(array valori, array soluzione, unsigned int posizione);
unsigned int _PRESET_disposizioniRipetute(array valori, array soluzione, unsigned int posizione, bool (*check)(array, array, unsigned int), unsigned int (*ending)(array, array, unsigned int), bool (*next)(array, array, unsigned int, unsigned int));

#endif // CALCOLOCOMBINATORIO_H

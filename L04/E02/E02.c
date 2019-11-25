#include <stdio.h>
#include <string.h>

typedef struct Massimale {
    int Valore;
    size_t Occorrenze;
} massimale;


massimale majorityRecursive(int *Array, size_t begin, size_t end) { // Restituisce un massimale ricorsivamente
    if (begin == end) { // Se ho un vettore unitario ne restituisco i valori
        massimale risultato;
        risultato.Valore = Array[begin];
        risultato.Occorrenze = 1;
        return risultato;
    }

    size_t middle = (begin + end) / 2;
    massimale sinistro = majorityRecursive(Array, begin, middle);
    massimale destro = majorityRecursive(Array, middle + 1, end);

    if (sinistro.Valore == destro.Valore) { // Se i risulati dei massimali sinistro e destro sono uguali ne sommo le occorrenze
        sinistro.Occorrenze += destro.Occorrenze;
        return sinistro;
    }

    if (sinistro.Occorrenze > destro.Occorrenze) { // Se il sinistro è presente più volte lo restituisco
        return sinistro;
    }

    if (sinistro.Occorrenze < destro.Occorrenze) { // Se il destro è presente più voolte lo restituisco 
        return destro;
    }
    
    massimale nonTrovato;
    nonTrovato.Valore = -1;
    nonTrovato.Occorrenze = 0;
    return nonTrovato; // Altrimento restituisco il valore di non trovato
    
}

int majority(int *Array, size_t N) { // Restituisce l'elemento maggioritario di un array
    massimale risultato = majorityRecursive(Array, 0, N-1);
    risultato.Occorrenze = 0;
    for (size_t i = 0; i < N; i++) { // Conto le occorrenze del massimale calcolato ricorsivamente
        risultato.Occorrenze += risultato.Valore == Array[i] ? 1 : 0;
    }

    return risultato.Occorrenze > N/2 ? risultato.Valore : -1; // Se le occorrenze sono maggiori di N/2 restituisco il massimale, altrimenti non vi è alcun massimale
}

int main(int argc, char const *argv[]) {
    int array[7] = {3, 3, 9, 4, 3, 5, 3};
    printf("L'elemento maggioritario è: %d\n", majority(array, 7));
    return 0;
}

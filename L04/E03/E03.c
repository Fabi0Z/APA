#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum RegexpressionType { punto,
                                 quadre,
                                 apice,
                                 minuscola,
                                 maiuscola,
                                 perfectMatch } regexpressionType;
typedef struct Regexpression { // Dichiaro struct per regrexpression
    char *Espressione;
    regexpressionType Tipo;
    size_t Caratteri;
} regexpression;

regexpressionType isRegexpChar(char *c) { // Restituisce -1 se il carattere NON è un simbolo di regex, altrimenti il corrispondente enum
    switch (*c) {
        case '.': {
            return punto;
            break;
        }
        case '[': {
            return *(c + 1) == '^' ? apice : quadre;
            break;
        }

        case '\\': {
            return *(c + 1) == 'a' ? minuscola : maiuscola;
            break;
        }

        default: {
            return perfectMatch;
            break;
        }
    }
}

regexpression nextRegexp(char *Espressione) { // Restituisce la prossima regexp
    size_t i = 0;
    regexpression risultato;
    size_t lunghezza = strlen(Espressione);

    switch (isRegexpChar(&Espressione[i])) { // Esamino la tringa regexp
        case punto: {
            risultato.Espressione = &Espressione[0]; // Restituisco come posizione il punto stesso
            risultato.Tipo        = punto;
            risultato.Caratteri   = 1;
            return risultato;
            break;
        }

        case quadre: {
            risultato.Tipo        = quadre;
            risultato.Espressione = &Espressione[1];
            i++;
            while (i < lunghezza && Espressione[i] != ']')
                i++;
            risultato.Caratteri = i;
            break;
        }

        case apice: {
            risultato.Tipo        = apice;
            risultato.Espressione = &Espressione[2];
            i += 2;
            while (i < lunghezza && Espressione[i] != ']')
                i++;
            risultato.Caratteri = i - 1;
            break;
        }

        case minuscola: {
            risultato.Espressione = &Espressione[1]; // Restituisco come posizione la lettera dopo '\'
            risultato.Tipo        = minuscola;
            risultato.Caratteri   = 1;
            return risultato;
            break;
        }

        case maiuscola: {
            risultato.Espressione = &Espressione[1]; // Restituisco come posizione la lettera dopo '\'
            risultato.Tipo        = maiuscola;
            risultato.Caratteri   = 1;
            return risultato;
            break;
        }

        case perfectMatch: {
            while (i < lunghezza && isRegexpChar(&Espressione[i]) == perfectMatch)
                i++; // Sinché mi trovo di fronte lettere normali continuo a leggere l'array
            risultato.Espressione = &Espressione[0];
            risultato.Caratteri   = i;
            risultato.Tipo        = perfectMatch;
            return risultato;
            break;
        }
    }
}

bool checkRegexp(char *string, regexpression *regexp) { // Restituisce se un determinato carattere (o serie consecutiva di caratteri) rispettano la regexp
    size_t lunghezza = strlen(string);

    switch (regexp->Tipo) { // Analizzo i vari casi in base al tipo di vincolo
        case punto: {
            return true;
            break;
        }

        case quadre: {
            for (size_t i = 0; i < regexp->Caratteri; i++) { // Per ogni carattere del vincolo
                if (*string == regexp->Espressione[i]) {     // Se è uguale ad almeno uno dei caratteri indicati dall'espressione
                    regexp->Caratteri = 1;                   // Indico di aver controllato un solo carattere
                    return true;
                }
            }

            return false;
            break;
        }

        case apice: {
            for (size_t i = 0; i < regexp->Caratteri; i++) { // Per ogni carattere del vincolo
                if (*string == regexp->Espressione[i]) {     // Se è uguale anche a solo uno dei caratteri indicati dall'espressione
                    return false;
                }
            }

            regexp->Caratteri = 1; // Indico di aver controllato un solo carattere
            return true;
            break;
        }

        case minuscola: {
            return tolower(*string) == *string ? true : false; // Se è una lettera minuscola restituisco true, altrimenti false
            break;
        }

        case maiuscola: {
            return toupper(*string) == *string ? true : false; // Se è una lettera maiuscola restituisco true, altrimenti false
            break;
        }

        case perfectMatch: {
            return strncmp(string, regexp->Espressione, regexp->Caratteri) == 0 ? true : false; // Se la strncmp mi conferma che le stringhe sono uguali restituisco true, altrimenti false
        }
        default: {
            break;
        }
    }

    return false; // risposta false preventiva
}

bool cercaRegexpRecursive(char *string, char *espressione) { // Funzione ricorsiva per trovare regexp
    if (strlen(espressione) == 0) {                          // Se ho esaurito l'espressione l'intero controllo è andato a buon fine
        return true;
    }

    regexpression vincolo = nextRegexp(espressione);
    char *prossimoVincolo = &vincolo.Espressione[vincolo.Caratteri]; // Preparo il puntatore al prossimo vincolo
    bool prossimoControllo;
    if (checkRegexp(string, &vincolo)) {                    // Se l'espressione è verificata passo al prossimo vincolo
        char *prossimaStringa = &string[vincolo.Caratteri]; // Sposto il puntatore per n posizioni pari al numero di caratteri trovati
        prossimoControllo     = cercaRegexpRecursive(prossimaStringa, prossimoVincolo);
    } else { // Se il vincolo non è verificato restituisco false
        return false;
    }

    return prossimoControllo; // Restituisco il valore del vincolo successivo
}

char *cercaRegexp(char *src, char *regexp) {         // Trova l'indice di una regexp corrispondente
    for (size_t i = 0; i < strlen(src); i++) {       // Per ogni carattere della stringa
        if (cercaRegexpRecursive(&src[i], regexp)) { // Se la ricerca ricorsiva restituisce vero interrompo
            return &src[i];
        }
    }

    return NULL;
}

int main() {
    char stringa[]   = "foto moto coto kyoto";
    char controllo[] = ".[^fmc]oto";

    char *indice = cercaRegexp(stringa, controllo);

    if (indice != NULL) {
        printf("La stringa trovata è: \"%s\"\n", indice);
    } else {
        puts("Non è stato trovato alcun indice corrispondente");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define N 6

typedef struct Attivita {
    int va;
    int vb;
} attivita;
attivita *riempi(char nomefile[50]);
void LISprint(attivita *val, int *P, int i);
void LISDP(attivita *val);

int main() {

    attivita *b;
    char nomefile[50];
    printf("inserisci Nome file:\n>>");
    scanf("%s", nomefile);
    b = riempi(nomefile);
    LISDP(b);

    return 0;
}

void LISDP(attivita *val) {
    int i, j, ris, tmp = 0, c, L[N], P[N], last;
    ris  = 1; // patat e cozz
    last = 1;
    L[0] = val[0].vb - val[0].va;
    P[0] = -1;
    for (i = 1; i < N; i++) {
        L[i] = val[i].vb - val[i].va; //lunghezza
        P[i] = -1;                    //provenienza
        for (j = 0; j < i; j++)
            if ((val[j].vb <= val[i].va)) {
                c = L[j] + (val[i].vb - val[i].va);
                if (c > tmp) {
                    P[i] = j;
                    L[i] = c;
                    tmp  = L[i];
                }
            }

        if (ris < L[i]) {
            ris  = L[i];
            last = i;
        }
    }
    printf("One of the Longest Increasing Sequences is ");
    LISprint(val, P, last);
    printf("\n");
    printf("and its length is %d\n", ris);
}

void LISprint(attivita *val, int *P, int i) {
    if (P[i] == -1) {
        printf("%d->%d \n", val[i].va, val[i].vb);
        return;
    }
    LISprint(val, P, P[i]);
    printf("%d->%d \n", val[i].va, val[i].vb);
}

attivita *riempi(char nomefile[50]) {
    attivita *a;
    int numrighe;
    FILE *f1;
    f1 = fopen(nomefile, "r");
    fscanf(f1, "%d", &numrighe);
    a = (attivita *)malloc(numrighe * sizeof(attivita));
    for (int i = 0; i < numrighe; i++) {
        fscanf(f1, "%d", &a[i].va);
        fscanf(f1, "%d", &a[i].vb);
    }
    for (int i = 0; i < numrighe; i++) {
        printf("%d->", a[i].va);
        printf("%d\n", a[i].vb);
    }
    return a;
}
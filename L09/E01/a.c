#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int LISR(int *val, int i) {
    int j, ris;
    ris = 1;
    for (j = 0; j < i; j++)
        if (val[j] < val[i])
            ris = max(ris, 1 + LISR(val, j));
    return ris;
}

int LIS(int *val, int N) {
    int i, res = 0, tmp;
    for (i = 0; i < N; i++) {
        tmp = LISR(val, i);
        if (tmp > res)
            res = tmp;
    }
    return res;
}

void printLIS(int *array, int lenght, int *lisOUT, int lisOUTL) {

}

void LISS()

int main(int argc, char const *argv[]) {
    int array[6] = {11, 14, 13, 7, 8, 15};

    int a = LIS(array, 6);
    printf("%d\n", a);
    return 0;
}

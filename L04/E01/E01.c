#include <stdio.h>

int isEven(int a) {
    return !(a%2);
}

int gcd(int a, int b) { // Restituisce GCD tra due numeri
    if (a == b) { // Se sono uguali restituisco il GCD
        return a;
    } else if (a < b) { // Scambio variabili
        int temp = a;
        a = b;
        b = temp;
    }
    
    if (isEven(a) && isEven(b)) {
        return 2 * gcd(a/2, b/2);
    } else if (!isEven(a) && isEven(b)) {
        return gcd(a, b/2);
    } else if (!isEven(a) && !isEven(b)){
        return gcd((a-b)/2, b);
    } else {
        return gcd(a/2, b);
    }
}

int main() {
    printf("GCD tra 600 e 54: %d\n", gcd(600, 54));
    return 0;
}
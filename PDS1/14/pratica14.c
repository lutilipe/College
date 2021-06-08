#include <stdio.h>
#include <string.h>
#include "pratica14.h"

unsigned long long cubeSum(int n) {
    if (n <= 0) return 0;
    
    return n*n*n + cubeSum(n - 1);
}

void printNAsc(int n) {
    if (n <= 0) return;

    printNAsc(n - 1);

    printf("%i\n", n);
}

void printNDes(int n) {
    if (n <= 0) return;

    printf("%i\n", n);

    printNDes(n - 1);
}

int sumArray(int V[], int n) {
    if (n == 0) return V[0];
    if (n < 0) return 0;
    n -= 1; 

    return V[n] + sumArray(V, n);
}

int medianArray(int V[], int n) {
    return (sumArray(V, n )) / n;
}

unsigned long long fakePow(int x, int y) {
    if (y <= 0) return 1;
    return x * fakePow(x, y - 1);
}

void invertString(char *str) {
    if(*str) {
        invertString(str+1);
        putchar(*str);
    }
}

void invertInt(int i) {
    int sum = 0, rem;
    if (i == 0) return ;

    printf("%i", i % 10);
    invertInt(i / 10);
}

void intToBinary(int i) {
    if (i == 1) {
        printf("%i", 1);
        return;
    };
    intToBinary(i / 2);
    printf("%i", i % 2);

}

int minVec(int i[], int len) {
    int atual = i[len - 1];
    int menor;
    if (len - 1 == 0) {
        return i[len - 1];
    } else {
        menor = minVec(i, len - 1);
        if (menor < atual) {
            return menor;
        } else {
            return atual;
        }
    }
}
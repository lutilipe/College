#include <stdio.h>

float parteInteira(float x) {
    return (int) x;
}

float parteFracionaria(float x) {
    int y = (int) x;
    return x - y;
}

float divInts(int x, int y) {
    return (float) x / y;
}

void soma1(int* x) {
    *x += 1;
}

void troca(float* x, float* y) {
    float tmp = *y;
    *y = *x;
    *x = tmp;
}

unsigned long long fast_pow_2(int expoente) {
    unsigned long long x = 1;
    return x << expoente;
}

int ddd(unsigned int number) {
    return (int) (number / 100000000);
}

int soma1SePar(unsigned int number) {
    int isEven = !(number % 2);
    return number + isEven;
}

int parOuImpar(unsigned int number) {
    return !(number % 2);
}

void main() {
    printf("%llu", fast_pow_2(61));
}
#include <stdio.h>
#include "pratica6.h"

int main() {
    double result = 1;
    int i = 1;
    while (1) {
        float divisor = factorial(i);
        if (divisor < 0.000001) {
            break;
        }
        result = result + (1 / divisor);
        i++;
    }
    printf("%lf", result);
    return 1;
}
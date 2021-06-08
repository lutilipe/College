#include <stdio.h>
#include "estatistica.h"

int main() {
    float result1, result2, result3;
    result1 =  cauchy(-2);
    result2 =  gumbel(0, 0.5, 2);
    result3 =  laplace(-6, -5, 4);
    printf("Resultado caunchy: %f\nResultado gumbel: %f\nResultado laplace: %f", result1, result2, result3);
    return 0;
}
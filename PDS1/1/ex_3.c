#include <stdio.h>

void main() {
    float primeiro_mes, segundo_mes, terceiro_mes;

    primeiro_mes = 789.54;
    segundo_mes = primeiro_mes * 1.0056 + 303.20;
    terceiro_mes = segundo_mes * 1.0056 - 58.25;
    printf("%6.2f", terceiro_mes * 1.0056);
}
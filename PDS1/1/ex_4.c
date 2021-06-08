#include <stdio.h>

void main() {
    float peso, altura, imc;

    scanf("%f", &peso);
    scanf("%f", &altura);

    imc = peso / (altura * altura);

    printf("IMC: %4.2f", imc);
}
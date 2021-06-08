#include "pratica.h"
#include <stdio.h>

void main() {
    float peso, altura, peso_ideal;
    char sexo;
    printf("Digite seu sexo (M ou F):\n");
    scanf("%c", &sexo);
    printf("Digite seu peso:\n");
    scanf("%f", &peso);
    printf("Digite seu altura:\n");
    scanf("%f", &altura);
    
    peso_ideal = pesoIdeal(altura, sexo);

    if (peso_ideal > peso) {
        printf("Voce precisa ganhar: %.2f", peso_ideal - peso);
    } else {
        printf("Voce precisa perder: %.2f", peso - peso_ideal);
    }
}
#include "pratica.h"
#include <stdio.h>

void main() {
    int x, y, mmc_r, mdc_r;
    
    printf("Digite o primeiro numero:\n");
    scanf("%i", &x);
    while (x <= 0) {
        printf("Por favor, insira um numero maior que 0:\n");
        scanf("%i", &x);
    }
    printf("Digite o segundo numero:\n");
    scanf("%i", &y);
    while (y <= 0) {
        printf("Por favor, insira um numero maior que 0:\n");
        scanf("%i", &y);
    }

    mdc_r = mdc(x, y);
    mmc_r = mmc(x, y);

    printf("MMC: %i\nMDC: %i", mmc_r, mdc_r);
}
#include "pratica.h"
#include "stdio.h"

void main() {
    int maior_3_r,
    ehPar_r,
    ehDivisivelPor3ou5_r,
    somaImpares_r,
    somaNumerosDiv3ou5_r,
    numeroDivisores_r,
    enesimoFibonacci_r,
    mmc_r, 
    mdc_r;

    float paraMetrosPorSegundo_r,
    areaCirculo_r,
    pesoIdeal_r,
    calculaMedia_r;

    double fatorial_r;

    maior_3_r = maior3(4, 25, 8);
    ehPar_r = ehPar(5);
    ehDivisivelPor3ou5_r = ehDivisivelPor3ou5(8);
    somaImpares_r = somaImpares(9);
    somaNumerosDiv3ou5_r = somaNumerosDiv3ou5(9);
    numeroDivisores_r = numeroDivisores(18);
    enesimoFibonacci_r = enesimoFibonacci(8);
    mmc_r = mmc(18, 12);
    mdc_r = mdc(18, 12);

    paraMetrosPorSegundo_r = paraMetrosPorSegundo(72);
    areaCirculo_r = areaCirculo(2);
    pesoIdeal_r = pesoIdeal(1.8, 'M');
    calculaMedia_r = calculaMedia(2, 4, 9, 2);

    fatorial_r = fatorial(5);

    printf("Maior_3: %i\nEhPar: %i\nEhDivisivelPor3ou5: %i\nSomaImpares: %i\nSomaDiv3ou5: %i\nNdivisiores: %i\nFibonnaci: %i\nMMC: %i\nMDC: %i\nParaM/s: %.2f\nAreaCirculo: %.2f\nPesoIdeal: %.2f\nCalculaMedia: %.2f\nFatorial: %.2f", 
        maior_3_r,
        ehPar_r,
        ehDivisivelPor3ou5_r,
        somaImpares_r,
        somaNumerosDiv3ou5_r,
        numeroDivisores_r,
        enesimoFibonacci_r,
        mmc_r, 
        mdc_r,
        paraMetrosPorSegundo_r,
        areaCirculo_r,
        pesoIdeal_r,
        calculaMedia_r,
        fatorial_r
    );
}
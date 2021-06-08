#include "pratica.h"
#include <math.h>

float paraMetrosPorSegundo(float v) {
    return v / 3.6;
}

float areaCirculo(float raio) {
    return 2 * M_PI * raio;
}

int maior3(int n1, int n2, int n3) {
    if ((n1 > n2) && (n1 > n3)) {
        return n1;
    } else if ((n2 > n1) && (n2 > n3)) {
        return n2;
    }

    return n3;
}

int ehPar(int n) {
    return !(n % 2);
}

int ehDivisivelPor3ou5(int n) {
    if (((n % 3 == 0) && (n % 5 == 0)) || ((n % 3 != 0) && (n % 5 != 0))) {
        return 0;
    } else if ((n % 3 == 0) || (n % 5 == 0)) {
        return 1;
    }
}

float pesoIdeal(float h, char sexo) {
    if (sexo == 'M') {
        return (72.7 * h) - 58;
    } else if (sexo == 'F') {
        return (62.1 * h) - 44.7;
    }
}

int somaImpares(int N) {
    int contador, resultado = 0;
    for (contador = 1; contador <= N; contador++) {
        if (contador % 2 == 1) {
            resultado += contador;
        }
    }
    return resultado;
}

double fatorial(int N) {
    double resultado = 1;
    while (N > 1) {
        resultado *= N;
        N--;
    }
    return resultado;
}

int somaNumerosDiv3ou5(int N) {
    int contador, resultado = 0;
    for (contador = 1; contador <= N; contador++) {
        if ((contador % 3 == 0) || (contador % 5 == 0)) {
            resultado += contador;
        }
    }
    return resultado;
}

float calculaMedia(int x, int y, int z, int operacao) {
    if (operacao == 1) {
        return pow(x * y * z, 1/3);
    } else if (operacao == 2) {
        return ((x + 2) * (y + 3) * z) / 6;
    } else if (operacao == 3) {
        return 3 / ((1 / x) + (1 / y) + (1 / z));
    } else if (operacao == 4) {
        return (x + y + z) / 3;
    }
}

int numeroDivisores(int N) {
    int contador, resultado = 0;
    for (contador = 1; contador <= N; contador++) {
        if (N % contador == 0) {
            resultado++;
        }
    }
    return resultado;
}

int enesimoFibonacci(int N) {
    int contador,
    tmp,
    numero_anterior = 0,
    numero_atual = 1,
    resultado;
    for (contador = 3; contador <= N; contador++) {
        tmp = numero_atual;
        numero_atual += numero_anterior;
        numero_anterior = tmp;
        if (contador == N) {
            resultado = numero_atual;
        }
    }    
    return resultado;
}

int mdc(unsigned int x, unsigned int y) {
    int maior, menor;
    if (x > y) {
        maior = x;
        menor = y;
    } else {
        maior = y;
        menor = x;
    }
    while(menor != 0){
        int tmp = maior % menor;
        maior = menor;
        menor = tmp;
    }
    return maior;
}

int mmc(unsigned int x, unsigned int y) {
    int maior, menor;
    if (x > y) {
        maior = x;
        menor = y;
    } else {
        maior = y;
        menor = x;
    }
    return maior * (menor / mdc(maior, menor));
}

#include "pratica7.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int escalar(int vec1[], int vec2[], int n) {
    int i = 0, result = 0;
    for (i = 0; i < n; i++) {
        result += vec1[i] * vec2[i];
    }

    return result;
}

int vecIncludes(int num, int vec[]) {
    int i = 0;
    for (i = 0; i <= 1000; i++) {
        if (vec[num]) {
            return 1;
        }
    }

    return 0;
}

unsigned long long fibonnaci(int num, int vec[]) {
    printf("%i ", vecIncludes(num, vec));
    if (vecIncludes(num, vec)) { 
        return vec[num];
    }

    return (fibonnaci(num - 1, vec) + fibonnaci(num - 2, vec));
}

double media(int num) {
    int vec[num], i=0;
    double result;
    srand(time(NULL));
    for (i =0; i < num; i++) {
        vec[i] = rand();
    }
    for (i =0; i < num; i++) {
        printf("%i %i\n", i, vec[i]);
        result += vec[i];
    }
    return (double) result / (double) num;
}

void intercalate(int vec1[], int vec2[], int vec3[], int n) {
    int i = 0 , j = 0;
    for (i = 0; i < n - 1; i+=2) {
        vec3[i] = vec1[j];
        vec3[i+1] = vec2[j];
        j++;
    }
}

void invertVec(int vec[], int vecInv[], int n) {
    int i =0;
    for (n = n - 1; n >= 0; n--) {
        vecInv[i] = vec[n];
        i++;
    }
}

int randBirth() {
    srand(time(NULL));
    return rand() % 366;
}

int vecIncludes2(int num, int vec[], int n) {
    int i = 0;
    for (i = 0; i <= n; i++) {
        if (vec[num]) {
            return 1;
        }
    }
}
   

void vecUnion(int vec1[], int vec2[], int vec3[], int n) {
    int i = 0, includesI, includesJ;
    for (i = 0; i < n; i++) {
        vec1[i] = randBirth();
        vec2[i] = randBirth();
    }
    for (i = 0; i < n; i++) {
        includesI = vecIncludes2(vec1[i], vec3, i);
        includesJ = vecIncludes2(vec2[i], vec3, i);
        printf("%i %i\n", includesI, includesJ);
        if ((!includesI) && (includesJ)) {
            vec3[i] = vec1[i];
        } else if ((!includesJ) && (includesI)) {
            vec3[i] = vec2[i];
        } else if ((!includesJ) && (includesI)) {
            vec3[i] = vec1[i];
            vec3[i + 1] = vec2[i + 1];
            i++;
        }
    }

    for (i = 0; i < n; i++) {
        if (vec3[i]) {
        }
    }
}

int randRep(int num, int length) {
    int vec[length], i =0, maior = 0, menor = 0, j = 0, tmp = 0;
    srand(time(NULL));
    for (i = 0; i < length; i++) {
        vec[i] = 0;
    }
    for (i = 0; i < num; i++) {
        tmp = rand() % length;
        vec[tmp] += 1;
    }
    maior = vec[0];
    menor = vec[0];
    for (i = 0; i < length; i++) {
        if (vec[i] > maior) {
            maior = vec[i];
        }
        if (vec[i] < menor) {
            menor = vec[i];
        }
    }

    return maior - menor;
}
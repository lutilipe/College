#include <stdio.h>
#include <stdlib.h>
#include "redesocial.h"

int M[NUM_PESSOAS][NUM_PESSOAS];

void inicializar_rede() {
    int i, j;
    for (i = 0; i < NUM_PESSOAS; i++) {
        for (j = 0; j < NUM_PESSOAS; j++) {
            M[i][j] = 0;
        }
    }
}

void adicionar_amizade(int i, int j) {
    M[i][j] = 1;
    M[j][i] = 1;
}

float random_float() {
    return rand() / (float) RAND_MAX;
}

void popularRedeSocialAleatoriamente(float P) {
    int i, j;
    float halfPeople = NUM_PESSOAS / 2.0, num;
    for (i = 0; i < halfPeople; i++) {
        for (j = 0; j < NUM_PESSOAS; j++) {
            num = random_float();
            if (!(num >= P) && i != j) {
                M[i][j] = 1;
                M[j][i] = 1;
            }
        }
    }
}

void imprimirRedeSocial() {
    int i, j;
    printf("\n");
    for (i = 0; i < NUM_PESSOAS; i++) {
        for (j = 0; j < NUM_PESSOAS; j++) {
            printf("%5d", M[i][j]);
        }
        printf("\n");
    }
}

int numAmigosEmComum(int v, int u) {
    int i, count = 0;
    for (i = 0; i < NUM_PESSOAS; i++) {
        if (M[v][i] == 1 && (M[u][i] == 1)) {
            count++;
        }
    }
    return count;
}

int numero_de_amigos(int v) {
    int i, count = 0;
    for (i = 0; i < NUM_PESSOAS; i++) {
        if (M[v][i] == 1) {
            count++;
        }
    }
    return count;
}

float coeficienteAglomeracao(int v) {
    int n = numero_de_amigos(v), count = 0, i, j;
    float halfPeople = NUM_PESSOAS / 2.0;
    for (i = 0; i < NUM_PESSOAS; i++) {
        if (!(M[v][i] == 1)) continue;
        for (j = 0; j < NUM_PESSOAS; j++) {
            if (!(M[i][j] == 1)) continue;
            if (M[v][j] == 1) {
                count++;
            }
        }
    }
    return (count / 2.0) / (n * (n - 1) / 2);
}
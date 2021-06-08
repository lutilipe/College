#include <stdio.h>
#include <stdlib.h>

void alocaMatriz(float ***M, int n) {
    int i = 0;
    *M = (float**)malloc(n * sizeof(float*));

    for (i = 0; i < n; i++) {
        (*M)[i] = (float*)malloc(n * sizeof(float));
    }
}

void preencheMatriz(float ***M, int n) {
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            (*M)[i][j] = 0.0;
        }
    }
}

void imprimeMatriz(float **M, int n) {
    int i = 0, j = 0; 
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%5.2f", M[i][j]);
        }
        printf("\n");
    }
}

void liberaMatriz(float **M, int n) {
    int i = 0;
    for (i = 0; i < n; i++) {
        free(M[i]);
    }
}

int main() {
    float **M = NULL;
    int n, i = 0, j = 0;

    scanf("%i", &n);
    /* M = (float**)malloc(n * sizeof(float*));
    for (i = 0; i < n; i++) {
        M[i] = (float*)malloc(n * sizeof(float));
    } */

    alocaMatriz(&M, n);

    preencheMatriz(&M, n);

    imprimeMatriz(M, n);

    liberaMatriz(M, n);

    return 0;
}
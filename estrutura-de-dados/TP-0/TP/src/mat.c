#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

void createMatrix(Matrix * mat, int tx, int ty, int id) {
// Descricao: cria matriz dinamica com dimensoes tx X ty
// Entrada: mat, tx, ty, id
// Saida: mat

  // verifica se os valores de tx e ty são validos
    erroAssert(tx>0,"Dimensao nula");
    erroAssert(ty>0,"Dimensao nula");

    // inicializa as dimensoes da matriz
    mat->M = tx;
    mat->N = ty;
    // inicializa o identificador da matriz, para rastreamento
    mat->id = id;
    // inicializa a matriz dinamica
    mat->m = (double **)malloc(mat->M * sizeof(double*));
    for (int i = 0; i < mat->M; i++) {
        mat->m[i] = (double *)malloc(mat->N * sizeof(double));
    }
}

void initNullMatrix(Matrix * mat) {
    // Descricao: inicializa mat com valores nulos 
    // Entrada: mat
    // Saida: mat

    int i, j;
    // inicializa todos os elementos da matriz com 0, por seguranca 
    for (i = 0; i < mat->M; i++) {
        for(j = 0; j < mat->N; j++) {
            mat->m[i][j] = 0;
            ESCREVEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
        }
    }
}

void initMatrixFromFile(char* filename, Matrix * mat, int id) {
    // Descricao: le matriz de um arquivo e inicializa a mesma
    // Entrada: filename, mat, id 
    // Saida: mat

    FILE *file;
    file = fopen(filename, "r");
    int N, M;

    // Verifica se o arquivo existe
    erroAssert(file != NULL, "Arquivo nao encontrado");

    erroAssert(fscanf(file, "%d %d", &M, &N), "Tamanho da matriz nao definido");
    erroAssert(N > 0 && M > 0,"Dimensao nula");
    createMatrix(mat, M, N, id);
    for (int i = 0; i < mat->M; i++) {
        for (int j = 0; j < mat->N; j++) {
            erroAssert(fscanf(file, "%lf", &(mat->m[i][j])), "Tamanho da matriz nao definido");
            ESCREVEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
        }
    }
    fclose(file);
}

double accessMatrix(Matrix * mat) {
    // Descricao: acessa mat para fins de registro de acesso 
    // Entrada: mat 
    // Saida: mat

    int i, j;
    double aux, s=0.0;
    for (i=0; i<mat->M; i++) {
        for(j=0; j<mat->N; j++) {
            aux = mat->m[i][j];
            s+=aux;
            LEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
        }
    }
    return s; // apenas para evitar que acesso seja eliminado
}

void printMatrix(Matrix * mat) {
    // Descricao: imprime a matriz com a identificacao de linhas e colunas
    // Entrada: mat
    // Saida: impressao na saida padrao (stdout) 

    int i,j;

    // imprime os identificadores de coluna
    printf("%9s"," ");
    for(j=0; j<mat->N; j++) {
        printf("%8d ",j);
    }
    printf("\n");

    // imprime as linhas
    for (i=0; i<mat->M; i++) {
        printf("%8d ",i);
        for(j=0; j<mat->N; j++) {
            printf("%8.2f ",mat->m[i][j]);
            LEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
        }
        printf("\n");
    }
}

void sumMatrix(Matrix *a, Matrix *b, Matrix *c) {
    // Descricao: soma as matrizes a e b e armazena o resultado em c
    // Entrada: a, b
    // Saida: c

    int i,j;
    // verifica se as dimensoes das matrizes a e b sao as mesmas
    erroAssert(a->M==b->M,"Dimensoes incompativeis");
    erroAssert(a->N==b->N,"Dimensoes incompativeis");

    // inicializa a matriz c garantindo a compatibilidade das dimensoes
    createMatrix(c,a->M, a->N, c->id);

    // faz a soma elemento a elemento
    for (i=0; i<a->M; i++) {
        for(j=0; j<a->N; j++) {
            c->m[i][j] = a->m[i][j]+b->m[i][j];
            LEMEMLOG((long int)(&(a->m[i][j])),sizeof(double),a->id);
            LEMEMLOG((long int)(&(b->m[i][j])),sizeof(double),b->id);
            ESCREVEMEMLOG((long int)(&(c->m[i][j])),sizeof(double),c->id);
        }
    }
}

void multiplyMatrix(Matrix *a, Matrix *b, Matrix *c) {
    // Descricao: multiplica as matrizes a e b e armazena o resultado em c
    // Entrada: a,b
    // Saida: c

    int i,j,k;
    // verifica a compatibilidade das dimensoes 
    erroAssert(a->N==b->M,"Dimensoes incompativeis");

    // cria e inicializa a matriz c
    createMatrix(c,a->M, b->N,c->id);

    // realiza a multiplicacao de matrizes
    for (i=0; i<c->M;i++) {
        for (j=0; j<c->N;j++) {
            for (k=0; k<a->N;k++) {
                c->m[i][j] += a->m[i][k]*b->m[k][j];
                LEMEMLOG((long int)(&(a->m[i][k])),sizeof(double),a->id);
                LEMEMLOG((long int)(&(b->m[k][j])),sizeof(double),b->id);
                ESCREVEMEMLOG((long int)(&(c->m[i][j])),sizeof(double),c->id);
            }
        }
    }
}

void transposeMatrix(Matrix *a, Matrix *b) {
    // Descricao: transpoe a matriz a
    // Entrada: a
    // Saida: a
 
    createMatrix(b,a->N, a->M,b->id);

    for (int i = 0; i < a->M; ++i) {
        for (int j = 0; j < a->N; ++j) {
            b->m[j][i] = a->m[i][j];
            LEMEMLOG((long int)(&(a->m[i][j])),sizeof(double),a->id);
            ESCREVEMEMLOG((long int)(&(b->m[j][i])),sizeof(double),b->id);
        }
    }
}

void writeMatrixToFile(char* filename, Matrix* mat) {
    // Descricao: escreve a matriz de entrada em um arquivo
    // Se o arquivo nao existir, o mesmo e' criado
    // Entrada: filename, mat 
    // Saida: mat


    FILE *file;
    file = fopen(filename, "rb+");
    // Checa se o arquivo especificado existe. Se nao, cria ele
    if(file == NULL) {
        file = fopen(filename, "wb");
        erroAssert(file != NULL, "Erro na criacao do arquivo");
    }

    int i = 0, j = 0;

    fprintf(file,"%d %d\n", mat->M, mat->N);
    for(i = 0;i < mat->M; i++) {
        for(j = 0; j < mat->N; j++) {
            fprintf(file,"%lf ",mat->m[i][j]);
        }
        fprintf(file,"\n");
    }
}

void destroyMatrix(Matrix *a) {
    // Descricao: destroi a matriz a, que se torna inacessível
    // Entrada: a
    // Saida: a
    
    // apenas um aviso se a matriz for destruida mais de uma vez
    avisoAssert(((a->M>0 && a->N>0) || (a->N != NULL)),"Matriz já foi destruida");

    int i = 0;

    for(i = 0; i < a->M; i++)
        free(a->m[i]);
    free(a->m);

    // torna as dimensoes invalidas
    a->id = a->M = a->N = -1;
}

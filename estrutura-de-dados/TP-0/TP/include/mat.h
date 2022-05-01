#ifndef MATRIX_H
#define MATRIX_H

#include "memlog.h"

typedef struct Matrix{
	double **m;
	int N, M;
	int id;
} Matrix;

void initMatrixFromFile(char* filename, Matrix * mat, int id);
void createMatrix(Matrix * mat, int tx, int ty, int id);
void initNullMatrix(Matrix * mat);
double accessMatrix(Matrix * mat);
void printMatrix(Matrix * mat);
void writeMatrixToFile(char* filename, Matrix *mat);
void sumMatrix(Matrix * a, Matrix * b, Matrix * c);
void multiplyMatrix(Matrix * a, Matrix * b, Matrix * c);
void transposeMatrix(Matrix *a, Matrix *b);
void destroyMatrix(Matrix *a);

#endif

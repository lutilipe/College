#ifndef MATRIX_H
#define MATRIX_H

#include "memlog.h"

#ifndef MAXTAM 
#define MAXTAM 500
#endif

typedef struct Matrix{
	double m[MAXTAM][MAXTAM];
	int i, j;
	int id;
} Matrix;

void createMatrix(Matrix * mat, int tx, int ty, int id);
void initNullMatrix(Matrix * mat);
void initRandomMatrix(Matrix * mat);
double accessMatrix(Matrix * mat);
void printMatrix(Matrix * mat);
void writeElement(Matrix * mat, int x, int y, double v);
double readElement (Matrix * mat, int x, int y);
void copyMatrix(Matrix * src, Matrix * dst, int dst_id);
void sumMatrix(Matrix * a, Matrix * b, Matrix * c);
void multiplyMatrix(Matrix * a, Matrix * b, Matrix * c);
void transposeMatrix(Matrix *a);
void destroyMatrix(Matrix *a);

#endif

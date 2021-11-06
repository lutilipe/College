// matrix.cpp
#include "matrix.h"
#include <iostream>

double** createMatrix(int m, int n) {
    double** a = new double*[m];
    for (int i = 0; i < m; i++) {
        a[i] = new double[n];
    }
    return a;
}

// contrutor default - cria uma matriz vazia com nRows = nCols = 0  
Matrix::Matrix(){
    this->nRows = 0;
    this->nCols = 0;
    this->m[this->nRows][this->nCols];
}
    
// contrutor parametrico 1 - cria uma matriz com nRows  = rows, nCols = cols e 
// com todos os elementos iguais a elem (double)
Matrix::Matrix(int rows, int cols, double elem) {
    this->nRows = rows;
    this->nCols = cols;
    double** a = createMatrix(this->nRows, this->nCols);
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++) {
        for (j = 0; j < this->nCols; j++) {
            a[i][j] = elem;
        }
    }
    this->m = a;
}

// destrutor
Matrix::~Matrix() {
    int i = 0;
    for (i; i < this->nRows; i++) {
        delete[] m[i];
    }
    delete[] m;
}


// obtem o numero de linhas
int Matrix::getRows() const {
    return this->nRows;
}

// obtem o numero de colunas
int Matrix::getCols() const {
    return this->nCols;
}

// retorna uma matriz transposta
Matrix Matrix::transpose() {
    Matrix n(this->nCols, this->nRows);
    double** a = createMatrix(this->nRows, this->nCols);
    int i = 0, j = 0;
    for (i = 0; i < this->nCols; i++ ) {
        for (j = 0; j < this->nRows; j++ ) {
            a[i][j] = this->m[j][i];
        }
    }
    n.m = a;
    return n;
}

// imprime o conteudo da matriz
void Matrix::print() const {
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++ ) {
        for (j = 0; j < this->nCols; j++ ) {
            std::cout << this->m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
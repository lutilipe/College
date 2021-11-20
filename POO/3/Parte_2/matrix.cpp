// matrix.cpp
#include "matrix.h"
#include <algorithm>
#include <iterator>
#include <fstream>

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
    this->m = createMatrix(this->nRows, this->nCols);
}
    

// contrutor parametrico 1 - cria uma matriz com nRows  = rows, nCols = cols e 
// com todos os elementos iguais a 0.0 (double)
Matrix::Matrix(int rows, int cols, const double &value){
    this->nRows = rows;
    this->nCols = cols;
    double** a = createMatrix(this->nRows, this->nCols);
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++) {
        for (j = 0; j < this->nCols; j++) {
            a[i][j] = value;
        }
    }
    this->m = a;
}

// contrutor parametrico 2 - cria uma matriz com os dados fornecidos pelo arquivo texto myFile.
Matrix::Matrix(std::ifstream &myFile) {
    myFile >> this->nRows >> this->nCols;
    double** a = createMatrix(this->nRows, this->nCols);
    for (int i = 0; i < this->nRows; i++) {
        for (int j = 0; j < this->nCols; j++) {
            myFile >> a[i][j];
        }
    }
    this->m = a;
}


// contrutor de copia
Matrix::Matrix(const Matrix& that){
    nRows = that.getRows();
    nCols = that.getCols();
    double** a = createMatrix(this->nRows, this->nCols);
    for (int i = 0; i < this->nRows; i++) {
        for (int j = 0; j < this->nCols; j++) {
            a[i][j] = that.m[i][j];
        }
    }
    m = a;
}


// destrutor
Matrix::~Matrix() {
    int i = 0;
    for (i = 0; i < this->nRows; i++) {
        delete[] m[i];
    }
    delete[] m;
}


// obtem o numero de linhas
inline int Matrix::getRows() const { return nRows; }

// obtem o numero de colunas
inline int Matrix::getCols() const { return nCols; }


// obtem um elemento específico na posição (row,col). Obs: deve checar consistencia
double Matrix::get(int row, int col) const {
    int parsedRow = std::max(row - 1, 0);
    int parsedCol = std::max(col - 1, 0);
    if (parsedRow > nRows || parsedCol > nCols) {
        return 0;
    }
    return m[parsedRow][parsedCol]; 
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

// faz com que a matriz torne-se uma matriz identidade
void Matrix::unit(){
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++ ) {
        for (j = 0; j < this->nCols; j++ ) {
            if (i != j) {
                this->m[i][j] = 0;
            } else {
                this->m[i][j] = 1;
            }
        }
    }
}

// faz com que a matriz torne-se uma matriz nula
void Matrix::zeros(){
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++ ) {
        for (j = 0; j < this->nCols; j++ ) {
            this->m[i][j] = 0;
        }
    }
}

// faz com que a matriz torne-se uma matriz cujos elementos sao iguaia a 1
void Matrix::ones(){
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++ ) {
        for (j = 0; j < this->nCols; j++ ) {
            this->m[i][j] = 1;
        }
    }
}


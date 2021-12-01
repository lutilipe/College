// matrix.cpp
#include "matrix.h"
#include <algorithm>
#include <iterator>
#include <fstream>
#include <cstring>

void Matrix::init( unsigned int r, unsigned int c, double ** m) {
    this->m = new double*[r];
    for(unsigned int i = 0; i < r; ++i) {
        this->m[i] = new double[c];
        if(!m)
            std::memset(this->m[i], 0, sizeof(double) * c);
        else
            std::memcpy(this->m[i], m[i], sizeof(double) * c);
    }
    this->nRows = r;
    this->nCols = c;
}

// contrutor default - cria uma matriz vazia com nRows = nCols = 0  
Matrix::Matrix(){
    init(0, 0);
}
    

// contrutor parametrico 1 - cria uma matriz com nRows  = rows, nCols = cols e 
// com todos os elementos iguais a 0.0 (double)
Matrix::Matrix(int rows, int cols, const double &value){
    init(rows, cols);
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++) {
        for (j = 0; j < this->nCols; j++) {
            this->m[i][j] = value;
        }
    }
}

// contrutor parametrico 2 - cria uma matriz com os dados fornecidos pelo arquivo texto myFile.
Matrix::Matrix(std::ifstream &myFile) {
    int r, c;
    myFile >> r >> c;
    init(r, c);
    for (int i = 0; i < this->nRows; i++) {
        for (int j = 0; j < this->nCols; j++) {
            myFile >> this->m[i][j];
        }
    }
}


// contrutor de copia
Matrix::Matrix(const Matrix& that){
    this->init(that.nRows, that.nCols, that.m);
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

inline double** Matrix::getMatrix() const { return m; }


// obtem um elemento específico na posição (row,col). Obs: deve checar consistencia
double Matrix::get(int row, int col) const {
    int parsedRow = std::max(row - 1, 0);
    int parsedCol = std::max(col - 1, 0);
    if (parsedRow > nRows || parsedCol > nCols) {
        exit(1);
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

Matrix& Matrix::operator=(const Matrix &ref) {
    int r = std::min(ref.getRows(), nRows);
    int c = std::min(ref.getCols(), nCols);
    for (unsigned int i = 0; i < r; ++i)
        std::memcpy(this->m[i], ref.m[i], sizeof(double) * c);
    return *this;
}

const Matrix Matrix::operator+ (const Matrix& n) const {
    Matrix S(*this);
    S += n;
    return S;
}

Matrix& Matrix::operator+= (const Matrix& n) {
    int r = std::min(n.getRows(), nRows);
    int c = std::min(n.getCols(), nCols);
    for (unsigned i = 0; i < r; i++ ) {
        for (unsigned j = 0; j < c; j++ ) {
            this->m[i][j] = n.m[i][j] + m[i][j];
        }
    }
    return *this;
}

const Matrix Matrix::operator- (const Matrix& n) const {
    Matrix S(*this);
    S -= n;
    return S;
}

Matrix& Matrix::operator-= (const Matrix& n) {
    int r = std::min(n.getRows(), nRows);
    int c = std::min(n.getCols(), nCols);
    for (unsigned i = 0; i < r; i++ ) {
        for (unsigned j = 0; j < c; j++ ) {
            m[i][j] = m[i][j] - n.m[i][j];
        }
    }
    return *this;
}

const Matrix Matrix::operator* (const Matrix& n) const {
    Matrix S(*this);
    S *= n;
    return S;
}

Matrix& Matrix::operator*= (const Matrix& n) {
    int r = std::min(n.getRows(), nRows);
    int c = std::min(n.getCols(), nCols);
    for (unsigned i = 0; i < r; i++ ) {
        for (unsigned j = 0; j < c; j++ ) {
            m[i][j] = m[i][j] * n.m[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*= (const float n) {
    for (unsigned i = 0; i < nRows; i++ ) {
        for (unsigned j = 0; j < nCols; j++ ) {
            m[i][j] = m[i][j] * n;
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream &out, const Matrix &ref) {
    for(unsigned int i = 0; i < ref.getRows(); i++) {
        for(unsigned int j = 0; j < ref.getCols(); j++)
            out << ref.getMatrix()[i][j] << " ";
        out << std::endl;
    }
    return out;
}

std::istream& operator>>( std::istream &in, Matrix &ref ){
    for(unsigned int i = 0; i < ref.getRows(); i++)
        for(unsigned int j = 0; j < ref.getCols(); j++) {
            in >> ref.getMatrix()[i][j];
        }
    return in;
}

bool Matrix::operator== (const Matrix& n) {
    if (nRows != n.getRows() || nCols != n.getCols()) {
        return false;
    }
    for(unsigned int i = 0; i < n.getRows(); i++)
        for(unsigned int j = 0; j < n.getCols(); j++) {
            if (m[i][j] != n.getMatrix()[i][j]) {
                return false;
            }
        }
    return true;
}

bool Matrix::operator!= (const Matrix& n) {
    if (nRows != n.getRows() || nCols != n.getCols()) {
        return true;
    }
    for(unsigned int i = 0; i < n.getRows(); i++)
        for(unsigned int j = 0; j < n.getCols(); j++) {
            if (m[i][j] != n.getMatrix()[i][j]) {
                return true;
            }
        }
    return false;
}

double& Matrix::operator()(int i, int j) {
    int parsedRow = std::max(i - 1, 0);
    int parsedCol = std::max(j - 1, 0);
    if (parsedRow > nRows || parsedCol > nCols) {
        exit(1);
    }
    return m[parsedRow][parsedCol]; 
}

Matrix Matrix::operator~ () const {
    Matrix n(this->nCols, this->nRows);
    int i = 0, j = 0;
    for (i = 0; i < this->nCols; i++ ) {
        for (j = 0; j < this->nRows; j++ ) {
            n.m[i][j] = this->m[i][j];
        }
    }
    return n;
}
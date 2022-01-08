// matrix.cpp
#include "matrix.h"
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <fstream>
#include <cstring>

template<class T> 
void Matrix<T>::init( unsigned int r, unsigned int c, T ** m) {
    this->m = new T*[r];
    for(unsigned int i = 0; i < r; ++i) {
        this->m[i] = new T[c];
        if(!m)
            std::memset(this->m[i], 0, sizeof(T) * c);
        else
            std::memcpy(this->m[i], m[i], sizeof(T) * c);
    }
    this->nRows = r;
    this->nCols = c;
}

// contrutor default - cria uma matriz vazia com nRows = nCols = 0  
template<class T> 
Matrix<T>::Matrix(){
    init(0, 0);
}
    

// contrutor parametrico 1 - cria uma matriz com nRows  = rows, nCols = cols e 
// com todos os elementos iguais a 0.0 (T)
template<class T> 
Matrix<T>::Matrix(int rows, int cols, const T &value){
    init(rows, cols);
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++) {
        for (j = 0; j < this->nCols; j++) {
            this->m[i][j] = value;
        }
    }
}

// contrutor parametrico 2 - cria uma matriz com os dados fornecidos pelo arquivo texto myFile.
template<class T> 
Matrix<T>::Matrix(std::ifstream &myFile) {
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
template<class T> 
Matrix<T>::Matrix(const Matrix& that){
    this->init(that.nRows, that.nCols, that.m);
}


// destrutor
template<class T> 
Matrix<T>::~Matrix() {
    int i = 0; 
    for (i = 0; i < this->nRows; i++) {
        delete[] m[i];
    }
    delete[] m;
}


// obtem o numero de linhas
template<class T> 
inline int Matrix<T>::getRows() const { return nRows; }

// obtem o numero de colunas
template<class T> 
inline int Matrix<T>::getCols() const { return nCols; }

template<class T> 
inline T** Matrix<T>::getMatrix() const { return m; }


// obtem um elemento específico na posição (row,col). Obs: deve checar consistencia
template<class T> 
T Matrix<T>::get(int row, int col) const {
    int parsedRow = std::max(row - 1, 0);
    int parsedCol = std::max(col - 1, 0);
    if (parsedRow > nRows || parsedCol > nCols) {
        throw std::invalid_argument("Index out of bound");
    }
    return m[parsedRow][parsedCol]; 
}

// imprime o conteudo da matriz
template<class T> 
void Matrix<T>::print() const {
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++ ) {
        for (j = 0; j < this->nCols; j++ ) {
            std::cout << this->m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// faz com que a matriz torne-se uma matriz identidade
template<class T> 
void Matrix<T>::unit(){
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
template<class T> 
void Matrix<T>::zeros(){
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++ ) {
        for (j = 0; j < this->nCols; j++ ) {
            this->m[i][j] = 0;
        }
    }
}

// faz com que a matriz torne-se uma matriz cujos elementos sao iguaia a 1
template<class T> 
void Matrix<T>::ones(){
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++ ) {
        for (j = 0; j < this->nCols; j++ ) {
            this->m[i][j] = 1;
        }
    }
}

template<class T> 
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &ref) {
    int r = std::min(ref.getRows(), nRows);
    int c = std::min(ref.getCols(), nCols);
    for (unsigned int i = 0; i < r; ++i)
        std::memcpy(this->m[i], ref.m[i], sizeof(T) * c);
    return *this;
}

template<class T> 
const Matrix<T> Matrix<T>::operator+ (const Matrix<T>& n) const {
    Matrix S(*this);
    S += n;
    return S;
}

template<class T> 
Matrix<T>& Matrix<T>::operator+= (const Matrix<T>& n) {
    int r = std::min(n.getRows(), nRows);
    int c = std::min(n.getCols(), nCols);
    for (unsigned i = 0; i < r; i++ ) {
        for (unsigned j = 0; j < c; j++ ) {
            this->m[i][j] = n.m[i][j] + m[i][j];
        }
    }
    return *this;
}

template<class T> 
const Matrix<T> Matrix<T>::operator- (const Matrix<T>& n) const {
    Matrix S(*this);
    S -= n;
    return S;
}

template<class T> 
Matrix<T>& Matrix<T>::operator-= (const Matrix<T>& n) {
    int r = std::min(n.getRows(), nRows);
    int c = std::min(n.getCols(), nCols);
    for (unsigned i = 0; i < r; i++ ) {
        for (unsigned j = 0; j < c; j++ ) {
            m[i][j] = m[i][j] - n.m[i][j];
        }
    }
    return *this;
}

template<class T> 
const Matrix<T> Matrix<T>::operator* (const Matrix<T>& n) const {
    Matrix S(*this);
    S *= n;
    return S;
}

template<class T> 
Matrix<T>& Matrix<T>::operator*= (const Matrix<T>& n) {
    int r = std::min(n.getRows(), nRows);
    int c = std::min(n.getCols(), nCols);
    for (unsigned i = 0; i < r; i++ ) {
        for (unsigned j = 0; j < c; j++ ) {
            m[i][j] = m[i][j] * n.m[i][j];
        }
    }
    return *this;
}

template<class T> 
Matrix<T>& Matrix<T>::operator*= (const float n) {
    for (unsigned i = 0; i < nRows; i++ ) {
        for (unsigned j = 0; j < nCols; j++ ) {
            m[i][j] = m[i][j] * n;
        }
    }
    return *this;
}

template<class U> 
std::ostream& operator<<(std::ostream &out, const Matrix<U> &ref) {
    for(unsigned int i = 0; i < ref.getRows(); i++) {
        for(unsigned int j = 0; j < ref.getCols(); j++)
            out << ref.getMatrix()[i][j] << " ";
        out << std::endl;
    }
    return out;
}

template<class U> 
std::istream& operator>>( std::istream &in, Matrix<U> &ref ){
    for(unsigned int i = 0; i < ref.getRows(); i++)
        for(unsigned int j = 0; j < ref.getCols(); j++) {
            in >> ref.getMatrix()[i][j];
        }
    return in;
}

template<class T> 
bool Matrix<T>::operator== (const Matrix& n) {
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

template<class T> 
bool Matrix<T>::operator!= (const Matrix& n) {
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

template<class T> 
T& Matrix<T>::operator()(int i, int j) {
    int parsedRow = std::max(i - 1, 0);
    int parsedCol = std::max(j - 1, 0);
    if (parsedRow > nRows || parsedCol > nCols) {
        throw std::invalid_argument("Index out of bound");
    }
    return m[parsedRow][parsedCol]; 
}

template<class T> 
Matrix<T> Matrix<T>::operator~ () const {
    Matrix n(this->nCols, this->nRows);
    int i = 0, j = 0;
    for (i = 0; i < this->nRows; i++ ) {
        for (j = 0; j < this->nCols; j++ ) {
            n.m[j][i] = this->m[i][j];
        }
    }
    return n;
}

template <class T> 
std::ostream& operator<<(std::ostream&, const Matrix<T>&);
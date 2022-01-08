// matrix.h (header file)

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template <class T>
class Matrix {
    private:
        void init(unsigned int nL, unsigned int nC, T** m = 0);

        T** m; // m é um array 2D a ser implementado como um pointer de pointers
        int nRows;  // numero de linhas
        int nCols;  //  numero de colunas

    public:

        // Construtores
        Matrix();                           
        Matrix(int rows, int cols, const T &value = 0.0);
        Matrix(std::ifstream &myFile);
        Matrix(const Matrix<T>& that);
        // destrutor
        ~Matrix();
    
        // basic getters
        int getRows() const;
        int getCols() const;
        T** getMatrix() const;
        T get(int row, int col) const;   
        
        // other methods
        void print() const;
        void unit();
        void zeros();
        void ones();

        // operators
        Matrix<T>& operator=(const Matrix<T> &ref);

        T& operator()(int i, int j);

        const Matrix<T> operator+ (const Matrix<T>& n) const;
        Matrix<T>& operator+= (const Matrix<T>& n);

        const Matrix<T> operator- (const Matrix<T>& n) const;
        Matrix<T>& operator-= (const Matrix<T>& n);

        const Matrix<T> operator* (const Matrix<T>& n) const;
        Matrix<T>& operator*= (const Matrix<T>& n);

        Matrix<T>& operator*= (const float n);

        bool operator== (const Matrix<T>& n);
        bool operator!= (const Matrix<T>& n);

        template<class U>
        friend std::ostream& operator<<(std::ostream &out, const Matrix<U> &ref);

        template<class U>
        friend std::istream& operator>>(std::istream &in, Matrix<U> &obj);

        Matrix<T> operator~ () const;
};

#endif
// matrix.h (header file)

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
    private:
        void init(unsigned int nL, unsigned int nC, double ** m = 0);

        double** m; // m é um array 2D a ser implementado como um pointer de pointers
        int nRows;  // numero de linhas
        int nCols;  //  numero de colunas

    public:

        // Construtores
        Matrix();                           
        Matrix(int rows, int cols, const double &value = 0.0);
        Matrix(std::ifstream &myFile);
        Matrix(const Matrix& that);
        // destrutor
        ~Matrix();
    
        // basic getters
        int getRows() const;
        int getCols() const;
        double** getMatrix() const;
        double get(int row, int col) const;   
        
        // other methods
        void print() const;
        void unit();
        void zeros();
        void ones();

        // operators
        Matrix& operator=(const Matrix &ref);

        double& operator()(int i, int j);

        const Matrix operator+ (const Matrix& n) const;
        Matrix& operator+= (const Matrix& n);

        const Matrix operator- (const Matrix& n) const;
        Matrix& operator-= (const Matrix& n);

        const Matrix operator* (const Matrix& n) const;
        Matrix& operator*= (const Matrix& n);

        Matrix& operator*= (const float n);

        bool operator== (const Matrix& n);
        bool operator!= (const Matrix& n);

        friend std::ostream& operator<<(std::ostream &out, const Matrix &ref);
        friend std::istream& operator>>( std::istream &in, Matrix &obj );

        Matrix operator~ () const;

};

#endif
#include "matrix.h"
#include "matrix.cpp" 
#include <iostream>
#include <fstream>

void assert(const bool expr, const char* msg) {
    if (!expr) {
        std::cout << msg << std::endl;
        exit(1);
    }
}

void testConstructors() {
    std::ifstream in("myMatrix.txt", std::ifstream::in);
    Matrix<double> Y;
    Matrix<double> X(3,1);
    Matrix<double> Z(3,2,7.0);
    Matrix<double> W(X);
    Matrix<double> K(in);
    std::cout << "PASS: testConstructors()" << std::endl;
}

void testGet() {
    std::ifstream in("myMatrix.txt", std::ifstream::in);
    Matrix<double> X(in);
    assert(X.get(1, 3) == 3, "ERROR: testGet() -> Value does not match");
    std::cout << "PASS: testGet()" << std::endl;
}

void testNullMatrix() {
    int n = 3, m = 2;
    Matrix<double> X(n,m, 3);
    X.zeros();
    bool correct = true;
    int i = 0, j = 0;
    for (i = 1; i <= 3; i++ ) {
        for (j = 1; j <= 2; j++ ) {
            if (X.get(i, j) != 0) {
                correct = false;
            }
        }
    }
    assert(correct, "ERROR: testNullMatrix() -> Not all indexes are equal to 0");
    std::cout << "PASS: testNullMatrix()" << std::endl;
}

void testIdentityMatrix() {
    int n = 3, m = 3;
    Matrix<int> X(n, m, 4);
    X.unit();
    bool correct = true;
    int i = 0, j = 0;
    for (i = 1; i <= 3; i++ ) {
        for (j = 1; j <= 2; j++ ) {
            if (i == j) {
                if (X.get(i, j) != 1) {
                    correct = false;
                }
            } else {
                if (X.get(i, j) != 0) {
                    correct = false;
                }
            }
        }
    }
    assert(correct, "ERROR: testIdentityMatrix() -> This is not a identity matrix");
    std::cout << "PASS: testIdentityMatrix()" << std::endl;
}

void testOnesMatrix() {
    int n = 3, m = 2;
    Matrix<int> X(n, m, 3);
    X.ones();
    bool correct = true;
    int i = 0, j = 0;
    for (i = 1; i <= 3; i++ ) {
        for (j = 1; j <= 2; j++ ) {
            if (X.get(i, j) != 1) {
                correct = false;
            }
        }
    }
    assert(correct, "ERROR: testOnesMatrix() -> Not all indexes are equal to 1");
    std::cout << "PASS: testOnesMatrix()" << std::endl;
}

void testOperators() {
    std::ifstream in("myMatrix.txt");
    Matrix<double> Y;
    Matrix<int> X(3,4, 2), A(4,3, 5), C(5,3, 5), D(3, 5);
    Matrix<double> Z(3,2,7.0);
    Matrix<unsigned int> W(in);
    
    A(2, 1) = 10;
    assert(A.get(2, 1) == 10, "ERROR: A(2, 1) == 10 -> Value not equal");
    C = A + A;
    assert(C.get(2, 1) == 20, "ERROR: M + M");
    C -= A;
    assert(C.get(2, 1) == 10, "ERROR: M -= N");
    A += A;
    assert(A.get(2, 1) == 20, "ERROR: M += N");
    D = ~C;
    assert(D.get(1, 2) == 10 && D.get(1, 1) == 5, "ERROR: M ~ N");
    X *= 2;
    assert(X == Matrix<int>(3, 4, 4), "ERROR: M * int");
    C = A * X;
    assert(C(2, 1) == 80, "ERROR: M * N");
    C *= X;
    assert(C(2, 1) == 320, "ERROR: M * int");
    A = C - A;
    assert(A(2, 1) == 300, "ERROR: M - N");
    std::cout << "PASS: testOperators()" << std::endl;
}

void testThrowError() {
    Matrix<double> Z(3,2,7.0);
    try {
        Z(50, 50) = 2;
        assert(false, "ERROR: index out of bound -> Z(50, 50)");
    } catch (std::invalid_argument &e) {
        std::cout << "PASS: throwInvalidArgument -> Z(50, 50)" << std::endl;
    }

    try {
        Z.get(50, 50);
        assert(false, "ERROR: index out of bound -> Z.get(50, 50)");
    } catch (std::invalid_argument &e) {
        std::cout << "PASS: throwInvalidArgument -> Z.get(50, 50)" << std::endl;
    }
}

int main() {
    try {
        testConstructors();
        testGet();
        testNullMatrix();
        testIdentityMatrix();
        testOnesMatrix();
        testOperators();
        testThrowError();
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown error" << std::endl;
    }

    return 0;
}


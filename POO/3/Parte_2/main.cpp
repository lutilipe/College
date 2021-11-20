#include "matrix.h"
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
    Matrix Y;
    Matrix X(3,1);
    Matrix Z(3,2,7.0);
    Matrix W(X);
    Matrix K(in);
    std::cout << "PASS: testConstructors()" << std::endl;
}

void testGet() {
    std::ifstream in("myMatrix.txt", std::ifstream::in);
    Matrix X(in);
    assert(X.get(1, 3) == 3, "ERROR: testGet() -> Value does not match");
    assert(X.get(10, 10) == 0, "ERROR: testGet() -> Invalid value");
    std::cout << "PASS: testGet()" << std::endl;
}

void testNullMatrix() {
    int n = 3, m = 2;
    Matrix X(n,m, 3);
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
    Matrix X(n, m, 4);
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
    Matrix X(n,m, 3);
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

int main() {
    testConstructors();
    testGet();
    testNullMatrix();
    testIdentityMatrix();
    testOnesMatrix();
    
    return 0;
}


#include "matrix.h"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream in("myMatrix.txt");
    Matrix Y;
    Matrix X(3,1), A(4,3, 5), C(5,3, 5);
    Matrix Z(3,2,7.0);
    Matrix W(in);
    
    // operadores a serem implementados em sua classe:
    
    A(25, 55) = 10;
    A.print();
    C = A + A;
    C -= A;      
    A = C - A;
    A += A;
    A = ~C;
    X *= 2;
    C = A*X;
    C *= X;
    if(A == C) std::cout << "true" << std::endl;
    if(X != Y) std::cout << "true" << std::endl;
    std::cout << Z << std::endl;
    std::cin >> W;
  
    return 0;
}


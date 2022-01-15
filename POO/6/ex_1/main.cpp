#include <iostream>

#include "Ponto_2D.h"
#include "Ponto_3D.h"

int main() {
    Ponto2D p1(3,4), p2;
    p2.set(2,1.5);
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;

    p2 = p1;
    std::cout << p2 << std::endl;

    Ponto3D p3(2,4.5,5), p4;
    p4.set(1,0.3,12);
    std::cout << p3 << std::endl;
    std::cout << p4 << std::endl;

    p4 = p3;
    std::cout << p4 << std::endl;

    p4 = p1;
    std::cout << p4 << std::endl;

    return 0;
}

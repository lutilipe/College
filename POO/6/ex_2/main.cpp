#include <iostream>

#include "../ex_1/Ponto_3D.h"
#include "Box.h"

void assert(const bool expr, const char* msg) {
    if (!expr) {
        std::cout << msg << std::endl;
        exit(1);
    }
}

void testBox() {
    Box b1(2, 3, 4);
    Box b2(Ponto3D(2, 3, 4), Ponto3D(4, 5, 6));

    assert(b1.getVolume() == 24, "ERROR: it should calculate box volume");
    assert(b1.getArea() == 52, "ERROR: it should calculate box area");

    assert(b2.getHeight() == 2, "ERROR: it should set correct height from vertices coordinates");
    assert(b2.getWidth() == 2, "ERROR: it should set correct width from vertices coordinates");
    assert(b2.getDepth() == 2, "ERROR: it should set correct depth from vertices coordinates");
}

int main() {
    testBox();

    return 0;
}

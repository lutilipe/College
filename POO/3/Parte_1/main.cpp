#include <iostream>
#include <time.h>
#include <algorithm>

#include "ponto2d.h"

void assert(const bool expr, const char* msg) {
  if (!expr) {
    std::cout << msg << std::endl;
    exit(1);
  }
}

void testCopyConstructor() {
    Ponto2D p1(2, 2);
    Ponto2D p2 = p1;
    Ponto2D p3(p1);
    assert(
        p1.getX() == p2.getX() && p1.getY() == p2.getY() &&
        p2.getX() == p3.getX() && p2.getY() == p3.getY(),
        "ERROR: testCopyConstructor() -> Coordinates does not match");
    std::cout << "PASS: testCopyConstructor" << std::endl;
}

int main() {
    srand(time(NULL));

    testCopyConstructor();

    return 0;
}
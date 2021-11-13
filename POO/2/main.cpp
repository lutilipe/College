#include <iostream>
#include <algorithm>

#include "ponto2d.h"

void assert(const bool expr, const char* msg) {
  if (!expr) {
    std::cout << msg << std::endl;
    exit(1);
  }
}

void testSumOf() {
    double x = 4, y = 3;
    Ponto2D p1(2, 2);
    Ponto2D p2(2, 1);
    p1.sumOf(p2);
    assert(p1.getX() == x && p1.getY() == y, "ERROR: testSumOf() -> Different sum");
    std::cout << "PASS: testSumOf()" << std::endl;
}

void testDistToOrig() {
    double distance = 5;
    Ponto2D p1(4, 3);
    assert(p1.distToOrig() == distance, "ERROR: testDistToOrig() -> Different distance");
    std::cout << "PASS: testDistToOrig()" << std::endl;
}

void testDistTo() {
    double distance = 5;
    Ponto2D p1(2, 2);
    Ponto2D p2(6, 5);
    assert(p1.distTo(p2) == distance, "ERROR: testDistTo() -> Different distance");
    std::cout << "PASS: testDistTo()" << std::endl;
}

void testGetSumOf() {
    double x = 4, y = 3;
    Ponto2D p1(2, 2);
    Ponto2D p2(2, 1);
    Ponto2D p3 = p1.getSumOf(p2);
    assert(p3.getX() == x && p3.getY() == y, "ERROR: testGetSumOf() -> Different sum");
    std::cout << "PASS: testGetSumOf()" << std::endl;
}

void testGetNextId() {
    Ponto2D p1;
    auto it = std::find(Ponto2D::ids.begin(), Ponto2D::ids.end(), p1.getId());
    assert(
        p1.getId() > 0 && p1.getId() < 1000 && it != Ponto2D::ids.end(), 
        "ERROR: getNextId() -> Invalid id"
    );
    std::cout << "PASS: getNextId()" << std::endl;
}

void testDestructor() {
    Ponto2D *p1 = new Ponto2D();
    delete p1;
    auto it = std::find(Ponto2D::ids.begin(), Ponto2D::ids.end(), p1->getId());
    assert(it == Ponto2D::ids.end(), "ERROR: ~Ponto2D() -> ID still exists!");
    std::cout << "PASS: ~Ponto2D()" << std::endl;
}

int main() {
    testSumOf();
    testGetSumOf();
    testDistToOrig();
    testDistTo();
    testGetNextId();
    testDestructor();
    return 0;
}
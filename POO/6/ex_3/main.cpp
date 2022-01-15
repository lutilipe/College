#include <iostream>
#include <string>

#include "BusinessTraveler.h"

void assert(const bool expr, const char* msg) {
    if (!expr) {
        std::cout << msg << std::endl;
        exit(1);
    }
}

void testBusinessTraveler() {
    std::string expect = "fake-string";

    BusinessTraveler b1;
    BusinessTraveler b2(expect);
    BusinessTraveler b3(b2);
    BusinessTraveler b4 = b2;

    assert(b1.getST() == "1", "ERROR: it should set ST as 1");
    assert(b1.getP().getSP() == "1", "ERROR: it should set SP as 1");

    assert(b2.getST() == expect, "ERROR: it should set ST as given string param");
    assert(b2.getP().getSP() == expect, "ERROR: it should set SP as given string param");

    assert(b3.getST() == expect, "ERROR: it should set ST as given BusinessTraveler param");
    assert(b3.getP().getSP() == expect, "ERROR: it should set SP as given BusinessTraveler param");

    assert(b4.getST() == expect, "ERROR: it should set ST as equal BusinessTraveler");
    assert(b4.getP().getSP() == expect, "ERROR: it should set SP as equal BusinessTraveler");
}

int main() {
    testBusinessTraveler();

    return 0;
}

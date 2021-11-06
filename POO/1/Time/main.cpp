#include <iostream>
#include "time.h"

int main() {
    Time t4(45, 30, 56, 5);
    Time t3;
    
    t4.print();
    t4.decrement();
    t4.decrement();
    t4.print();
    t4.increment();
    t4.print();

    t3.read();
    t3.print();

    t4 = t4 + t3;

    t4.print();

    return 0;
}
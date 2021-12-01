#include<iostream> 
#include "ponto2d.h"

int main() {
    Ponto2D a(1,4), b(3,2), c;
    c = a + b;       
    --c;
}


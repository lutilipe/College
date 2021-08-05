#include <iostream>

#include "Ponto.hpp"
#include "Circulo.hpp"
#include "Cilindro.hpp"

using namespace std;

int main() {
    std::cout << "PDS2 - Makefile" << std::endl;

    Ponto ponto(72, 115);
    cout << "Ponto: " << ponto << endl;

    Circulo circulo(2.5, 37, 43);
    cout << "Circulo: " << circulo << endl;

    Cilindro cilindro(10, 4.25, 2, 2);
    cout << "Cilindro: " << cilindro << endl;
    
    return 0;
}
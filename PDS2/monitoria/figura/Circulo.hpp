#include <iostream>
#include "Ponto.hpp"
#include "Figura.hpp"

#ifndef CIRCULO_H
#define CIRCULO_H

using namespace std;

class Circulo : public Figura {
private:
    double _x;
    double _y;
    double _r;

public:
    Circulo(double x, double y, double raio) : _x(x), _y(y), _r(raio) {}
    ~Circulo() {
        std::cout << "Destrutor Circulo" << std::endl;
    };
    bool contem(Ponto p) const;
};

#endif

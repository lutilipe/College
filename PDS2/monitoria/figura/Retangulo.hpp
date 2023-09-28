#ifndef RETANGULO_H
#define RETANGULO_H

#include <iostream>
#include "Ponto.hpp"
#include "Figura.hpp"

using namespace std;

class Retangulo : public Figura {
private:
    double _x;
    double _y;
    double _largura;
    double _altura;

public:
    Retangulo(double x, double y, double largura, double altura)
        : _x(x), _y(y), _largura(largura), _altura(altura) {}

    ~Retangulo() {
        std::cout << "Destrutor Retangulo" << std::endl;
    }

    bool contem(Ponto p) const;
};

#endif
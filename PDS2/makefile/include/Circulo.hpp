#ifndef CIRCULO_HPP
#define CIRCULO_HPP

#include <iostream>

#include "Ponto.hpp"

using namespace std;

class Circulo : public Ponto {
    friend ostream &operator<<( ostream &, const Circulo & );
public:
    Circulo(double = 0.0, int = 0, int = 0);
    void setRaio(double);
    double getRaio() const;
    double area() const;
protected:
    double raio;
};

#endif
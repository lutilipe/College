#ifndef CILINDRO_HPP
#define CILINDRO_HPP

#include<iostream>
#include "Circulo.hpp"

using namespace std;

class Cilindro : public Circulo {
    friend ostream &operator<<( ostream &, const Cilindro &);
public:
    Cilindro(double=0.0, double=0.0, int=0, int=0);
    void setAltura(double);
    double getAltura() const;
    double area() const;
    double volume() const;
protected:
    double altura;
};

#endif
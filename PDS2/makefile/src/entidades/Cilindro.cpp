#include <iomanip>

#include "Cilindro.hpp"

using namespace std;

Cilindro::Cilindro(double h, double r, int x, int y) : Circulo(r, x, y) {
    setAltura(h);
}

void Cilindro::setAltura(double h) {
    this->altura = (h >=0) ? h : 0.0;
}

double Cilindro::getAltura() const {
    return this->altura;
}

double Cilindro::area() const {
    return  2 * Circulo::area() +
            2 * 3.14159 * this->raio * this->altura;
}

double Cilindro::volume() const {
    return Circulo::area() * this->altura;
}

ostream &operator<<(ostream &out, const Cilindro &c) {
    out << static_cast<Circulo>(c) << ";Altura=" << c.altura
        << ";Volume=" << c.volume();
    return out;
}
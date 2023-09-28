#include "Circulo.hpp"
#include "Ponto.hpp"
#include "math.h"

bool Circulo::contem(Ponto p) const {
    return (p.getX() - _x)*(p.getX() - _x) + (p.getY() - _y)*(p.getY() - _y) <= _r*_r;
}

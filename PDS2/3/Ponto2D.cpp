#include "Ponto2D.hpp"
#include <cmath>

Ponto2D::Ponto2D(double x, double y) {
    _x = x;
    _y = y;
}

Ponto2D::Ponto2D() {
    _x = 1;
    _y = 1;
}

double Ponto2D::calcular_distancia(Ponto2D *ponto) {
    double distX = fabs(this->_x - ponto->_x);
    double distY = fabs(this->_y - ponto->_y);
    return sqrt(distX*distX+distY*distY);
}
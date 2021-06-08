#include "Triangulo.hpp"
#include <cmath>

Triangulo::Triangulo(Ponto2D p1, Ponto2D p2, Ponto2D p3) {
    _p1 = p1;
    _p2 = p2;
    _p3 = p3;
}

double Triangulo::calcular_area() {
    double a = _p1.calcular_distancia(&_p2);
    double b = _p2.calcular_distancia(&_p3);
    double c = _p3.calcular_distancia(&_p1);
    double p = (a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

double Triangulo::calcular_perimetro() {
    double a = _p1.calcular_distancia(&_p2);
    double b = _p2.calcular_distancia(&_p3);
    double c = _p3.calcular_distancia(&_p1);
    return a+b+c;
}

int Triangulo::comparar_area(Triangulo *t) {
    double area = calcular_area();
    if (area < t->calcular_area()) {
        return -1;
    } else if (area > t->calcular_area()) {
        return 1;
    }
    return 0;
}
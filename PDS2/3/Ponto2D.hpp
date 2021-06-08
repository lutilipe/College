#ifndef PONTO_2D_H
#define PONTO_2D_H

struct Ponto2D {
    double _x, _y;
    Ponto2D();
    Ponto2D(double _x, double _y);
    double calcular_distancia(Ponto2D *ponto);
};

#endif

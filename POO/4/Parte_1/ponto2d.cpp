#include "ponto2d.h"

int Ponto2D::getX() {return x;};
int Ponto2D::getY() {return y;};

Ponto2D Ponto2D::operator+ (const Ponto2D& p) const {
    Ponto2D c;
    c.x = x + p.x;
    c.y = y + p.y;
    return c;
}

Ponto2D& Ponto2D::operator-- () {
    x = x - 1;
    y = y - 1;
    return *this;
}

#include "Ponto.hpp"

Ponto::Ponto(int x, int y) {
    setPonto(x, y);
}

void Ponto::setPonto(int x, int y) {
    this->x = x;
    this->y = y;
}

ostream &operator<<(ostream &out, const Ponto &p) {
    out << '[' << p.x << ',' << p.y << ']';
    return out;
}
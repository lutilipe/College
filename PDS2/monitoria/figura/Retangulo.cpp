#include "Retangulo.hpp"

bool Retangulo::contem(Ponto p) const {
    double xTr = _x + _largura,
               yTr = _y + _altura; 
        return p.getX() >= _x and p.getX() <= xTr and p.getY() >= _y and p.getY() <= yTr;
}

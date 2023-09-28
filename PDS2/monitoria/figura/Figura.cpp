#include "Figura.hpp"

Figura* operator+(Figura& f1, Figura& f2) {
    return new FiguraComposta(&f1, &f2, '+');
}

Figura* operator-(Figura& f1, Figura& f2) {
    return new FiguraComposta(&f1, &f2, '-');
}

bool FiguraComposta::contem(Ponto p) const {
    if (_tipo == '+') {
        return _figura1->contem(p) || _figura2->contem(p);
    } else if (_tipo == '-') {
        return _figura1->contem(p) && !_figura2->contem(p);
    }
    return false;
}
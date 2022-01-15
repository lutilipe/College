#include "Ponto_2D.h"

Ponto2D& Ponto2D::operator= (const Ponto2D &p){
    x = p.x;
    y = p.y;
    return *this;
}

std::ostream& operator<< (std::ostream &op, const Ponto2D &p){
    op << std::endl;
    op << "x = " << p.x << std::endl;
    op << "y = " << p.y << std::endl;
    return op;
}

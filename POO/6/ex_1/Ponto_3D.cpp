#include "Ponto_3D.h"

std::ostream& operator<< (std::ostream &op, const Ponto3D &p){
    op << std::endl;
    op << "x = " << p.get_x() << std::endl;
    op << "y = " << p.get_y() << std::endl;
    op << "z = " << p.z << std::endl;
    return op;
}

Ponto3D& Ponto3D::operator= (const Ponto2D &p) {
    x = p.get_x();
    y = p.get_y();
    return *this;
}

Ponto3D& Ponto3D::operator= (const Ponto3D &p) {
    x = p.get_x();
    y = p.get_y();
    z = p.z;
    return *this;
}
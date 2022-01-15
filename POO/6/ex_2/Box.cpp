#include <cmath>

#include "Box.h"

Box::Box(Ponto3D ur, Ponto3D bl) {
    height = abs(ur.get_z() - bl.get_z());
    width = abs(ur.get_y() - bl.get_y());
    depth = abs(ur.get_x() - bl.get_x());
}

double Box::getArea() const {
    double s = height * depth;
    double f = height * width;
    double u = width * depth;
    return s*2 + f*2 + u*2;
}

double Box::getVolume() const {
    return width * height * depth;
}
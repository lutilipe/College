#include <iostream>

#include "Point.h"

std::ostream & operator << (std::ostream &out, const Point &p) {
    out << "(" << p.x << ", " << p.y << ")" << " ";
    return out;
}

std::istream & operator >> (std::istream &in,  Point &p) {
  in >> p.x >> p.y;
  return in;
}

Point Point::operator + (const Point &p) {
    Point newP;
    newP.x = this->x + p.x;
    newP.y = this->y + p.y;
    return newP;
}

Point& Point::operator += (const Point &p) {
    this->x += p.x;
    this->y += p.y;
    return *this;
}
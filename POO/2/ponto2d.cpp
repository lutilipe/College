#include "ponto2d.h"

#include <cmath>
#include <iostream>
#include <algorithm>

std::vector<unsigned> generateAllAvailableIds() {
    std::vector<unsigned> ids(MAX_IDS_COUNT);
    for (unsigned i = 1; i <= MAX_IDS_COUNT; i++) {
        ids[i] = i;
    }
    return ids;
}

std::vector<unsigned> Ponto2D::ids = generateAllAvailableIds();

unsigned Ponto2D::_getNextId() {
    unsigned i = rand() % ids.size();
    unsigned id = ids[i];
    auto it = std::find(ids.begin(), ids.end(), id);
    if (it != ids.end()) {
        int index = it - ids.begin();
        ids.erase(ids.begin() + index);
    }
    return id;
}

Ponto2D::Ponto2D(double x, double y): _x(x), _y(y), _id(_getNextId()) {};

Ponto2D::~Ponto2D() {
    ids.push_back(_id);
}

inline double Ponto2D::getX() const { return _x; };
inline double Ponto2D::getY() const { return _y; };

unsigned Ponto2D::getId() const { return _id; };

inline void Ponto2D::setX(double x) { _x = x; };
inline void Ponto2D::setY(double y) { _y = y; };

double Ponto2D::distTo(const Ponto2D& p) const {
    double cx = fabs(p.getX() - _x);
    double cy = fabs(p.getY() - _y);
    return sqrt(cx*cx+cy*cy);
}

double Ponto2D::distToOrig() const {
    Ponto2D o;
    return distTo(o);
}

void Ponto2D::sumOf(const Ponto2D& p) {
    _x += p.getX();
    _y += p.getY();
}

Ponto2D Ponto2D::getSumOf(const Ponto2D& p) const {
    Ponto2D p3;
    p3.setX(p.getX() + _x);
    p3.setY(p.getY() + _y);
    return p3;
}

void Ponto2D::print() {
    std::cout << "(" << _x << ", " << _y << ")" << std::endl;
}
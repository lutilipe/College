#include <iostream>
#include <algorithm>
#include "polygon.h"

std::ostream& operator << (std::ostream &out, const Polygon &poly) {
  for (const Point& p: poly.limits) {
    out << " " << p;
  }
  return out;
}

bool operator == (const Polygon &lhs, const Polygon &rhs) {
    auto lhsPoints = (const std::vector<Point>&)lhs;
    auto rhsPoints = (const std::vector<Point>&)rhs;
    bool hasPoint = false;
    if (lhsPoints.size() != rhsPoints.size()) return false;
    for (unsigned i = 0; i < lhsPoints.size(); i++) {
        hasPoint = false;
        for (unsigned j = 0; j < rhsPoints.size(); j++) {
            if (lhsPoints[i].contains(rhsPoints[j])) {
                hasPoint = true;
                break;
            };
        }
        if (!hasPoint) return false;
    }
    return true;
}

bool Point::contains(const Point& p) const {
  return p.x == this->x && p.y == this->y;
}

std::ostream& operator << (std::ostream &out, const Point &p) {
  out << "(" << p.x << ", " << p.y << ")";
  return out;
}

bool RightRectangle::contains(const Point& p) const {
    if (p.x >= limits[0].x && p.x <= limits[1].x && p.y >= limits[0].y && p.y <= limits[1].y)
        return true;
 
    return false;
}

Point::Point(int xx = 0, int yy = 0): x(xx), y(yy) {
    limits.push_back(*this);
}

bool includes(std::vector<Point> v, Point p) {
    for (const auto &pv : v) {
        if (pv == p) {
            return true;
        }
    }
    return false;
}

RightRectangle::RightRectangle(int x0, int y0, int x1, int y1) {
    int width = std::abs(x0-x1);
    int heigth = std::abs(y0-y1);
    Point p1 = x0 > x1 ? Point(x1, y1 ) : Point(x0 , y0);
    Point p2 = x0 > x1 ? Point(x0, y0 ) : Point(x1 , y1);
    int o1 = p1.y > p2.y ? p1.y - heigth : p1.y + heigth;
    int o2 = p2.y > p1.y ? p2.y - heigth : p2.y + heigth;
    Point p3(p2.x, o2);
    Point p4(p1.x, o1);
    if (!includes(this->limits, p1)) {
        this->limits.push_back(p1);
    }
    if (!includes(this->limits, p2)) {
        this->limits.push_back(p2);
    }
    if (!includes(this->limits, p3)) {
        this->limits.push_back(p3);
    }
    if (!includes(this->limits, p4)) {
        this->limits.push_back(p4);
    }
}
#ifndef POINT_H
#define POINT_H

class Point {
  public:
    Point(double xx = 0, double yy = 0): x(xx), y(yy) {}
    double getX() const { return x; }
    double getY() const { return y; }
    friend std::ostream & operator << (std::ostream &out, const Point &c);
    friend std::istream & operator >> (std::istream &in,  Point &c);
    Point operator + (const Point &p);
    Point& operator += (const Point &p);
  private:
    double x;
    double y;
};

#endif
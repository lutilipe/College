#ifndef BOX_H
#define BOX_H

#include "../ex_1/Ponto_3D.h"

class Box {
    public:
        Box(double h = 0.0, double w = 0.0, double d = 0.0);
        Box(Ponto3D ur, Ponto3D bl);

        double getHeight() const;
        double getWidth() const;
        double getDepth() const;

        void setHeight(double h);
        void setWidth(double w);
        void setDepth(double d);

        double getArea() const;
        double getVolume() const;

    private:
        double height;
        double width;
        double depth;
};

inline Box::Box(double h, double w, double d): height(h), width(w), depth(d) {};

inline double Box::getWidth() const { return width; };
inline double Box::getHeight() const { return height; };
inline double Box::getDepth() const { return depth; };

inline void Box::setHeight(double h) { height = h; };
inline void Box::setWidth(double w) { width = w; };
inline void Box::setDepth(double d) { depth = d; };

#endif
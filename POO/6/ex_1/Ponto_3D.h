#ifndef PONTO_3D_H
#define PONTO_3D_H

#include <iostream>

#include "Ponto_2D.h"

class Ponto3D: public Ponto2D {
    public:
        Ponto3D(double xx = 0, double yy = 0, double zz=0);
        ~Ponto3D();
        friend std::ostream& operator<< (std::ostream &op, const Ponto3D &p);
        void set(double nx = 0, double ny = 0, double nz=0);
        double get_z();
        Ponto3D& operator= (const Ponto2D &p);
        Ponto3D& operator= (const Ponto3D &p);
            
    private:
        double z;
};

inline Ponto3D::Ponto3D(double xx, double yy, double zz): Ponto2D(xx, yy), z(zz) {};
inline Ponto3D::~Ponto3D() {};
inline double Ponto3D::get_z() { return z; };
inline void Ponto3D::set(double nx, double ny, double nz) { x = nx; y = ny; z = nz; };

#endif
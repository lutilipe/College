#ifndef PONTO_2D_H
#define PONTO_2D_H

#include<iostream> 

class Ponto2D{
     public:
        Ponto2D(int xx = 0.0, int yy = 0.0);
        ~Ponto2D();
        friend std::ostream& operator<< (std::ostream &op, const Ponto2D &p);
        Ponto2D& operator= (const Ponto2D &p);
        double get_x() const;
        double get_y() const;
        void set (double nx, double ny);
    
    protected:                
        double x;
        double y;
};

inline Ponto2D::~Ponto2D() {};
inline Ponto2D::Ponto2D(int xx, int yy): x(xx), y(yy) {};
inline double Ponto2D::get_x() const { return x; };
inline double Ponto2D::get_y() const { return y; };
inline void Ponto2D::set(double nx, double ny) { x=nx; y=ny; };

#endif
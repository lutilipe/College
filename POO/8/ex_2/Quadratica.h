#ifndef QUADRATICA_H
#define QUADRATICA_H

#include "Funcao.h"

class Quadratica : public Funcao {
    public:
        Quadratica(double aa, double bb, double cc): a(aa), b(bb), c(cc) {};
        double func(double x);
        virtual ~Quadratica() {};
    private:
        double a;
        double b;
        double c;
};

double Quadratica::func(double x) {
    return a*x*x + b*x + c;
}

#endif
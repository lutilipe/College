#ifndef SENOIDE_H
#define SENOIDE_H

#include "Funcao.h"
#include <cmath>

class Senoide : public Funcao {
    public:
        Senoide(double aa = 1): a(aa) {};
        double func(double x);
        virtual ~Senoide() {};
    private:
        double a;
};

double Senoide::func(double x) {
    return a*sin(x) / x;
}

#endif
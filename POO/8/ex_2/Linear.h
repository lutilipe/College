#ifndef LINEAR_H
#define LINEAR_H

#include "Funcao.h"

class Linear : public Funcao {
    public:
        Linear(double aa, double bb): a(aa), b(bb) {};
        double func(double x);
        virtual ~Linear() {};
    private:
        double a;
        double b;
};

double Linear::func(double x) {
    return a*x + b;
}

#endif
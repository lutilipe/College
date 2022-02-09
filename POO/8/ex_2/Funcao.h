#ifndef FUNCAO_H
#define FUNCAO_H

class Funcao {
    public:
        double getIntegral(double limiteInferior, double limiteSuperior, double intervalos);
        virtual double func(double x) = 0;
        virtual ~Funcao(){}
};

double Funcao::getIntegral(double limiteInferior, double limiteSuperior, double intervalos) {
    float h = (limiteSuperior - limiteInferior) / intervalos;
    float s = func(limiteInferior) + func(limiteSuperior);

    for (int i = 1; i < intervalos; i++) {
        s += 2 * func(limiteInferior + i * h);
    }
 
    return (h / 2) * s;
}

#endif
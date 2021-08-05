#ifndef PONTO_HPP
#define PONTO_HPP

#include <iostream>

using namespace std;

class Ponto {
    friend ostream &operator<<(ostream &, const Ponto &);
public:
    Ponto(int = 0, int = 0);
    void setPonto(int, int);
    int getX() const { return x; };
    int getY() const { return y; };
private:
    int x, y;
};

#endif
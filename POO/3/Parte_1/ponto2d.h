#ifndef PONTO_2D_H
#define PONTO_2D_H

#include <vector>

const unsigned MAX_IDS_COUNT = 999;

class Ponto2D {
    private:        
        unsigned _id;
        unsigned _teste;
        double _x;
        double _y;

        unsigned _getNextId();

    public:
        static std::vector<unsigned> ids;

        Ponto2D(double x = 0, double y = 0);
        Ponto2D(const Ponto2D&);
        ~Ponto2D();

        double getX() const;
        double getY() const;
        unsigned getId() const;

        void setX(double x);
        void setY(double y);

        void print();

        double distToOrig() const;
        double distTo(const Ponto2D& p) const;

        void sumOf(const Ponto2D& p);
        Ponto2D getSumOf(const Ponto2D& p) const;
};

#endif
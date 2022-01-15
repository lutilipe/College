#ifndef TRAVELER_H
#define TRAVELER_H

#include <string>

class Traveler {
    public:
        Traveler(std::string ss);
        Traveler(const Traveler &p);
        Traveler& operator= (const Traveler &p);
        std::string getST();
    
    protected:
        std::string st;
};

inline Traveler::Traveler(std::string ss): st(ss) {};
inline Traveler::Traveler(const Traveler &p) { st = p.st; };

inline std::string Traveler::getST() { return st; };

Traveler& Traveler::operator= (const Traveler &p) { 
    st = p.st;
    return *this;
};

#endif
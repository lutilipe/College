#ifndef BUSINESS_TRAVELER_H
#define BUSINESS_TRAVELER_H

#include "Traveler.h"
#include "Pager.h"

#include <string>

class BusinessTraveler: public Traveler {
    public:
        BusinessTraveler();
        BusinessTraveler(std::string ss);
        BusinessTraveler(const BusinessTraveler &b);
        BusinessTraveler& operator= (const BusinessTraveler &b);
        Pager& getP();
    
    private:
        Pager p;
};

inline BusinessTraveler::BusinessTraveler(): p("1"), Traveler("1") {};
inline BusinessTraveler::BusinessTraveler(std::string ss): p(ss), Traveler(ss) {};
inline BusinessTraveler::BusinessTraveler(const BusinessTraveler &b): Traveler(b.st), p(b.p) {};
inline Pager& BusinessTraveler::getP() { return p; };

BusinessTraveler& BusinessTraveler::operator= (const BusinessTraveler &b) { 
    st = b.st;
    p = b.p;
    return *this;
};

#endif
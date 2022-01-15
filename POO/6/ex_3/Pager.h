#ifndef PAGER_H
#define PAGER_H

#include <string>

class Pager {
    public:
        Pager(std::string ss);
        Pager(const Pager &p);
        Pager& operator= (const Pager &p);

        std::string getSP();
    
    private:
        std::string sp;
};

inline Pager::Pager(std::string ss): sp(ss) {};
inline Pager::Pager(const Pager &p) { sp = p.sp; };

inline std::string Pager::getSP() { return sp; };

Pager& Pager::operator= (const Pager &p) { 
    sp = p.sp;
    return *this;
};

#endif
#ifndef PESSOA_H
#define PESSOA_H

#include <string>

class Pessoa {
    public:
        Pessoa(): name("indefinido"), age(0) {};
        Pessoa(std::string n, unsigned int a): name(n), age(a) {};

        std::string getName();
        unsigned int getAge();
        void setName(std::string n);
        void setAge(unsigned int a);

        virtual std::string getEmail() { return "indefinido"; };
        virtual std::string getBirthday() { return "indefinido"; };

        virtual void setEmail() {};
        virtual void setBirthday() {};
    
    protected:
        std::string name;
        unsigned int age;
};

inline unsigned int Pessoa::getAge() { return age; }
inline std::string Pessoa::getName() { return name; }
inline void Pessoa::setName(std::string n) { name = n; }
inline void Pessoa::setAge(unsigned int a) { age = a; }

#endif
#ifndef EMAIL_H
#define EMAIL_H

#include <iostream>

using namespace std;

class Email {
    private:
        int key;
        string message;
    public:
        Email(): key(-1), message("") {};
        Email(int k, string msg): key(k), message(msg) {};

        int getKey();
        string getMessage();
        bool operator> (Email& e);
        bool operator< (Email& e);
        void operator= (Email& e);
};

#endif

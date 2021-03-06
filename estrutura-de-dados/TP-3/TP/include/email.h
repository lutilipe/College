#ifndef EMAIL_H
#define EMAIL_H

#include <iostream>

using namespace std;

class Email {
    private:
        int key;
        int userId;
        string message;
    public:
        Email(): key(-1), userId(-1), message("") {};
        Email(int k, int uuid, string msg);

        int getKey();
        int getUserId();
        string getMessage();
        bool operator> (Email& e);
        bool operator< (Email& e);
        void operator= (Email& e);
};

#endif

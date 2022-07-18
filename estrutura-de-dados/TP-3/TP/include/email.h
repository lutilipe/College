#ifndef EMAIL_H
#define EMAIL_H

#include <iostream>

using namespace std;

class Email {
    private:
        // Memlog id
        int _id;

        int key;
        int userId;
        string message;
    public:
        Email(): _id(-1), key(-1), userId(-1), message("") {};
        Email(int k, int uuid, string msg);

        int getKey();
        int getUserId();
        int getLogId();
        string getMessage();
        bool operator> (Email& e);
        bool operator< (Email& e);
        void operator= (Email& e);
};

#endif

#ifndef EMAIL_SERVER_H
#define EMAIL_SERVER_H

#include <iostream>
#include "email-box.h"
#include "email.h"

using namespace std;
class EmailServer {
    private:
        int size;
        EmailBox* table;
        int hash(int id);
    public:
        EmailServer(int length);
        ~EmailServer();
        void add(Email e);
        bool remove(int id);
        Email* get(int id);
};

#endif

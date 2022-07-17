#ifndef EMAIL_SERVER_H
#define EMAIL_SERVER_H

#include <iostream>
#include <fstream>
#include "email-box.h"
#include "email.h"

using namespace std;
class EmailServer {
    private:
        // Memlog id
        int _id;

        int size;
        EmailBox* table;
        int hash(int id);

        void handleDeliveryMessage(ifstream* in, ofstream* out);
        void handleSearchMessage(ifstream* in, ofstream* out);
        void handleDeleteMessage(ifstream* in, ofstream* out);
    public:
        EmailServer(int length);
        ~EmailServer();
        int add(Email e);
        bool remove(int userId, int key);
        Email* get(int userId, int key);

        void handleCommands(string command, ifstream* in, ofstream* out);
};

#endif

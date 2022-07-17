#include "email-server.h"
#include "email-box.h"
#include "email.h"
#include <iostream>

EmailServer::EmailServer(int length) {
    EmailServer::size = length;
    EmailServer::table = new EmailBox[length];
}

EmailServer::~EmailServer() {
    delete[] EmailServer::table;
}

int EmailServer::hash(int id) {
    return id % EmailServer::size;
}

void EmailServer::add(Email e) {
    int key = hash(e.getKey());
    EmailServer::table[key].add(e);
}

Email* EmailServer::get(int id) {
    int key = hash(id);
    return EmailServer::table[key].get(id);
}

bool EmailServer::remove(int id) {
    int key = hash(id);
    return EmailServer::table[key].remove(id);
}

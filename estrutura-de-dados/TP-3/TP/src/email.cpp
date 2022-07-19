#include <iostream>
#include "email.h"

using namespace std;

Email::Email(int k, int uuid, string msg) {
    Email::key = k;
    Email::userId = uuid;
    Email::message = msg;
}

int Email::getKey() {
    return Email::key;
}

int Email::getUserId() {
    return Email::userId;
}

string Email::getMessage() {
    return Email::message;
}

bool Email::operator<(Email& e) {
    return Email::getKey() < e.getKey();
}

bool Email::operator>(Email& e) {
    return Email::getKey() > e.getKey();
}

void Email::operator=(Email& e) {
    Email::key = e.getKey();
    Email::userId = e.getUserId();
    Email::message = e.getMessage();
}

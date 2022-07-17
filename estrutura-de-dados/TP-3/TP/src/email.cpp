#include <iostream>
#include "email.h"

using namespace std;

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
    return Email::key < e.getKey();
}

bool Email::operator>(Email& e) {
    return Email::key > e.getKey();
}

void Email::operator=(Email& e) {
    Email::key = e.getKey();
    Email::userId = e.getUserId();
    Email::message = e.getMessage();
}

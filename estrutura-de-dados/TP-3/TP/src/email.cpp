#include <iostream>
#include "email.h"

using namespace std;

int Email::getKey() {
    return Email::key;
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
    Email::message = e.getMessage();
}

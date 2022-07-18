#include <iostream>
#include "email.h"
#include "memlog.h"

using namespace std;

int CURR_ID = 1;

Email::Email(int k, int uuid, string msg) {
    Email::_id = CURR_ID; CURR_ID++;
    Email::key = k;
    Email::userId = uuid;
    Email::message = msg;
}

int Email::getKey() {
    LEMEMLOG((long int)(&(Email::key)),sizeof(Email::key),Email::_id);
    return Email::key;
}

int Email::getUserId() {
    LEMEMLOG((long int)(&(Email::userId)),sizeof(Email::userId),Email::_id);
    return Email::userId;
}

int Email::getLogId() {
    return Email::_id;
}

string Email::getMessage() {
    LEMEMLOG((long int)(&(Email::message)),sizeof(Email::message),Email::_id);
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
    ESCREVEMEMLOG((long int)(&(Email::key)),sizeof(Email::key),Email::_id);
    Email::userId = e.getUserId();
    ESCREVEMEMLOG((long int)(&(Email::userId)),sizeof(Email::userId),Email::_id);
    Email::message = e.getMessage();
    ESCREVEMEMLOG((long int)(&(Email::message)),sizeof(Email::message),Email::_id);
}

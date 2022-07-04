#include "letter.h"
#include "memlog.h"
#include <iostream>

using namespace std;

int Letter::getIndex() {
    LEMEMLOG((long int)(&(Letter::index)),sizeof(Letter::index),Letter::id);
    return Letter::index; 
};

char Letter::getVal() {
    //LEMEMLOG((long int)(&(Letter::val)),sizeof(char),Letter::id);
    return Letter::val; 
};

void Letter::setIndex(int newIdx) {
    //ESCREVEMEMLOG((long int)(&(Letter::index)),sizeof(Letter::index),Letter::id);
    Letter::index = newIdx; 
};

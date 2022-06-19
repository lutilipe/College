#ifndef UTILS_H
#define UTILS_H

#include <iostream>

using namespace std;

char charToLowerCase(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

string stringToLowerCase(string& in) {
    size_t i = 0;
    for (i = 0; i < in.size(); i++) {
        in[i] = charToLowerCase(in[i]);
    }
    return in;
}

#endif
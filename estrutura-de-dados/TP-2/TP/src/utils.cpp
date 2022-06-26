#include <iostream>
#include "utils.h"

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

void removeUnexpectedChars(string* s) {
    char last = (*s)[s->size() - 1];
    if (last == ',' ||
        last == '.' ||
        last == '!' ||
        last == '?' ||
        last == ':' ||
        last == ';' ||
        last == '_'
    ) s->pop_back();
}

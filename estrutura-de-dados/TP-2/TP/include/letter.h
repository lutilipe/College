#ifndef LETTER_H
#define LETTER_H

#include <iostream>

using namespace std;

#define ALPHABET_ID 0

class Letter {
    private:
        char val;
        int index;
        int id;
    public:
        Letter(): val(0), index(-1), id(ALPHABET_ID) {};
        Letter(char c, int idx, int i = ALPHABET_ID): val(c), index(idx), id(i) {};

        int getIndex();
        char getVal();
        void setIndex(int newIdx);
};

#endif
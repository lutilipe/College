#ifndef ALPHABETIC_ORDER_H
#define ALPHABETIC_ORDER_H

#include <iostream>

using namespace std;

// Isso exclui os caracteres maiusculos
#define CHARS_IN_ASCII 255

#define ALPHABET_SIZE 26
#define FIRST_LOWERCASE_CHAR 97

class Letter {
    private:
        char val;
        int index;
    public:
        Letter(): val(0), index(-1) {};
        Letter(char c, int idx): val(c), index(idx) {};

        int getIndex() { return index; };
        char getVal() { return val; };
        void setIndex(int newIdx) { index = newIdx; };
};

class AlphabeticOrder {
    private:
        Letter order[CHARS_IN_ASCII];
        void populate();
    public:
        AlphabeticOrder(string newOrder);
        Letter* getOrder() { return order; };
};

#endif
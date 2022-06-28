#ifndef ALPHABETIC_ORDER_H
#define ALPHABETIC_ORDER_H

#include <iostream>

using namespace std;

// Isso exclui os caracteres maiusculos
#define CHARS_IN_ASCII 255

#define ALPHABET_SIZE 26
#define FIRST_LOWERCASE_CHAR 97

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

class AlphabeticOrder {
    private:
        Letter order[CHARS_IN_ASCII];
        void populate();
    public:
        AlphabeticOrder(string newOrder);
        Letter* getOrder();
};

#endif
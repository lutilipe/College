#ifndef ALPHABETIC_ORDER_H
#define ALPHABETIC_ORDER_H

#include <iostream>
#include "letter.h"

using namespace std;

#define CHARS_IN_ASCII 255

#define ALPHABET_SIZE 26
#define FIRST_LOWERCASE_CHAR 97

class AlphabeticOrder {
    private:
        Letter order[CHARS_IN_ASCII];
        void populate();
    public:
        AlphabeticOrder(string newOrder);
        Letter* getOrder();
};

#endif
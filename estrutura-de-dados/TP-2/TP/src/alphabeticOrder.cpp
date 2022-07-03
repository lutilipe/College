#include "msgassert.h"
#include "alphabeticOrder.h"
#include "letter.h"
#include "utils.h"
#include "memlog.h"
#include <iostream>

using namespace std;

void AlphabeticOrder::populate() {
    int i = 0;
    for (i = 0; i < CHARS_IN_ASCII; i++) {
        char c = (char) i;
        Letter l(c, i);
        AlphabeticOrder::order[i] = l;
        ESCREVEMEMLOG((long int)(&(AlphabeticOrder::order[i])),sizeof(AlphabeticOrder::order[i]),ALPHABET_ID);
    }
}

AlphabeticOrder::AlphabeticOrder(string newOrder) {
    erroAssert(
        newOrder.size() == ALPHABET_SIZE,
        "Invalid order"
    );
    AlphabeticOrder::populate();
    int i = 0;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        int newIdx = i + FIRST_LOWERCASE_CHAR;
        AlphabeticOrder::getOrder()[(int) charToLowerCase(newOrder[i])].setIndex(newIdx);
    }
}

Letter* AlphabeticOrder::getOrder() {
    LEMEMLOG((long int)(&(AlphabeticOrder::order)),sizeof(AlphabeticOrder::order),ALPHABET_ID);
    return AlphabeticOrder::order; 
};

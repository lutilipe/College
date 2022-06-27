#include "msgassert.h"
#include "alphabeticOrder.h"
#include "utils.h"
#include <iostream>

using namespace std;

void AlphabeticOrder::populate() {
    int i = 0;
    for (i = 0; i < CHARS_IN_ASCII; i++) {
        char c = (char) i;
        Letter l(c, i);
        AlphabeticOrder::order[i] = l;
    }
}

AlphabeticOrder::AlphabeticOrder(string newOrder) {
/*     for (int j = 0 ; j < newOrder.size(); j++) {
        cout << newOrder[j] << endl;
    } */
    erroAssert(
        newOrder.size() == ALPHABET_SIZE,
        "Invalid order"
    );
    AlphabeticOrder::populate();
    int i = 0;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        int newIdx = i + FIRST_LOWERCASE_CHAR;
        AlphabeticOrder::order[(int) charToLowerCase(newOrder[i])].setIndex(newIdx);
    }
}

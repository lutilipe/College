#include "hand.h"

#include <iostream>
#include "msgassert.h"
#include "utils.h"

using namespace std;

void Hand::order() {
    erroAssert(cards != NULL, "Hand cards not setted!");
    sort(cards, HAND_SIZE);
}

void Hand::setCards(ifstream* in) {
    string tmp;
    for (int i = 0; i < HAND_SIZE; i++) {
        (*in) >> tmp;
        cards[i] = Card(tmp);
    }

    order();
}

void Hand::print() {
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i != HAND_SIZE - 1) {
            cout << cards[i].getCard() << " ";
        } else {
            cout << cards[i].getCard();
        }
    }
    cout << endl;
}

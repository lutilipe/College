#include "card.h"
#include "player.h"
#include "msgassert.h"
#include "utils.h"

#include <iostream>

using namespace std;

Player::Player(std::string n, float a) {
    name = n;
    amount = a;
}

void Player::organizeHand() {
    erroAssert(!!hand, "Player hand not setted!");
    sort(hand, HAND_SIZE);
}

void Player::setHand() {
    string tmp;
    for (int i = 0; i < HAND_SIZE; i++) {
        cin >> tmp;
        hand[i] = Card(tmp);
    }

    organizeHand();
}

void Player::printHand() {
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i != HAND_SIZE - 1) {
            cout << hand[i].getCard() << " ";
        } else {
            cout << hand[i].getCard();
        }
    }
    cout << endl;
}
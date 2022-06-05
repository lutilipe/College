#include "card.h"
#include "player.h"
#include "msgassert.h"
#include "game.h"

#include <iostream>
#include <fstream>

using namespace std;

Player::Player(std::string n, float a) {
    name = n;
    amount = a;
    hand = new Hand();
}

Player::~Player() {
    delete hand;
}

void Player::setHand(ifstream *in) {
    delete hand;
    Player::hand = new Hand();
    hand->setCards(in);
}

void Player::doAnte(int ante) {
    int tmp = this->amount - ante;
    if (tmp < 0) {
        throw RoundException();
    }
    this->amount = tmp;
}

void Player::doBet() {
    int tmp = this->amount - this->bet;
    if (tmp < 0) {
        throw RoundException();
    }
    this->amount = tmp;
}

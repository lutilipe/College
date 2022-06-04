#include "card.h"
#include "player.h"
#include "msgassert.h"

#include <iostream>
#include <fstream>

using namespace std;

Player::Player(std::string n, float a) {
    name = n;
    amount = a;
    hand = new Hand();
}

Player::Player(const Player& p) {
    name = p.name;
    amount = p.amount;
    hand = new Hand(*p.hand);
}

Player::~Player() {
    delete hand;
}

void Player::setHand(Hand* h) {
    delete hand;
    this->hand = h;
}

void Player::doAnte(int ante) {
    int tmp = this->amount - ante;
    erroAssert(tmp >= 0, "Player can not have negative amount!");
    this->amount = tmp;
}

void Player::doBet() {
    int tmp = this->amount - bet;
    erroAssert(tmp >= 0, "Player can not have negative amount!");
    this->amount = tmp;
}

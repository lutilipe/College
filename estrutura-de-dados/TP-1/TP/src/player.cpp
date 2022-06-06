#include "card.h"
#include "player.h"
#include "msgassert.h"
#include "game.h"

#include <iostream>
#include <fstream>

using namespace std;

Player::Player(std::string n, float a, int i) {
    name = n;
    amount = a;
    id = i;
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
    int tmp = Player::amount - ante;
    if (tmp < 0) {
        throw RoundException();
    }
    Player::amount = tmp;
}

void Player::doBet() {
    int tmp = Player::amount - Player::bet;
    if (tmp < 0) {
        throw RoundException();
    }
    Player::amount = tmp;
}

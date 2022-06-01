#include "card.h"
#include "player.h"
#include "msgassert.h"
#include "utils.h"

#include <iostream>
#include <fstream>

using namespace std;

Player::Player(std::string n, float a) {
    name = n;
    amount = a;
}

void Player::doAnte(int ante) {
    int tmp = amount - ante;
    erroAssert(tmp >= 0, "Player can not have negative amount!");
    amount = tmp;
}

void Player::doBet() {
    int tmp = amount - bet;
    erroAssert(tmp >= 0, "Player can not have negative amount!");
    amount = tmp;
}
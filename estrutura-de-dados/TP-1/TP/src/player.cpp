#include "card.h"
#include "player.h"
#include "memlog.h"
#include "msgassert.h"
#include "game.h"

#include <iostream>
#include <fstream>

using namespace std;

Player::Player(std::string n, float a, int i) {
    name = n;
    amount = a;
    id = i;
    hand = new Hand(id);
}

Player::~Player() {
    delete hand;
}

void Player::setBet(int b) {
    ESCREVEMEMLOG((long int)(&(bet)),sizeof(int),Player::id);
    bet = b; 
};

int Player::getBet() { 
    LEMEMLOG((long int)(&(bet)),sizeof(int),Player::id);
    return bet; 
};

void Player::resetBet() {
    ESCREVEMEMLOG((long int)(&(bet)),sizeof(int),Player::id);
    bet = 0; 
};

string Player::getName() {
    LEMEMLOG((long int)(&(name)),sizeof(string),Player::id);
    return name; 
}

int Player::getAmount() {
    LEMEMLOG((long int)(&(amount)),sizeof(int),Player::id);
    return amount; 
}

void Player::increaseAmount(int n) { 
    ESCREVEMEMLOG((long int)(&(amount)),sizeof(int),Player::id);
    amount += n; 
}

Hand* Player::getHand() { 
    LEMEMLOG((long int)(&(hand)),sizeof(Hand),Player::id);
    return hand; 
}

void Player::setHand(ifstream *in) {
    delete hand;
    Player::hand = new Hand(Player::id);
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

Player* PlayerRef::getRef() {
    if (ref) {
        LEMEMLOG((long int)(&(ref)),sizeof(Player),ref->getId());
    }
    return ref; 
};
void PlayerRef::setRef(Player* r) {
    ref = r;
    if (ref) {
        ESCREVEMEMLOG((long int)(&(ref)),sizeof(Player),ref->getId());
    }
};

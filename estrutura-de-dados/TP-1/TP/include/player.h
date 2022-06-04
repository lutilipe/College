#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "card.h"
#include "hand.h"

using namespace std;

class Player {
    private:
        string name;
        int amount;
        int bet = 0;
        Hand* hand = new Hand();

    public:
        Player() { name = ""; amount = 0; };
        Player(string n, float a);
        Player(const Player& p);
        ~Player();

        Hand* getHand() { return hand; };
        void setHand(Hand* h);

        string getName() { return name; };

        int getAmount() { return amount; };
        void doAnte(int ante);
        void doBet();

        void setBet(int b) { bet = b; };
        int getBet() { return bet; };
};

#endif
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
        friend class PlayerRef;

    public:
        Player() { name = ""; amount = 0; };
        Player(string n, float a);
        ~Player();

        Hand* getHand() { return hand; };
        void setHand(Hand* h);

        string getName() { return name; };

        int getAmount() { return amount; };
        void increaseAmount(int n) { amount += n; };

        void doAnte(int ante);
        void doBet();

        void setBet(int b) { bet = b; };
        int getBet() { return bet; };
};

class PlayerRef {
    private:
        Player* ref;
    public:
        PlayerRef() { ref = NULL; };
        Player* getRef() { return ref; };
        void setRef(Player* r) { ref = r; };
};

#endif
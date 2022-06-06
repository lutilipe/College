#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
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
        int id;

    public:
        Player() { name = ""; amount = 0; id = -1; };
        Player(string n, float a, int id);
        ~Player();

        Hand* getHand() { return hand; };
        void setHand(ifstream *in);

        string getName() { return name; };

        int getAmount() { return amount; };
        void increaseAmount(int n) { amount += n; };

        void doAnte(int ante);
        void doBet();

        void setBet(int b) { bet = b; };
        int getBet() { return bet; };
        void resetBet() { bet = 0; };

        int getId() { return id; };
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
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
        Hand* hand;
        friend class PlayerRef;
        int id = -1;

    public:
        Player() { name = ""; amount = 0; };
        Player(string n, float a, int id);
        ~Player();

        Hand* getHand();
        void setHand(ifstream *in);

        string getName();

        int getAmount();
        void increaseAmount(int n);

        void doAnte(int ante);
        void doBet();

        void setBet(int b);
        int getBet();
        void resetBet();

        int getId() { return id; };
};

class PlayerRef {
    private:
        Player* ref;
    public:
        PlayerRef() { ref = NULL; };
        Player* getRef();
        void setRef(Player* r);
};

#endif
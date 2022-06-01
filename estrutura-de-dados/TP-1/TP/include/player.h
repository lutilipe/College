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
        bool isPlaying = true;
        int bet = 0;
        Hand hand;

    public:
        Player() { name = ""; amount = 0; };
        Player(string n, float a);
        Hand getHand() { return hand; };
        string getName() { return name; };
        bool getIsPlaying() { return isPlaying; };
        void setIsPlaying(bool playing) { isPlaying = playing; };
        int getAmount() { return amount; };
        void doAnte(int ante);
        void doBet();
        void setBet(int b) { bet = b; };
        int getBet() { return bet; };
        void setHand(Hand h) { hand = h; };
};

#endif
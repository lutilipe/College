#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "card.h"

using namespace std;

#ifndef HAND_SIZE 
#define HAND_SIZE 5
#endif

class Player {
    private:
        string name;
        int amount;
        Card hand[HAND_SIZE];
        bool isPlaying = true;
    public:
        Player() { name = ""; amount = 0; };
        Player(string n, float a);
        Card* getHand() { return hand; };
        string getName() { return name; };
        bool getIsPlaying() { return isPlaying; };
        void setIsPlaying(bool playing) { isPlaying = playing; };
        int getAmount() { return amount; };
        int doAnte();
        int doBet();
        void setHand();
        void printHand();
};

#endif
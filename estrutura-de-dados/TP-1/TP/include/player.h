#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class Player {
    private:
        string name;
        float amount;
    public:
        Player(string n, float a);
        ~Player();
        string getName() { return name; };
        float getAmount() { return amount; };
        float doAnt();
        float doBet();
};

#endif
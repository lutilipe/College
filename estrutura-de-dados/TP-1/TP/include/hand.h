#ifndef HAND_RANK_H
#define HAND_RANK_H

#include <iostream>
#include <fstream>
#include "card.h"

using namespace std;

class Hand {
    public:
        enum Type {
            HighCard,
            OnePair,
            TwoPairs,
            ThreeOfAKind,
            Straight,
            Flush,
            FullHouse,
            FourOfAKind,
            StraightFlush,
            RoyalStraightFlush,
        };

        static const int HAND_SIZE = 5;

        Hand() {};

        void setType(Hand::Type t) { type = t; };
        Hand::Type getType() { return type; };
        void setCards(ifstream* in);
        void order();
        void print();

    private:
        Hand::Type type;
        Card cards[HAND_SIZE];

};

#endif
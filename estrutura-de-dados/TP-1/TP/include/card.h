#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

enum Suit {
    OUROS = 'O',
    ESPADAS = 'E',
    COPAS = 'C',
    PAUS = 'P',
};

class Card {
    public:
        Card(string card);
        int getValue() { return value; };
        char getSuit() { return (char) suit; };
    private:
        int value;
        Suit suit;
};

#endif

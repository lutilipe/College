#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

#ifndef SUIT_TYPES_SIZE
#define SUIT_TYPES_SIZE 4
#endif

class Card {
    public:
        enum CardNumber {
            INVALIDNUMBER = 0,
            ACE = 1,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            JACK,
            QUEEN,
            KING,
        };

        enum Suit {
            INVALIDSUIT = 0,
            OUROS = 'O',
            ESPADAS = 'E',
            COPAS = 'C',
            PAUS = 'P',
        };

        Card() { value = INVALIDNUMBER; suit = INVALIDSUIT; };
        Card(string card);
        Card::CardNumber getValue() { return value; };
        Card::Suit getSuit() { return suit; };
        void print();
        string getCard();

        bool operator > (Card c);
    private:
        Card::CardNumber value;
        Card::Suit suit;
};

#endif

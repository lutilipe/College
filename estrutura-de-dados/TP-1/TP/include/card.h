#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

#ifndef SUIT_TYPES_SIZE
#define SUIT_TYPES_SIZE 4
#endif

#ifndef MAX_CARD_VALUE
#define MAX_CARD_VALUE 13
#endif

#ifndef MIN_CARD_VALUE
#define MIN_CARD_VALUE 1
#endif

enum Suit {
    OUROS = 'O',
    ESPADAS = 'E',
    COPAS = 'C',
    PAUS = 'P',
};

class Card {
    public:
        Card() { value = 0; suit = 0; };
        Card(string card);
        int getValue() { return value; };
        char getSuit() { return suit; };
        void print();
        string getCard();

        bool operator > (Card c);
    private:
        int value;
        char suit;
};

#endif

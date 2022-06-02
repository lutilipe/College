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
            InvalidNumber,
            Ace,
            Two,
            Three,
            Four,
            Five,
            Six,
            Seven,
            Eight,
            Nine,
            Ten,
            Jack,
            Queen,
            King,
        };

        enum Suit {
            InvalidSuit = 0,
            Ouros = 'O',
            Espadas = 'E',
            Copas = 'C',
            Paus = 'P',
        };

        Card() { value = Card::CardNumber::InvalidNumber; suit = Card::Suit::InvalidSuit; };
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

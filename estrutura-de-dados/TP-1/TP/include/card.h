#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

#ifndef SUIT_TYPES_SIZE
#define SUIT_TYPES_SIZE 4
#endif

class Card {
    public:
        enum Number {
            InvalidNumber,
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
            Ace,
        };

        enum Suit {
            InvalidSuit = 0,
            Ouros = 'O',
            Espadas = 'E',
            Copas = 'C',
            Paus = 'P',
        };

        Card() { value = Card::Number::InvalidNumber; suit = Card::Suit::InvalidSuit; };
        Card(string card, int id);
        Card::Number getValue();
        Card::Suit getSuit();
        void print();
        string getCard();

        bool operator > (Card c);
    private:
        Card::Number value;
        Card::Suit suit;
        int id = -1;
};

#endif

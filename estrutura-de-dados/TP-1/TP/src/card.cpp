#include "card.h"

#include <iostream>
#include "msgassert.h"

using namespace std;

Card::Card(std::string card) {
    string subHand;
    Card::CardNumber v = Card::CardNumber::InvalidNumber;

    erroAssert((card != "" && card != " "), "Invalid card!");

    Card::suit = (Card::Suit) card[card.size() - 1];
    erroAssert((
        suit == Card::Suit::Ouros ||
        suit == Card::Suit::Paus ||
        suit == Card::Suit::Espadas ||
        suit == Card::Suit::Copas
    ), "Invalid card suit!");

    card.pop_back();
    v = (Card::CardNumber) stoi(card);
    erroAssert((v >= Card::CardNumber::Ace && v <= Card::CardNumber::King), "Invalid card value!");
    Card::value = v;
}

string Card::getCard() {
    string card = "";
    card += to_string(Card::value);
    card += Card::suit;
    return card;
}

bool Card::operator>(Card c) {
    return Card::value > c.getValue();
}

void Card::print() {
    cout << Card::getCard() << endl;
}

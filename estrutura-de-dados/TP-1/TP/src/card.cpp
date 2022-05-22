#include "card.h"

#include <iostream>
#include "msgassert.h"

Card::Card(std::string card) {
    string subHand;
    int v = 0;

    erroAssert((card != "" && card != " "), "Invalid card!");

    this->suit = (Suit) card[card.size() - 1];
    erroAssert((suit == OUROS || suit == PAUS || suit == ESPADAS || suit == COPAS), "Invalid card suit!");

    card.pop_back();
    v = stoi(card);
    erroAssert((v >= 1 && v <= 13), "Invalid card value!");
    this->value = v;
}
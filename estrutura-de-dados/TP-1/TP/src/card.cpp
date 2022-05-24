#include "card.h"

#include <iostream>
#include "msgassert.h"

using namespace std;

Card::Card(std::string card) {
    string subHand;
    int v = 0;

    erroAssert((card != "" && card != " "), "Invalid card!");

    this->suit = card[card.size() - 1];
    erroAssert((suit == OUROS || suit == PAUS || suit == ESPADAS || suit == COPAS), "Invalid card suit!");

    card.pop_back();
    v = stoi(card);
    erroAssert((v >= MIN_CARD_VALUE && v <= MAX_CARD_VALUE), "Invalid card value!");
    this->value = v;
}

string Card::getCard() {
    string card = "";
    card += to_string(this->value);
    card += this->suit;
    return card;
}

void Card::print() {
    cout << getCard() << endl;
}
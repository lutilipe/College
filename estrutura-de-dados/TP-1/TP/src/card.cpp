#include "card.h"

#include <iostream>
#include "msgassert.h"
#include "memlog.h"

using namespace std;

Card::Card(std::string card, int i) {
    id = i;
    
    string subHand;
    Card::CardNumber v = Card::CardNumber::InvalidNumber;

    erroAssert((card != "" && card != " "), "Invalid card!");

    Card::suit = (Card::Suit) card[card.size() - 1];

    card.pop_back();
    v = (Card::CardNumber) stoi(card);
    Card::value = v;
}

Card::CardNumber Card::getValue() {
    LEMEMLOG((long int)(&(value)),sizeof(int),Card::id);
    return value; 
};

Card::Suit Card::getSuit() { 
    LEMEMLOG((long int)(&(suit)),sizeof(string),Card::id);
    return suit; 
};

string Card::getCard() {
    string card = "";
    card += to_string(Card::getValue());
    card += Card::getSuit();
    return card;
}

bool Card::operator>(Card c) {
    return Card::getValue() > c.getValue();
}

void Card::print() {
    cout << Card::getCard() << endl;
}

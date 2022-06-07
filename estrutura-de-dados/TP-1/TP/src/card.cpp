#include "card.h"

#include <iostream>
#include "msgassert.h"
#include "memlog.h"

using namespace std;

Card::Card(std::string card, int i) {
    id = i;
    
    string subHand;
    Card::Number v = Card::Number::InvalidNumber;

    erroAssert((card != "" && card != " "), "Invalid card!");

    Card::suit = (Card::Suit) card[card.size() - 1];

    card.pop_back();
    v = (Card::Number) stoi(card);

    // Ajustar para o As para ser carta mais valiosa
    if (v == 1) {
        v = Card::Number::Ace;
    } else {
        v = (Card::Number) (((int) v) - 1);
    }
    Card::value = v;
}

Card::Number Card::getValue() {
    return value; 
};

Card::Suit Card::getSuit() { 
    //LEMEMLOG((long int)(&(suit)),sizeof(Card::Suit),Card::id);
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

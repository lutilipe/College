#include "player.h"
#include "card.h"

#include <iostream>

using namespace std;

int main() {
    Card c = Card("5O");
    cout << c.getValue() << endl;
    cout << c.getSuit() << endl;
    return 0;
}
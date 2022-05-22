#ifndef DECK_H
#define DECK_H

enum Suits {
    OUROS = 'O',
    ESPADAS = 'E',
    COPAS = 'C',
    P = 'P',
};

enum Combinations {
    RoyalStraightFlush = 'RSF',
    StraightFlush = 'SF',
    FourOfAKind = 'FK',
    FullHouse = 'FH',
    Flush = 'F',
    Straight = 'S',
    ThreeOfAKind = 'TK',
    TwoPairs = 'TP',
    OnePair = 'OP',
    HighCard = 'HC',
};

class Deck {

};

#endif
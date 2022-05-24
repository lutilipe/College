#ifndef GAME_H
#define GAME_H

#include "player.h"

enum Combinations {
    HighCard,
    OnePair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalStraightFlush,
};

static const string CombinationsStr[] = {
    "HC",
    "OP",
    "TP",
    "TK",
    "S",
    "F",
    "FH",
    "FK",
    "SF",
    "RSF",
};

class Game {
    private:
        int numberOfRounds = 0;
        int initialAmount = 0;
        int numberOfPlayersInRound = 0;
        int totalNumberOfPlayers = 0;
        int anteValue = 0;

        Player* players;

        void setRound(bool isFirstRound = false);
    public:
        Game(int nRounds, int iAmount);
        ~Game();
        int getNumberOfRounds() { return numberOfRounds; };
        int getInitialAmount() { return initialAmount; };

        void handleFirstRound();
        void handleRound();
};

#endif
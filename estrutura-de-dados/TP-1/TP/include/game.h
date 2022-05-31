#ifndef GAME_H
#define GAME_H

#include "player.h"

class Game {
    private:
        int numberOfRounds = 0;
        int initialAmount = 0;
        int numberOfPlayersInRound = 0;
        int totalNumberOfPlayers = 0;
        int anteValue = 0;
        bool isRoundValid = true;

        Player* players;

        void setRound(bool isFirstRound = false);
        void initPlayers(Player* players, int numberOfPlayers);
        Player createPlayer();
    public:
        Game(int nRounds, int iAmount);
        ~Game();
        int getNumberOfRounds() { return numberOfRounds; };
        int getInitialAmount() { return initialAmount; };

        void handleFirstRound();
        void handleRound();
};

#endif
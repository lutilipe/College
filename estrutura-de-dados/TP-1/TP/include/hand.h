#ifndef HAND_RANK_H
#define HAND_RANK_H

#include <iostream>
#include <fstream>
#include "card.h"
#include "stack.h"

using namespace std;

class Hand {
    public:
        enum Rank {
            InvalidRank,
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

        enum CardRepetition {
            Single = 1,
            Pair,
            Triple,
            Quad
        };

        enum ComparationResult {
            InvalidResult,
            FirstWin,
            SecondWin,
            Tie,
        }; 

        static const int HAND_SIZE = 5;

        Hand(int id);
        ~Hand();

        void setRank(Hand::Rank r);
        Hand::Rank getRank();
        string getRankName();
        void rankHand();

        void setCards(ifstream* in);
        void sortCards();
        void print();

        Stack<Card::CardNumber>* getSinglesBundle() { return singlesBundle; };
        Stack<Card::CardNumber>* getPairsBundle() { return pairsBundle; };
        Stack<Card::CardNumber>* getTriplesBundle() { return triplesBundle; };
        Stack<Card::CardNumber>* getQuadsBundle() { return quadsBundle; };

        void setSinglesBundle(Stack<Card::CardNumber>* c) { singlesBundle = c; };
        void setPairsBundle(Stack<Card::CardNumber>* c) { pairsBundle = c; };
        void setTriplesBundle(Stack<Card::CardNumber>* c) { triplesBundle = c; };
        void setQuadsBundle(Stack<Card::CardNumber>* c) { quadsBundle = c; };

        bool hasSinglesBundle() { return singlesBundle != NULL && !singlesBundle->empty(); };
        bool hasPairsBundle() { return pairsBundle != NULL && !pairsBundle->empty(); };
        bool hasTriplesBundle() { return triplesBundle != NULL && !triplesBundle->empty(); };
        bool hasQuadsBundle() { return quadsBundle != NULL && !quadsBundle->empty(); };

        Hand::ComparationResult compareWithSameRankHand(Hand* handToCompare);

        bool operator < (Hand* h);
    private:
        int id = -1;
        Hand::Rank rank;
        Card cards[Hand::HAND_SIZE];

        // Utilizados para comparar maos com mesmo rank
        Stack<Card::CardNumber>* singlesBundle;
        Stack<Card::CardNumber>* pairsBundle;
        Stack<Card::CardNumber>* triplesBundle;
        Stack<Card::CardNumber>* quadsBundle;

        bool isRoyalStraighFlush();
        bool isStraighFlush();
        bool isFlush();
        bool isStraight();
        bool isHighAceStraight();
        void adjustHighAceStraightSort();

        int getNumberOfDuplicatesAndBuildBundles();

        Hand::ComparationResult compareHighCards(Hand* firstHand, Hand* secondHand);
        Hand::ComparationResult compareFourOfAKind(Hand* firstHand, Hand* secondHand);
        Hand::ComparationResult compareFullHouse(Hand* firstHand, Hand* secondHand);
        Hand::ComparationResult compareThreeOfAKind(Hand* firstHand, Hand* secondHand);
        Hand::ComparationResult comparePairs(Hand* firstHand, Hand* secondHand);

        Hand::ComparationResult compareRepetitions(
            Hand* firstHand, 
            Hand* secondHand,
            Hand::CardRepetition repetition
        );

        Hand::ComparationResult handleRepetitionsComparation(
            Stack<Card::CardNumber>* firstReps,
            Stack<Card::CardNumber>* secondReps
        );

        const string RankNames[11] = {
            "I",
            "HC",
            "OP",
            "TP",
            "TK",
            "S",
            "F",
            "FH",
            "FK",
            "SF",
            "RSF"
        };
};

#endif
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

        Hand();
        Hand(Hand& h);
        ~Hand();

        void setRank(Hand::Rank r) { rank = r; };
        Hand::Rank getRank() { return rank; };
        string getRankName();
        void rankHand();

        void setCards(ifstream* in);
        void sortCards();
        void print();

        Stack<Card::CardNumber>* getSinglesBundle() { return singlesBundle; };
        Stack<Card::CardNumber>* getPairsBundle() { return pairsBundle; };
        Stack<Card::CardNumber>* getTriplesBundle() { return triplesBundle; };
        Stack<Card::CardNumber>* getQuadsBundle() { return pairsBundle; };

        void setSinglesBundle(Stack<Card::CardNumber>* c) { singlesBundle = c; };
        void setPairsBundle(Stack<Card::CardNumber>* c) { pairsBundle = c; };
        void setTriplesBundle(Stack<Card::CardNumber>* c) { triplesBundle = c; };
        void setQuadsBundle(Stack<Card::CardNumber>* c) { quadsBundle = c; };

        bool hasSinglesBundle() { return pairsBundle != NULL && !singlesBundle->empty(); };
        bool hasPairsBundle() { return quadsBundle != NULL && !pairsBundle->empty(); };
        bool hasTriplesBundle() { return singlesBundle != NULL && !triplesBundle->empty(); };
        bool hasQuadsBundle() { return triplesBundle != NULL && !quadsBundle->empty(); };

        Hand::ComparationResult compareWithSameRankHand(Hand* handToCompare);

        bool operator < (Hand* h);
    private:
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
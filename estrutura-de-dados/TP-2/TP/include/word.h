#ifndef WORD_H
#define WORD_H

#include <iostream>
#include "alphabeticOrder.h"

using namespace std;

class Word {
    private:
        Letter* val;
        int reps;
        size_t size;
    public:
        Word(): val(0), reps(0), size(0) {};
        Word(string v);
        int getReps() { return reps; };
        Letter* getVal() { return val; };
        size_t getSize() { return size; };

        string toString();

        void resetReps() { reps = 0; };
        void increaseReps() { Word::reps++; }

        bool operator>(Word& w);
        bool operator==(Word& w);
        void operator=(Word& w);

        void adaptToNewAlphabeticOrder(AlphabeticOrder& order);
};

#endif
#ifndef WORD_H
#define WORD_H

#include <iostream>
#include "alphabeticOrder.h"
#include "letter.h"

using namespace std;

class Word {
    private:
        Letter* val;
        int reps;
        size_t size;
        int id;
    public:
        Word(): val(0), reps(0), size(0), id(-1) {};
        Word(string v, int i);
        int getReps();
        Letter* getVal();
        size_t getSize();
        int getId();

        string toString();

        void resetReps();
        void increaseReps();

        bool operator>(Word& w);
        bool operator==(Word& w);
        void operator=(Word& w);

        void adaptToNewAlphabeticOrder(AlphabeticOrder& order);
};

#endif
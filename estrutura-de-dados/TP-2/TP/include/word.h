#ifndef WORD_H
#define WORD_H

#include <iostream>

using namespace std;

class Word {
    private:
        string val;
        int reps;
    public:
        Word(string v): val(v), reps(0) {};
        int getReps() { return reps; };
        string getVal() { return val; };

        void increaseRep() { reps++; };
        void resetReps() { reps = 0; };
};

#endif
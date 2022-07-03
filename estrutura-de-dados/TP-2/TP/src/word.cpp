#include <word.h>
#include <memlog.h>
#include <alphabeticOrder.h>

using namespace std;

Word::Word(string s, int idd) {
    Word::size = s.size();
    Word::reps = 1;
    Word::id = idd;

    Word::val = new Letter[Word::getSize()];

    size_t i = 0;
    for (i = 0; i < Word::getSize(); i++) {
        Letter l(s[i], (int) s[i], Word::id);
        Word::val[i] = l;
    }
}

void Word::adaptToNewAlphabeticOrder(AlphabeticOrder& order) {
    size_t i = 0;
    for (i = 0; i < Word::getSize(); i++) {
        int originalIndex = Word::getVal()[i].getIndex();
        Word::getVal()[i].setIndex(order.getOrder()[originalIndex].getIndex());
    }
}

bool Word::operator==(Word& w) {
    size_t i = 0;
    if (Word::getSize() != w.getSize()) {
        return false;
    }
    for (i = 0; i < Word::getSize(); i++) {
        if (Word::getVal()[i].getVal() != w.getVal()[i].getVal()) {
            return false;
        }
    }
    return true;
}

bool Word::operator>(Word& w) {
    size_t i = 0;
    for (i = 0; i < Word::getSize(); i++) {
        if (!(Word::getVal()[i].getIndex() == w.getVal()[i].getIndex())) {
            break;
        }
    }
 
    return Word::getVal()[i].getIndex() - w.getVal()[i].getIndex() > 0;
}

void Word::operator=(Word& w) {
    Word::reps = w.reps;
    Word::val = w.val;
    Word::size = w.size;
    Word::id = w.id;

    ESCREVEMEMLOG((long int)(&(Word::reps)),sizeof(Word::reps),Word::id);
    ESCREVEMEMLOG((long int)(&(Word::val)),sizeof(Word::val),Word::id);
    ESCREVEMEMLOG((long int)(&(Word::size)),sizeof(Word::size),Word::id);
}

string Word::toString() {
    string tmp = "";
    size_t i = 0;
    for (i = 0; i < Word::getSize(); i++) {
        tmp += Word::getVal()[i].getVal();
    }
    return tmp;
}

int Word::getReps() {
    LEMEMLOG((long int)(&(Word::reps)),sizeof(Word::reps),Word::id);
    return Word::reps;
};

Letter* Word::getVal() {
    LEMEMLOG((long int)(&(Word::val)),sizeof(Word::val),Word::id);
    return Word::val;

};
size_t Word::getSize() {
    LEMEMLOG((long int)(&(Word::size)),sizeof(Word::size),Word::id);
    return Word::size;
};
int Word::getId() {
    LEMEMLOG((long int)(&(Word::id)),sizeof(Word::id),Word::id);
    return Word::id;
};

void Word::resetReps() {
    Word::reps = 0;
    ESCREVEMEMLOG((long int)(&(Word::reps)),sizeof(Word::reps),Word::id);
};

void Word::increaseReps() {
    Word::reps++;
    ESCREVEMEMLOG((long int)(&(Word::reps)),sizeof(Word::reps),Word::id);
};

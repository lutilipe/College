#include <word.h>
#include <alphabeticOrder.h>

using namespace std;

Word::Word(string s) {
    Word::size = s.size();
    Word::reps = 1;

    Word::val = new Letter[Word::size];

    size_t i = 0;
    for (i = 0; i < Word::size; i++) {
        Letter l(s[i], (int) s[i]);
        Word::val[i] = l;
    }
}

void Word::adaptToNewAlphabeticOrder(AlphabeticOrder& order) {
    size_t i = 0;
    for (i = 0; i < Word::size; i++) {
        int originalIndex = Word::val[i].getIndex();
        Word::val[i].setIndex(order.getOrder()[originalIndex].getIndex());
    }
}

bool Word::operator==(Word& w) {
    int i = 0;
    while (&(Word::val[i]) != nullptr) {
        if (Word::val[i].getVal() != w.getVal()[i].getVal()) {
            return false;
        }
        i++;
    }
    return true;
}

bool Word::operator>(Word& w) {
    int i = 0;
    while (&(Word::val[i]) != nullptr) {
        if (!(Word::val[i].getIndex() == w.getVal()[i].getIndex())) {
            break;
        }
 
        i++;
    }
 
    return Word::val[i].getIndex() - w.getVal()[i].getIndex() > 0;
}

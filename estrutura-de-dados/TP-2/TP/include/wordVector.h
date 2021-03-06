#ifndef WORD_VECTOR_H
#define WORD_VECTOR_H

#include "msgassert.h"
#include "word.h"
#include "memlog.h"
#include "alphabeticOrder.h"
#include <iostream>
#include <fstream>

using namespace std;

#define CAPACITY_INCREASE_FACTOR 2
#define INITIAL_CAPACITY 10

class TmpWord {
    private:
        Word val;
        int index;
        int id;
    public:
        TmpWord(): val(Word()), index(-1), id(-1) {};
        TmpWord(Word w, int idx, int i): val(w), index(idx), id(i) {};

        Word getVal() { 
            LEMEMLOG((long int)(&(TmpWord::val)),sizeof(TmpWord::val),TmpWord::id);
            return TmpWord::val;
        };

        int getIndex() { 
            LEMEMLOG((long int)(&(TmpWord::index)),sizeof(TmpWord::index),TmpWord::id);
            return TmpWord::index; 
        };
        
        bool operator>(TmpWord& w) {
            return TmpWord::val > w.val;
        }

        void operator=(TmpWord& w) {
            TmpWord::id = w.id;
            TmpWord::val = w.val;
            ESCREVEMEMLOG((long int)(&(TmpWord::val)),sizeof(TmpWord::val),TmpWord::id);
            TmpWord::index = w.index;
            ESCREVEMEMLOG((long int)(&(TmpWord::index)),sizeof(TmpWord::index),TmpWord::id);
        }
};

class WordVector {
public:
    WordVector(int median, int partSize);
    ~WordVector();

    int getCapacity();
    int getSize();
    bool isEmpty();
    void push(Word value); 
    int findIndex(Word el);

    void print(ofstream* out);

    void sort();

    void parseWords(AlphabeticOrder& order);

    Word& operator[](int index);  
    void clear();
private:
    int length; // Numero total de elementos no vetor
    int capacity; // Numero total de elementos que podem ser armazenados no vetor

    // Quicksort props
    int medianSize;
    int minPartSize;

    Word* buffer;

    void quicksort(Word* arr, int start, int end);
    int partition(Word* arr, int start, int end);
};

WordVector::WordVector(int median, int partSize) {
    WordVector::capacity = INITIAL_CAPACITY;
    WordVector::length = 0;
    WordVector::buffer = new Word[INITIAL_CAPACITY];
    WordVector::medianSize = median;
    WordVector::minPartSize = partSize;
}

// Adiciona um elemento ao vetor. 
// Se o vetor atingiu sua capacidade maxima, aloca um vetor
// de capacidade 2 vezes maior e copia os valores antigos
// para o novo vetor
void WordVector::push(Word v) {
    if (length >= WordVector::capacity) {
        if(WordVector::buffer == 0) {
            length = 0;
            capacity = 0;
        }
        
        int newCapacity = WordVector::capacity * CAPACITY_INCREASE_FACTOR;
        Word* newBuffer = new Word[newCapacity];
        int newSize = newCapacity < WordVector::length ? newCapacity : WordVector::length;

        for (int i = 0; i < newSize; i++)
            newBuffer[i] = WordVector::buffer[i];

        WordVector::capacity = newCapacity;
        delete[] WordVector::buffer;
        WordVector::buffer = newBuffer;
    }
    WordVector::buffer[length++] = v;
}

int WordVector::findIndex(Word el) {
    int i = 0;
    int index = -1;
    for (i = 0; i < WordVector::length; i++) {
        if (WordVector::buffer[i] == el) {
            index = i;
            break;
        }
    }
    return index;
}

int WordVector::getSize() {
    return WordVector::length;
}

Word& WordVector::operator[](int index) {
    LEMEMLOG((long int)(
        &(WordVector::buffer[index])),
        sizeof(WordVector::buffer[index]),
        WordVector::buffer[index].getId()
    );
    return WordVector::buffer[index];
}  

int WordVector::getCapacity() {
    return WordVector::capacity;
}

bool WordVector::isEmpty() {
    return WordVector::length == 0;
}

void swap(Word* arr, int i, int j) {
    Word temp = arr[i];
    LEMEMLOG((long int)(&(arr[i])),sizeof(arr[i]),arr[i].getId());
    arr[i] = arr[j];
    LEMEMLOG((long int)(&(arr[j])),sizeof(arr[j]),arr[j].getId());
    ESCREVEMEMLOG((long int)(&(arr[i])),sizeof(arr[i]),arr[i].getId());
    arr[j] = temp;
    LEMEMLOG((long int)(&(arr[j])),sizeof(arr[j]),arr[j].getId());
}

template<class T>
void insertionSort(T* arr, int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        T value = arr[i];
        int j = i;
        while (j > start && arr[j - 1] > value) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = value;
    }
}

int WordVector::partition(Word* arr, int start, int end) {
    int medianIndex = -1;

    int currLength = end - start;
    if (WordVector::medianSize > currLength) {
        int middle = (start + end) / 2;
        medianIndex = middle;
    } else {
        // Cria uma classe para armazenar o valor e o index
        // de cada palavra, de forma temporaria
        TmpWord* tmp = new TmpWord[WordVector::medianSize];
        int i = 0;
        int p = start;
        for (i = 0, p = start; i < WordVector::medianSize; i++, p++) {
            TmpWord w(arr[p], p, arr[p].getId());
            tmp[i] = w;
        }
        insertionSort(tmp, 0, WordVector::medianSize-1);
        int t = WordVector::medianSize;
        if(t % 2){
            medianIndex = tmp[t/2].getIndex();
        } else {
            TmpWord f = tmp[t/2-1];
            TmpWord s = tmp[t/2];
            if (f > s) {
                medianIndex = f.getIndex();
            } else {
                medianIndex = s.getIndex();
            }
        }
        delete tmp;
    }

    erroAssert(medianIndex >= 0, "Error to get median index");

    // Coloca o pivot no final da lista
    swap(arr, medianIndex, end);

    Word pivot = arr[end];
    int i = start - 1;
    int j = start;
    for (j = start; j < end; j++) {
        if (!(arr[j] > pivot)) {
            i++;
            swap(arr, i, j);
        }
    }

    swap(arr, i + 1, end);
    return i + 1;
}

void WordVector::quicksort(Word* arr, int start, int end) {
    if (start < end) {
        int currLength = end - start + 1;
        if (currLength <= WordVector::minPartSize) {
            insertionSort(arr, start, end);
        } else {
            int p = partition(arr, start, end);
            quicksort(arr, start, p - 1);
            quicksort(arr, p + 1, end);
        }
    }
}

void WordVector::sort() {
    int start = 0;
    quicksort(WordVector::buffer, start, WordVector::length-1);
}

// Modifica o valor do index da letra no vetor contendo
// todas as letras da tabela ASCII
void WordVector::parseWords(AlphabeticOrder& order) {
    int i = 0;
    for (i = 0; i < length; i++) {
        WordVector::buffer[i].adaptToNewAlphabeticOrder(order);
    }
}

void WordVector::print(ofstream* out) {
    for (int i = 0; i < length; i++) {
        (*out) << WordVector::buffer[i].toString() << ' ' << WordVector::buffer[i].getReps() << endl;
    }
    (*out) << "#FIM" << endl;
}

WordVector::~WordVector() {
    delete[] WordVector::buffer;
}

void WordVector::clear() {
    WordVector::capacity = 0;
    WordVector::length = 0;
    WordVector::buffer = 0;
}

#endif

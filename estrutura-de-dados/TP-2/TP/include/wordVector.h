#ifndef WORD_VECTOR_H
#define WORD_VECTOR_H

#include "msgassert.h"
#include "word.h"
#include "alphabeticOrder.h"
#include <iostream>

using namespace std;

#define CAPACITY_INCREASE_FACTOR 2
#define INITIAL_CAPACITY 10

class TmpWord {
    public:
        int val;
        int index;
        bool operator>(TmpWord& w) {
            return TmpWord::val > w.val;
        }

        void operator=(TmpWord& w) {
            TmpWord::val = w.val;
            TmpWord::index = w.index;
        }
};

template <class T>
class WordVector {
public:
    WordVector(int median, int partSize);
    ~WordVector();

    int getCapacity();
    int getSize();
    bool isEmpty();
    void push(T value); 
    T pop();
    int findIndex(T el);

    void print();

    void sort();

    void parseWords(AlphabeticOrder& order);

    T operator[](int index);  
    void clear();
private:
    int length; // Numero total de elementos no vetor
    int capacity; // Numero total de elementos que podem ser armazenados no vetor

    // Quicksort props
    int medianSize;
    int minPartSize;

    T* buffer;

    void quicksort(T* arr, int start, int end);
    int partition(T* arr, int start, int end);
};

template<class T>
WordVector<T>::WordVector(int median, int partSize) {
    WordVector::capacity = INITIAL_CAPACITY;
    WordVector::length = 0;
    WordVector::buffer = new T[INITIAL_CAPACITY];
    WordVector::medianSize = median;
    WordVector::minPartSize = partSize;
}

template<class T>
void WordVector<T>::push(T v) {
    if (length >= WordVector::capacity) {
        if(WordVector::buffer == 0) {
            length = 0;
            capacity = 0;
        }
        
        int newCapacity = WordVector::capacity * CAPACITY_INCREASE_FACTOR;
        T * newBuffer = new T[newCapacity];
        int newSize = newCapacity < WordVector::length ? newCapacity : WordVector::length;

        for (int i = 0; i < newSize; i++)
            newBuffer[i] = WordVector::buffer[i];

        WordVector::capacity = newCapacity;
        delete[] WordVector::buffer;
        WordVector::buffer = newBuffer;
    }
    WordVector::buffer[length++] = v;
}

template<class T>
int WordVector<T>::findIndex(T el) {
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

template<class T>
T WordVector<T>::pop() {
    erroAssert(!isEmpty(), "Trying to pop on empty WordVector!");
    T tmp = WordVector::buffer[WordVector::length];
    WordVector::length--;
    return tmp;
}

template<class T>
int WordVector<T>::getSize() {
    return WordVector::length;
}

template<class T>
T WordVector<T>::operator[](int index) {
    return WordVector::buffer[index];
}  

template<class T>
int WordVector<T>::getCapacity() {
    return WordVector::capacity;
}

template<class T>
bool WordVector<T>::isEmpty() {
    return WordVector::length == 0;
}

template<class T>
void swap(T* arr, T i, T j) {
    T temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
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

template<class T>
int WordVector<T>::partition(T* arr, int start, int end) {
    int medianIndex = -1;

    int currLength = end - start;
    if (WordVector::medianSize > currLength) {
        int middle = (start + end) / 2;
        medianIndex = middle;
    } else {
        TmpWord* tmp = new TmpWord[WordVector::medianSize];
        int p = start;
        for (p = start; p < WordVector::medianSize; p++) {
            TmpWord w;
            w.index = p;
            w.val = arr[p];
            tmp[p] = w;
        }
        insertionSort(tmp, 0, WordVector::medianSize);
        int t = WordVector::medianSize - start + 1;
        if(t % 2){
            medianIndex = tmp[t/2].index;
        } else {
            TmpWord f = tmp[t/2-1];
            TmpWord s = tmp[t/2];
            if (f > s) {
                medianIndex = f.index;
            } else {
                medianIndex = s.index;
            }
        }
        delete tmp;
    }

    erroAssert(medianIndex >= 0, "Error to get median index");

    // Coloca o pivot no final da lista
    swap(arr, medianIndex, end);
        
    int pivot = arr[end];
    int i = start - 1;
    int j = start;
    for (j = start; j <= end - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr, i, j);
        }
    }

    swap(arr, i + 1, end);
    return i + 1;
}

template<class T>
void WordVector<T>::quicksort(T* arr, int start, int end) {
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

template<class T>
void WordVector<T>::sort() {
    int start = 0;
    quicksort(WordVector::buffer, start, WordVector::length-1);
}

template<class T>
void WordVector<T>::parseWords(AlphabeticOrder& order) {
    int i = 0;
    for (i = 0; i < length; i++) {
        WordVector::buffer[i].adaptToNewAlphabeticOrder(order);
    }
}

template<class T>
void WordVector<T>::print() {
    for (int i = 0; i < length; i++) {
        cout << buffer[i] << endl;
    }
}

template<class T>
WordVector<T>::~WordVector() {
    delete[] WordVector::buffer;
}

template <class T>
void WordVector<T>::clear() {
    WordVector::capacity = 0;
    WordVector::length = 0;
    WordVector::buffer = 0;
}

#endif
